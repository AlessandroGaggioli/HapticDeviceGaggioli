#include "ros/ros.h"
#include "tf/transform_broadcaster.h"
#include "sensor_msgs/JointState.h"
#include "franka_core_msgs/JointCommand.h"
#include "panda_ik/pandaIk.h"
#include "panda_ik/pandaFk.h"
#include <iostream>
#include <string>
#include <cmath>
#include <tf2_ros/transform_listener.h>
#include <geometry_msgs/TransformStamped.h>
#include "geometry_msgs/PointStamped.h" 
#include "tf2_ros/message_filter.h"
#include "message_filters/subscriber.h"
#include "tf2_geometry_msgs/tf2_geometry_msgs.h"

#define NumJointState 7
#define frequence 50
#define Ncoefficients 3 
#define N_punti 200

int state = 0 ; 

std::vector<double> pos_final ; 

std::vector<double> robot_pos_link0 ; 

std::vector<double> vel_initial ; 

std::vector<double> haptic_pose ; 
std::vector<double> haptic_vel ; 

std::vector<double> target ; 
std::vector<double> joint_target ; 

std::vector<double> offset_haptic_to_robot ; 
std::vector<double> offset_robot_to_haptic ; 

std::vector<std::vector<double>> BezierCurve ;

//CLIENT 
ros::ServiceClient fk_client ; 
ros::ServiceClient ik_client ; 

//SRV
panda_ik::pandaFk fk_srv ; 
panda_ik::pandaIk ik_srv ; 

//SUBSCRIBER 
ros::Subscriber sub ; 
ros::Subscriber haptic_sub ; 

//PUBLISHER 
ros::Publisher pub ; 

typedef struct  {
    std::vector<double> coefficients_x ; 
    std::vector<double> coefficients_y ; 
    std::vector<double> coefficients_z ; 
} coefficients ; 

coefficients calc_coefficients(coefficients *coeff,std::vector<double> pos_init,std::vector<double> pos_fin,std::vector<double> vel_init) {

    //Calcolo dei coefficienti della polinomiale 

    coeff->coefficients_x.resize(Ncoefficients) ;   
    coeff->coefficients_y.resize(Ncoefficients) ;   
    coeff->coefficients_z.resize(Ncoefficients) ;   

    // POS_CTRL_1 E POS_CTRL_2 posizioni di controllo

    std::vector<double> pos_ctrl_1 ; 
    std::vector<double> pos_ctrl_2 ; 
    pos_ctrl_1.resize(NumJointState) ; 
    pos_ctrl_2.resize(NumJointState) ; 

    //posizione di controllo 1 definita come il versore della velocità per la lunghezza del prolungamento
    double proiezione = 0.05 ; //distanza del punto 1 rispetto al punto 0 
    double modulo_velocita = sqrt(pow(vel_init[0],2)+pow(vel_init[1],2)+pow(vel_init[2],3))  ; //calcolo il modulo della velocità per calcolare il versore
    for(int i=0;i<3;i++) pos_ctrl_1[i] = pos_init[i]+proiezione * vel_init[i] / modulo_velocita ;

    //posizione di controllo 2 -- calcolata dal quaternione del punto finale
    std::vector<double> direzione_ctrl_2 ; 
    direzione_ctrl_2.resize(3) ; 
    direzione_ctrl_2[0] = 2*(pos_fin[4]*pos_fin[6]+pos_fin[5]*pos_fin[3]) ; 
    direzione_ctrl_2[1] = 2*(pos_fin[5]*pos_fin[6]-pos_fin[4]*pos_fin[3]) ; 
    direzione_ctrl_2[2] = pow(pos_fin[3],2)-pow(pos_fin[4],2)-pow(pos_fin[5],2)+pow(pos_fin[6],2) ; 
    for(int i=0;i<3;i++) pos_ctrl_2[i] = proiezione * direzione_ctrl_2[i] +pos_fin[i] ; 
    // --------------------------
    // --------------------------

    coeff->coefficients_x[2] = 3.0 *(pos_ctrl_1[0] - pos_init[0]) ; 
    coeff->coefficients_x[1] = 3.0 *(pos_ctrl_2[0] - pos_ctrl_1[0]) - coeff->coefficients_x[2] ; 
    coeff->coefficients_x[0] = pos_fin[0] - pos_init[0] - coeff->coefficients_x[2] - coeff->coefficients_x[1] ; 

    coeff->coefficients_y[2] = 3.0 * (pos_ctrl_1[1] - pos_init[1]) ; 
    coeff->coefficients_y[1] = 3.0 * (pos_ctrl_2[1] - pos_ctrl_1[1]) - coeff->coefficients_y[2] ; 
    coeff->coefficients_y[0] = pos_fin[1] - pos_init[1] - coeff->coefficients_y[2] - coeff->coefficients_y[1] ; 

    coeff->coefficients_z[2] = 3.0 * (pos_ctrl_1[2] - pos_init[2]) ; 
    coeff->coefficients_z[1] = 3.0 * (pos_ctrl_2[2] - pos_ctrl_1[2]) - coeff->coefficients_z[2] ; 
    coeff->coefficients_z[0] = pos_fin[2] - pos_init[2] - coeff->coefficients_z[2] - coeff->coefficients_z[1] ; 

return *coeff ;
}

