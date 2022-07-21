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
#define N_punti 200 

int state = 0 ; 

std::vector<double> joint_pos_initial ; 
std::vector<double> pos_initial ; 
std::vector<double> pos_final ; 

std::vector<double> target ; 
std::vector<double> joint_target ; 

std::vector<std::vector<double>> poly5 ; 

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

coefficients calc_coefficients(coefficients *coeff,std::vector<double> pos_init,std::vector<double> joint_pos_init,std::vector<double> pos_fin) {
                    
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

                    //Calcolo dei Coefficienti della Polinomiale 

                    double distance_x = pos_fin[0] - pos_init[0] ; //distanza da percorrere lungo x
                    double distance_y = pos_fin[1] - pos_init[1] ; //distanza da percorrere lungo y
                    double distance_z = pos_fin[2] - pos_init[2] ; //distanza da percorrere lungo z

                    double period = distance_max(distance_x,distance_y,distance_z) / Vmax; //periodo = distanza max / Vmax 

                    coeff->coefficients_x.resize(Ncoefficients) ;
                    coeff->coefficients_y.resize(Ncoefficients) ;
                    coeff->coefficients_z.resize(Ncoefficients) ;

                    coeff->coefficients_x[0]=pos_init[0] ; 
                    coeff->coefficients_x[1]=0 ; 
                    coeff->coefficients_x[2]=0 ; 
                    coeff->coefficients_x[3]=0.5 * pow(period,-3) *20 * (distance_x) ; 
                    coeff->coefficients_x[4]=0.5 * pow(period,-4) *30 * (distance_x) ; 
                    coeff->coefficients_x[5]=0.5 * pow(period,-5) *12 * (distance_x) ; 
            
                    coeff->coefficients_y[0]=pos_init[1] ; 
                    coeff->coefficients_y[1]=0 ; 
                    coeff->coefficients_y[2]=0 ; 
                    coeff->coefficients_y[3]=0.5 * pow(period,-3) *20 * (distance_y) ; 
                    coeff->coefficients_y[4]=0.5 * pow(period,-4) *30 * (distance_y) ; 
                    coeff->coefficients_y[5]=0.5 * pow(period,-5) *12 * (distance_y) ; 
                    
                    coeff->coefficients_z[0]=pos_init[2] ; 
                    coeff->coefficients_z[1]=0 ; 
                    coeff->coefficients_z[2]=0 ; 
                    coeff->coefficients_z[3]=0.5 * pow(period,-3) *20 * (distance_z) ; 
                    coeff->coefficients_z[4]=0.5 * pow(period,-4) *30 * (distance_z) ; 
                    coeff->coefficients_z[5]=0.5 * pow(period,-5) *12 * (distance_z) ; 
                
                    return *coeff ;
                  }

std::vector<std::vector<double>> trajectory_points(double Npunti,std::vector<double> pos_init,std::vector<double> pos_fin,coefficients coeff) {

                    double distance_x = pos_fin[0] - pos_init[0] ; //distanza da percorrere lungo x
                    double distance_y = pos_fin[1] - pos_init[1] ; //distanza da percorrere lungo y
                    double distance_z = pos_fin[2] - pos_init[2] ; //distanza da percorrere lungo z
                    
                    double period = distance_max(distance_x,distance_y,distance_z) / Vmax; //periodo = distanza max / Vmax 

                    std::vector<std::vector<double>> poly ; 
                    poly.resize(Npunti) ; 

                    double DeltaT = period/Npunti ; 
                    
                    for(int i=0;i<Npunti;i++) {
                        for(int j=0;j<Ncoefficients;j++) {
                            target[0] += coeff.coefficients_x[j]*pow(DeltaT*(i+1),j) ; 
                            target[1] += coeff.coefficients_y[i]*pow(DeltaT*(i+1),j) ; 
                            target[2] += coeff.coefficients_z[i]*pow(DeltaT*(i+1),j) ; 
                        }
                        for(int k=3;k<7;k++) {
                            target[k]=pos_fin[k] ; 
                        }
                        poly[i]= target ; 
                    }
return poly ; 
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

void print_target(int N,std::vector<double> vect) {
    for(int i=0;i<N;i++) {
        std::cout <<vect[i] ; 
    }
    std::cout <<std::endl ; 
    
}


int main(int argc,char **argv) {

    coefficients coeff_poly5 ; 

    name.resize(NumJointState) ; 
    joint_pos_initial.resize(NumJointState) ; 
    pos_final.resize(NumJointState) ;    
    pos_initial.resize(NumJointState) ; 
    target.resize(NumJointState) ; 
    coeff_poly5.coefficients_x.resize(Ncoefficients) ;    
    coeff_poly5.coefficients_y.resize(Ncoefficients) ;    
    coeff_poly5.coefficients_z.resize(Ncoefficients) ;   

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

    while(ros::ok()) {
        switch(state) {
            case 0: {
                //state: init 
                state = 1 ; 
            }
            case 1: {
                state = 2 ; 
            }
            case 2: {
                state = 3 ; 
            }
            case 3: {
                //calcolo dei coefficienti 
                calc_coefficients(&coeff_poly5,pos_initial,joint_pos_initial,pos_final) ; 
                state = 4 ; 
            }
            case 4: {
                //calcolo punti traiettoria 
                poly5 = trajectory_points(N_punti,pos_initial,pos_final,coeff_poly5) ; 
                state = 0 ; 
            }
        }
        ros::spinOnce() ; 
        loop_rate.sleep() ; 
    }
    ros::spin() ; 

    for(int i=0;i<Ncoefficients;i++) {
        std::cout <<coeff_poly5.coefficients_x[i] <<" "; 
        std::cout <<coeff_poly5.coefficients_y[i] <<" ";
        std::cout <<coeff_poly5.coefficients_z[i] <<std::endl ; 
    }

    for(int i=0;i<N_punti;i++) {
        print_target(N_punti,poly5[i]) ; 

    }

return 0 ; 
}

