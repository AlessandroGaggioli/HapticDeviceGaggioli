#include "ros/ros.h"
#include "tf/transform_broadcaster.h"
#include "sensor_msgs/JointState.h"
#include "franka_core_msgs/JointCommand.h"
#include "panda_ik/pandaIk.h"
#include "panda_ik/pandaFk.h"
#include <iostream>
#include <string>
#include <cmath>

#define NumJointState 7
#define frequence 50
#define Ncoefficients 3 
#define N_punti 200

int state = 0 ; 
double  Vmax =  0.1  ; 

std::vector<double> joint_pos_initial ; 
std::vector<double> pos_initial ; 
std::vector<double> pos_final ; 

std::vector<double> joint_vel_initial ; 

std::vector<double> target ; 
std::vector<double> joint_target ; 

std::vector<std::vector<double>> BezierCurve ;

std::vector<std::string> name ; 

bool data = false ;

//CLIENT 
ros::ServiceClient fk_client ; 
ros::ServiceClient ik_client ; 

//SRV
panda_ik::pandaFk fk_srv ; 
panda_ik::pandaIk ik_srv ; 

//SUBSCRIBER 
ros::Subscriber sub ; 

//PUBLISHER 
ros::Publisher pub ; 

typedef struct  {
    std::vector<double> coefficients_x ; 
    std::vector<double> coefficients_y ; 
    std::vector<double> coefficients_z ; 
} coefficients ; 

double distance_max(double a,double b,double c) {
    double max = a; 
    if(b>a) max = b ; 
    if(c>max) max = c; 
return max ; 
}

coefficients calc_coefficients(coefficients *coeff,std::vector<double> pos_init,std::vector<double>joint_pos_init,std::vector<double> pos_fin) {
   // std::cout <<"IN CALC_COEFFICIENTS\n" ;
    if(data) {
                        //Request FK della posizione iniziale
                        fk_srv.request.reference_joints.position=joint_pos_init ;
                        if(fk_client.call(fk_srv)) {    
                        pos_init[0]=fk_srv.response.solution.position.x ; 
                        pos_init[1]=fk_srv.response.solution.position.y ;
                        pos_init[2]=fk_srv.response.solution.position.z ;
                        pos_init[3]=fk_srv.response.solution.orientation.x ;
                        pos_init[4]=fk_srv.response.solution.orientation.y ;
                        pos_init[5]=fk_srv.response.solution.orientation.z ;
                        pos_init[6]=fk_srv.response.solution.orientation.w ;

                        std::cout <<"\npos_initial: \n" ; 
                        for(int i=0;i<NumJointState;i++) {
                            std::cout <<pos_init[i] <<std::endl ; 
                        }
                    }  
        else {
                std::cout <<"\nfail fk_service\n" ;  
            }
    } 
    data = false ; 

    //Calcolo dei coefficienti della polinomiale 

    double distance_x = pos_fin[0] - pos_init[0] ; //distanza da percorrere lungo x
    double distance_y = pos_fin[1] - pos_init[1] ; //distanza da percorrere lungo y
    double distance_z = pos_fin[2] - pos_init[2] ; //distanza da percorrere lungo z

    double period = abs(distance_max(distance_x,distance_y,distance_z)) / Vmax; //periodo = distanza max / Vmax 

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
    double modulo_velocita = sqrt(pow(joint_vel_initial[0],2)+pow(joint_vel_initial[1],2)+pow(joint_vel_initial[2],3))  ; //calcolo il modulo della velocità per calcolare il versore
    for(int i=0;i<3;i++) pos_ctrl_1[i] = pos_init[i]+proiezione * joint_vel_initial[i] / modulo_velocita ;

    //posizione di controllo 2 -- 
    std::vector<double> direzione_ctrl_2 ; 
    direzione_ctrl_2.resize(3) ; 
    direzione_ctrl_2[0] = 2*(pos_fin[4]*pos_fin[6]+pos_fin[5]*pos_fin[3]) ; 
    direzione_ctrl_2[1] = 2*(pos_fin[5]*pos_fin[6]-pos_fin[4]*pos_fin[3]) ; 
    direzione_ctrl_2[2] = pow(pos_fin[3],2)-pow(pos_fin[4],2)-pow(pos_fin[5],2)+pow(pos_fin[6],2) ; 
    for(int i=0;i<3;i++) pos_ctrl_2[i] = proiezione * direzione_ctrl_2[i] +pos_fin[i] ; 
    // --------------------------
    // --------------------------

    std::cout <<"POS CTRL \n" ; 
    for(int i=0;i<NumJointState;i++) {
        std::cout <<pos_ctrl_1[i] <<std::endl ;
    }

    for(int i=0;i<NumJointState;i++) {
        std::cout <<pos_ctrl_2[i] <<std::endl ;
    }

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
    double distance_x = pos_fin[0] - pos_init[0] ; //distanza da percorrere lungo x
    double distance_y = pos_fin[1] - pos_init[1] ; //distanza da percorrere lungo y
    double distance_z = pos_fin[2] - pos_init[2] ; //distanza da percorrere lungo z

    double period = abs(distance_max(distance_x,distance_y,distance_z)) / Vmax; //periodo = distanza max / Vmax S

    std::vector<std::vector<double>> BezierCurve ; 
    BezierCurve.resize(Npunti) ; 

    double DeltaT = period/Npunti ; //calcolo il DeltaT come perioso su numero di punti


    /* CURVA BEZIER 

        x = ax * t^3 + bx * t^2 + cx * t + x0 
        y = ay * t^3 + by * t^2 + cy * t + y0
        z = az * t^3 + bz * t^2 + cz * t + z0  */

    for(int i=0;i<Npunti;i++) {
        for(int j=Ncoefficients;j>0;j--) {
            target[0] += coeff.coefficients_x[j]*pow(DeltaT*(i+1),j) ; 
            target[1] += coeff.coefficients_y[j]*pow(DeltaT*(i+1),j) ; 
            target[2] += coeff.coefficients_z[j]*pow(DeltaT*(i+1),j) ;
        }

        for(int k=0;k<3;k++) target[k] += pos_init[k] ; 

        for(int k=3;k<7;k++) {
            target[k]=pos_fin[k] ; 
        }
        BezierCurve[i] = target ; 
        for(int k=0;k<NumJointState;k++) target[k] =0 ;  

        //for(int k=0;k<NumJointState;k++) std::cout <<target[k] ; 
    }

return BezierCurve ; 
}

