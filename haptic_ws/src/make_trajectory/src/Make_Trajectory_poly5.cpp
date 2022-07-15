#include "ros/ros.h"
#include "sensor_msgs/JointState.h"
#include "franka_core_msgs/JointCommand.h"
#include "panda_ik/pandaIk.h"
#include "panda_ik/pandaFk.h"
#include <iostream>
#include <string>
#include <cmath>

#define NumJointState 7
#define frequence 50
#define Ncoefficients 6 
#define Vmax 0.1 

double period ; 

std::vector<double> joint_pos_initial ; 
std::vector<double> pos_initial ; 
std::vector<double> pos_final ; 

std::vector<double> target ; 
std::vector<double> joint_target ; 

std::vector<double> coefficients_x ; 
std::vector<double> coefficients_y ; 
std::vector<double> coefficients_z ; 

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

double distance_max(double a,double b,double c) {
    double max = a; 
    if(b>a) max = b ; 
    if(c>max) max = c; 
return max ; 
}

void JointStateCallback(const sensor_msgs::JointState& msg_send_received) {
    //ricevo posizione di partenza 
    int j=0 ; 
    for(int i=0;i<9;i++) {
        if(msg_send_received.name[i] != "panda_finger_joint1" && msg_send_received.name[i] != "panda_finger_joint2") {
            name[j]=msg_send_received.name[i] ; 
            joint_pos_initial[j]=msg_send_received.position[i] ; 
            j++  ; 
        }
    }

    std::cout <<"\nname and position: " <<std::endl ; 
    for(int i=0;i<name.size();i++) {
        std::cout <<name[i] <<"\t" ; 
        std::cout <<joint_pos_initial[i] <<"\t"  ; 
    } std::cout <<std::endl ; 

    data = true ; 
    //-------------------------------------
}


int main (int argc,char **argv) {
    name.resize(NumJointState) ; 
    joint_pos_initial.resize(NumJointState) ; 
    pos_final.resize(NumJointState) ;    
    pos_initial.resize(NumJointState) ; 
    target.resize(NumJointState) ; 
    coefficients_x.resize(Ncoefficients) ;    
    coefficients_y.resize(Ncoefficients) ;    
    coefficients_z.resize(Ncoefficients) ;   
    
    name[0]="panda_joint1" ; 
    name[1]="panda_joint2" ;
    name[2]="panda_joint3" ;
    name[3]="panda_joint4" ;
    name[4]="panda_joint5" ;
    name[5]="panda_joint6" ;
    name[6]="panda_joint7" ;

    //Init and Node Handle
    ros::init(argc,argv,"Make_Trajectory_poly5") ; 
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

    //ricevo i dati
    sub= n.subscribe("joint_states",1,JointStateCallback) ; 

    while(ros::ok()) {
        //se ho ricevuto i dati 
        if(data) {
            //Request FK della posizione iniziale
            fk_srv.request.reference_joints.position=joint_pos_initial ;   
            if(fk_client.call(fk_srv)) {    
                pos_initial[0]=fk_srv.response.solution.position.x ; 
                pos_initial[1]=fk_srv.response.solution.position.y ;
                pos_initial[2]=fk_srv.response.solution.position.z ;
                pos_initial[3]=fk_srv.response.solution.orientation.x ;
                pos_initial[4]=fk_srv.response.solution.orientation.y ;
                pos_initial[5]=fk_srv.response.solution.orientation.z ;
                pos_initial[6]=fk_srv.response.solution.orientation.w ;

                std::cout <<"\npos_initial: \n" ; 
                for(int i=0;i<NumJointState;i++) {
                    std::cout <<pos_initial[i] <<std::endl ; 
                }
            }  
            else {
                std::cout <<"\nfail fk_service\n" ;  
            }

            //Calcolo dei Coefficienti della Polinomiale 

                std::cout <<"\ndistance \n" ; 

                double distance_x = pos_final[0] - pos_initial[0] ; //distanza da percorrere lungo x
                double distance_y = pos_final[1] - pos_initial[1] ; //distanza da percorrere lungo y
                double distance_z = pos_final[2] - pos_initial[2] ; //distanza da percorrere lungo z
                period = distance_max(distance_x,distance_y,distance_z) / Vmax; //periodo = distanza max / Vmax 

                std::cout <<distance_x <<" " <<distance_y <<" " <<distance_z <<"  max: " <<distance_max(distance_x,distance_y,distance_z) <<" periodo: " <<period ; 

                std::cout <<"\n\ncalcolo coefficienti\n" ; 

                //calcolo coefficienti 
                coefficients_x[0]=pos_initial[0] ; 
                coefficients_x[1]=0 ; 
                coefficients_x[2]=0 ; 
                coefficients_x[3]=0.5 * pow(period,-3) *20 * (distance_x) ; 
                coefficients_x[4]=0.5 * pow(period,-4) *30 * (distance_x) ; 
                coefficients_x[5]=0.5 * pow(period,-5) *12 * (distance_x) ; 
        
                coefficients_y[0]=pos_initial[1] ; 
                coefficients_y[1]=0 ; 
                coefficients_y[2]=0 ; 
                coefficients_y[3]=0.5 * pow(period,-3) *20 * (distance_y) ; 
                coefficients_y[4]=0.5 * pow(period,-4) *30 * (distance_y) ; 
                coefficients_y[5]=0.5 * pow(period,-5) *12 * (distance_y) ; 
                
                coefficients_z[0]=pos_initial[2] ; 
                coefficients_z[1]=0 ; 
                coefficients_z[2]=0 ; 
                coefficients_z[3]=0.5 * pow(period,-3) *20 * (distance_z) ; 
                coefficients_z[4]=0.5 * pow(period,-4) *30 * (distance_z) ; 
                coefficients_z[5]=0.5 * pow(period,-5) *12 * (distance_z) ; 

                std::cout <<"\nCoefficienti: \n" ; 
                for(int i=0;i<Ncoefficients;i++) {
                    std::cout <<coefficients_x[i] <<std::endl ; 
                    std::cout <<coefficients_y[i] <<std::endl ;
                    std::cout <<coefficients_z[i] <<std::endl <<std::endl ;   
                }

            double N_punti = 1000 ; 
            double DeltaT = period / N_punti;

            std::cout <<"\nDeltaT: \n" <<DeltaT <<std::endl ; 

            //Calcolo posizione target da raggiungere con l'equazione polinomiale
            for(int i=0;i<Ncoefficients;i++) {
                target[0] += coefficients_x[i] * pow(DeltaT,i) ;  
                target[1] += coefficients_y[i] * pow(DeltaT,i) ; 
                target[2] += coefficients_z[i] * pow(DeltaT,i) ; 
            } 
            //copio l'orientazione 
            for(int i=3;i<7;i++) {
                target[i] = pos_final[i] ; 
            }

            std::cout <<"\ntarget:\n" ; 

            for(int i=0;i<NumJointState;i++) {
                    std::cout <<target[i] <<std::endl ; 
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
    pub.publish(msg_send) ;
    //clear bool data */
    data = false ; 
}
//ciclo
    ros::spinOnce() ; 
    loop_rate.sleep() ; 
    }
    ros::spin() ; 
}