std::vector<std::vector<double>> ComputeBezier(double Npunti,std::vector<double> pos_init,std::vector<double> pos_fin,coefficients coeff) {

    std::vector<std::vector<double>> BezierCurve ; 
    BezierCurve.resize(Npunti) ; 

    /* CURVA BEZIER 

        x = ax * t^3 + bx * t^2 + cx * t + x0 
        y = ay * t^3 + by * t^2 + cy * t + y0
        z = az * t^3 + bz * t^2 + cz * t + z0  */

    double dt = 1.0/(Npunti-1) ; 

    for(int i=0;i<Npunti;i++) {
        for(int j=Ncoefficients;j>0;j--) {
            target[0] += coeff.coefficients_x[3-j]*pow(dt*i,j) ; 
            target[1] += coeff.coefficients_y[3-j]*pow(dt*i,j) ; 
            target[2] += coeff.coefficients_z[3-j]*pow(dt*i,j) ;
        }

        for(int k=0;k<3;k++) target[k] += pos_init[k] ; 

        for(int k=3;k<7;k++) {
            target[k]=pos_fin[k] ; 
        }
        BezierCurve[i] = target ; 

        for(int k=0;k<NumJointState;k++) target[k] =0 ;  
    }

return BezierCurve ; 
}


void JointStateCallback(const sensor_msgs::JointState& msg_send_received) {
    //ricevo posizione di partenza 
    int j=0 ; 
    for(int i=0;i<9;i++) {
        if(msg_send_received.name[i] != "panda_finger_joint1" && msg_send_received.name[i] != "panda_finger_joint2") {
            vel_initial[j]=msg_send_received.velocity[i] ; 
            j++  ; 
        }
    }

   //-------------------------------------
}

void HapticEndEffectorCallback(const sensor_msgs::JointState& msg) {
    //ricevo posizione dell'haptic
    for(int i=0;i<7;i++) {
        haptic_pose[i]=msg.position[i] ; 
        haptic_vel[i]=msg.velocity[i] ; 
        std::cout <<haptic_pose[i] <<std::endl ; 
    }


}

std::vector<double> ConvertWorkspace(std::vector<double> robot_pos,std::vector<double> haptic_pos,std::string mode) {

    std::vector<double> offset ;
    if(mode == "haptic_to_robot") {
         
        offset.resize(3) ; 
        offset[0] = robot_pos[0] - haptic_pos[0] ; 
        offset[1] = robot_pos[1] - haptic_pos[1] ; 
        offset[2] = robot_pos[2] - haptic_pos[2] ; 
    }
    else if(mode == "robot_to_haptic") {
        
        offset.resize(3) ; 
        offset[0] = haptic_pos[0] - robot_pos[0] ; 
        offset[1] = haptic_pos[1] - robot_pos[1] ; 
        offset[2] = haptic_pos[2] - robot_pos[2] ;
    }

return offset ; 
}