void JointStateCallback(const sensor_msgs::JointState& msg_send_received) {
    //ricevo posizione di partenza 
    int j=0 ; 
    for(int i=0;i<9;i++) {
        if(msg_send_received.name[i] != "panda_finger_joint1" && msg_send_received.name[i] != "panda_finger_joint2") {
            name[j]=msg_send_received.name[i] ; 
            joint_pos_initial[j]=msg_send_received.position[i] ; 
            joint_vel_initial[j]=msg_send_received.velocity[i] ; 
            j++  ; 
        }
    }

   /* std::cout <<"\nname and position: " <<std::endl ; 
    for(int i=0;i<name.size();i++) {
        std::cout <<name[i] <<"\t" ; 
        std::cout <<joint_pos_initial[i] <<"\t"  ; 
    } std::cout <<std::endl ; */

    data = true ; 
    //-------------------------------------
}

int main(int argc,char **argv) {

    coefficients coeff_Bezier ;

    name.resize(NumJointState) ; 
    joint_pos_initial.resize(NumJointState) ; 
    joint_vel_initial.resize(NumJointState) ;
    pos_final.resize(NumJointState) ;    
    pos_initial.resize(NumJointState) ; 
    target.resize(NumJointState) ; 
    coeff_Bezier.coefficients_x.resize(Ncoefficients) ;    
    coeff_Bezier.coefficients_y.resize(Ncoefficients) ;    
    coeff_Bezier.coefficients_z.resize(Ncoefficients) ;  

    name[0]="panda_joint1" ; 
    name[1]="panda_joint2" ;
    name[2]="panda_joint3" ;
    name[3]="panda_joint4" ;
    name[4]="panda_joint5" ;
    name[5]="panda_joint6" ;
    name[6]="panda_joint7" ;

    //Init and Node Handle
    ros::init(argc,argv,"MacchinaStati") ; 
    ros::NodeHandle n ; 
    ros::Rate loop_rate(frequence) ; 

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

    while(ros::ok()) {
        
        switch(state) {
            case 0: {
                //state: init, accendo haptic 
                state = 1 ; 
            } break ; 
            case 1: {
                //state: una volta acceso l'haptic, inizio a leggere le posizioni, 
                //converto le posizioni dal ref. frame haptic a quello del robot, 
                //collego l'haptic al robot
                state = 2 ; 
            } break ; 
            case 2: {
                //state: accendo il calcolo della traiettoria, aspetto che si definisca l'oggetto da 
                //prendere, la sua posizione e orientamento
                state = 3 ; 
            } break ; 
            case 3: {
                //state: calcolo dei coefficienti della curva Bezier
                calc_coefficients(&coeff_Bezier,pos_initial,joint_pos_initial,pos_final) ; 
                std::cout <<"\nCOEFFICIENTS :\n" ; 
                for(int i=0;i<Ncoefficients;i++) {
                    std::cout <<coeff_Bezier.coefficients_x[i] <<std::endl; 
                    std::cout <<coeff_Bezier.coefficients_y[i] <<std::endl ; 
                    std::cout <<coeff_Bezier.coefficients_z[i] <<std::endl; 
                }

                int in ; 
                std::cin >>in ; 
                while(!in) ; 


                state = 4 ; 
            } break ; 
            case 4: {
                //state: calcolo i punti della traiettoria completa
                BezierCurve = ComputeBezier(N_punti,pos_initial,pos_final,coeff_Bezier) ; 
                std::cout <<"\n PUNTI CURVA\n" ; 
                for(int i=0;i<N_punti;i++) {
                    std::cout <<"\npunto " <<i <<std::endl ; 
                    for(int j=0;j<NumJointState;j++) {
                        std::cout <<std::endl <<BezierCurve[i][j] <<std::endl ;
                    } 
                    
                }
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
            //set name e position del msg_send
            msg_send.names=name ; 
            msg_send.position=joint_target ; 
            //pubblico msg_send
            pub.publish(msg_send) ;*/

    ros::spinOnce() ; 
    loop_rate.sleep() ;
    }

    ros::spin() ; 

return 0 ; 
}


