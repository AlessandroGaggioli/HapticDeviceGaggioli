#include "ros/ros.h"
#include "sensor_msgs/JointState.h"
#include "franka_core_msgs/JointCommand.h"
#include "panda_ik/pandaIk.h"
#include "panda_ik/pandaFk.h"
#include <iostream>
#include <string>

#define NumJointState 7
#define N_STEP 50
#define frequence 50

std::vector<double> joint_pos_initial ; 
std::vector<double> pos_final ; 
std::vector<double> pos_initial ; 

std::vector<double> target ; 
std::vector<double> joint_target ; 

std::vector<std::string> name ; 

double difference ; 
double step ;

bool data = false ; 

//CLIENT
ros::ServiceClient fk_client ; 
ros::ServiceClient ik_client ; 

//SRV
panda_ik::pandaFk fk_srv ; 
panda_ik::pandaIk ik_srv ; 

//PUBLISHER 
ros::Publisher pub ; 

//SUBSCRIBER 
ros::Subscriber sub ; 

void JointStateCallback(const sensor_msgs::JointState& msg_send_received) {
     
    //ricevo posizione di partenza --------
    int j=0 ; 
    for(int i=0;i<9;i++) {
        if(msg_send_received.name[i] != "panda_finger_joint1" && msg_send_received.name[i]!= "panda_finger_joint2") {
            name[j]=msg_send_received.name[i] ; 
            joint_pos_initial[j]=msg_send_received.position[i] ; 
            j++  ; 
        }
    }

    std::cout <<"name and position: " <<std::endl ; 
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
    joint_target.resize(NumJointState) ; 

    name[0]="panda_joint1" ; 
    name[1]="panda_joint2" ;
    name[2]="panda_joint3" ;
    name[3]="panda_joint4" ;
    name[4]="panda_joint5" ;
    name[5]="panda_joint6" ;
    name[6]="panda_joint7" ;

    //Init and Node Handle
    ros::init(argc,argv,"make_trajectory_read_joint_v2") ; 
    ros::NodeHandle n ; 
    ros::Rate loop_rate(frequence) ; 

    //Client
    fk_client=n.serviceClient<panda_ik::pandaFk>("panda_fk_service") ;
    ik_client=n.serviceClient<panda_ik::pandaIk>("panda_ik_service") ;

    //PUBLISHER
    pub=n.advertise<franka_core_msgs::JointCommand>("jointstate",1) ; 

    //ricevo posizione finale-----------------
    std::cout <<"\nposizione di arrivo:\n" ; 
    for(int i=0;i<NumJointState;i++) {
        std::cin >>pos_final[i] ; 
    }
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
                    //////////////////////////////
                    target[i]=pos_initial[i] ; 
                    /////////////////////////////
                }
            }  
            else {
                std::cout <<"\nfail fk_service\n" ;  
            }

            //calcolo differenza tra posizioni 
            difference = pos_final[0]-pos_initial[0] ; 
            //divido la differenza per il numero di step desiderati 
            step = (difference / (double) N_STEP ) ; 

            //dichiaro msg_send tipo franka_core_msgs
            franka_core_msgs::JointCommand msg_send ; 

            //FOR per ogni step calcolato
            for(int i=0;i<step;i++) {
            //Ad ogni passo, aggiungo lo step lungo x
            target[0] += step ; 
            //chiamo ik_panda_service per ricevere posizioone dei giunti 
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
                std::cout <<"\nJoint target\n" ; 
                for(int i=0;i<NumJointState;i++) {
                    joint_target[i]=ik_srv.response.solution.position[i] ; 
                    std::cout <<joint_target[i] <<std::endl ; 
                    }
                } 
                else std::cout <<"no result\n" ; 
            }
                else {
                    std::cout <<"\nfail ik_service\n" ; 
                }
            }

            msg_send.mode=1 ; 
            //set name e position del msg_send_send
            msg_send.names=name ; 
            msg_send.position=joint_target ; 
            //pubblico msg_send
            pub.publish(msg_send) ;
            //clear bool data 
            data = false ; 
        }

    //ciclo
    ros::spinOnce() ; 
    loop_rate.sleep() ; 
    }
    ros::spin() ; 
return 0 ; 
}