int main(int argc,char **argv) {

    coefficients coeff_Bezier ;

    vel_initial.resize(NumJointState) ;
    pos_final.resize(NumJointState) ;    
    haptic_pose.resize(NumJointState) ; 
    haptic_vel.resize(NumJointState) ; 
    target.resize(NumJointState) ; 
    robot_pos_link0.resize(NumJointState) ; 
    coeff_Bezier.coefficients_x.resize(Ncoefficients) ;    
    coeff_Bezier.coefficients_y.resize(Ncoefficients) ;    
    coeff_Bezier.coefficients_z.resize(Ncoefficients) ;  
    offset_haptic_to_robot.resize(3) ; 
    offset_robot_to_haptic.resize(3) ; 

    //Init and Node Handle
    ros::init(argc,argv,"MacchinaStati") ; 
    ros::NodeHandle n ; 
    ros::Rate loop_rate(frequence) ; 

    //TF2_LISTENER
    tf2_ros::Buffer tfBuffer ; 
    tf2_ros::TransformListener tfListener(tfBuffer) ;
    ros::Rate rate(10.0) ; 

    //Client
    fk_client=n.serviceClient<panda_ik::pandaFk>("panda_fk_service") ;
    ik_client=n.serviceClient<panda_ik::pandaIk>("panda_ik_service") ;

    //Publisher
    pub=n.advertise<franka_core_msgs::JointCommand>("/panda_simulator/motion_controller/arm/joint_commands",1) ; 

    //ricevo posizione finale da tastiera-----------------
    std::cout <<"\nposizione di arrivo:\n" ; 
    for(int i=0;i<NumJointState;i++) {
        std::cin >>pos_final[i] ;
    }
    //----------------------------------------
    //----------------------------------------

    //Subscriber - ricevo i dati  
    sub= n.subscribe("joint_states",1,JointStateCallback) ; 
    haptic_sub=n.subscribe("geomagic/end_effector_pose",1,HapticEndEffectorCallback) ; 

    while(ros::ok()) {
        
        switch(state) {
            case 0: {
                //state: init, accendo haptic 
                state = 1 ; 
            } break ; 

            case 1: {
                //state: una volta acceso l'haptic, inizio a leggere le posizioni, 
                //converto le posizioni dal ref. frame end effector a quello del robot, 
                //collego l'haptic al robot previa trasformazione con offset delle posizioni

                // tf reference frame end effector - robot ------------------
                geometry_msgs::TransformStamped transformStamped ;
                try{
                    transformStamped = tfBuffer.lookupTransform("panda_link0","panda_hand",ros::Time(0)) ;   
                }
                catch (tf2::TransformException &ex) {
                    ROS_WARN("%s",ex.what()) ; 
                    ros::Duration(1.0).sleep() ; 
                    continue ; 
                }

                robot_pos_link0[0] = transformStamped.transform.translation.x ;
                robot_pos_link0[1] = transformStamped.transform.translation.y ;
                robot_pos_link0[2] = transformStamped.transform.translation.z ; 
                robot_pos_link0[3] = transformStamped.transform.rotation.x ;
                robot_pos_link0[4] = transformStamped.transform.rotation.y  ;
                robot_pos_link0[5] = transformStamped.transform.rotation.z ;
                robot_pos_link0[6] = transformStamped.transform.rotation.w ; 

                /*std::cout <<"\nrobot_pos_link0: \n" ;
                for(int i=0;i<robot_pos_link0.size();i++) std::cout <<robot_pos_link0[i] <<std::endl ; 
                std::cout <<std::endl ; */

                //-----------------------------------------------------------

                //--- conversione posizione haptic -> robot ------------------

                offset_haptic_to_robot = ConvertWorkspace(robot_pos_link0,haptic_pose,"haptic_to_robot") ; 

                //---------------------------------------------------------------------

                //----- calcolo posizioni reali, conversione haptic to robot-----------
                for(int i=0;i<3;i++) robot_pos_link0[i] += offset_haptic_to_robot[i] ; 
                //---------------------------------------------------------------------

                

                state = 2 ; 
            } break ; 

            case 2: {
                //state: accendo il calcolo della traiettoria, aspetto che si definisca l'oggetto da 
                //prendere, la sua posizione e orientamento
                state = 3 ; 
            } break ; 
            case 3: {
                //state: calcolo dei coefficienti della curva Bezier

                //----calcolo coefficienti ---------------------------------------------
                calc_coefficients(&coeff_Bezier,robot_pos_link0,pos_final,vel_initial) ; 
                //---------------------------------------------------------------------

                state = 4 ; 
            } break ; 
            case 4: {
                //state: calcolo i punti della traiettoria completa------------------
                BezierCurve = ComputeBezier(N_punti,robot_pos_link0,pos_final,coeff_Bezier) ; 
                
                std::cout <<"\n PUNTI CURVA\n" ; 
                for(int i=0;i<N_punti;i++) {
                    std::cout <<"\npunto " <<i <<std::endl ; 
                    for(int j=0;j<NumJointState;j++) {
                        std::cout <<std::endl <<BezierCurve[i][j] <<std::endl ;
                    } 
                    
                }
                //-----------------------------------------------------------
                //--------conversione posizione robot-> haptic---------------
                offset_robot_to_haptic = ConvertWorkspace(robot_pos_link0,haptic_pose,"robot_to_haptic") ;
                //-----------------------------------------------------------
                state = 0 ; 
            } break ; 
        }

        /*
            //dichiaro msg_send tipo franka_core_msgs
            franka_core_msgs::JointCommand msg_send ; 

            //Request IK del target
            ik_srv.request.reference_pose.position.x=target[0] ; 
            ik_srv.request.reference_pose.position.y=target[1] ; 
            ik_srv.request.reference_pose.position.z=target[2] ; 
            ik_srv.request.reference_pose.orientation.x=target[3] ; 
            ik_srv.request.reference_pose.orientation.y=target[4] ; 
            ik_srv.request.reference_pose.orientation.z=target[5] ; 
            ik_srv.request.reference_pose.orientation.w=target[6] ;

            //chiama ik_client 
            if(ik_client.call(ik_srv)) {
            //if success
            if(ik_srv.response.success) {
                //inserisci in joint_target la posizione dei giunti dei passi
                std::cout <<"Joint Target\n" ; 
                for(int i=0;i<NumJointState;i++) {
                    joint_target[i]=ik_srv.response.solution.position[i] ; 
                    std::cout <<joint_target[i] <<std::endl ; 
                    }
            } else std::cout <<"no result\n" ; 
        }
            else {
                    std::cout <<"\nfail ik_service\n" ; 
                }
            
            msg_send.mode=1 ; 
            //set position del msg_send
            msg_send.position=joint_target ; 
            //pubblico msg_send
            pub.publish(msg_send) ;*/

    ros::spinOnce() ; 
    loop_rate.sleep() ;
    }

    ros::spin() ; 

return 0 ; 
}


