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

std::vector<double> target ; 
std::vector<double> joint_target ; 

std::vector<std::vector<double>> bezier ;

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

std::vector<double> PointOnCubicBezier(coefficients *coeff,std::vector<double> pos_init,std::vector<double>joint_pos_init,std::vector<double> pos_fin,float t) {
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

    // POS_CTRL_1 E POS_CTRL_2 SONO LE POSIZIONI DI CONTROLLO 
    //DELLA POLINOMIALE, ANCORA NON DICHIARATE NEL CODICE

    std::vector<double> pos_ctrl_1 ; 
    std::vector<double> pos_ctrl_2 ; 
    pos_ctrl_1.resize(NumJointState) ; 
    pos_ctrl_2.resize(NumJointState) ; 

    coeff->coefficients_x[2] = 3.0 *(pos_ctrl_1[0] - pos_init[0]) ; 
    coeff->coefficients_x[1] = 3.0 *(pos_ctrl_2[0] - pos_ctrl_1[0]) - coeff->coefficients_x[2] ; 
    coeff->coefficients_x[0] = pos_fin[0] - pos_init[0] - coeff->coefficients_x[2] - coeff->coefficients_x[1] ; 

    coeff->coefficients_y[2] = 3.0 * (pos_ctrl_1[1] - pos_init[1]) ; 
    coeff->coefficients_y[1] = 3.0 * (pos_ctrl_2[1] - pos_ctrl_1[1]) - coeff->coefficients_y[2] ; 
    coeff->coefficients_y[0] = pos_fin[1] - pos_init[1] - coeff->coefficients_y[2] - coeff->coefficients_y[1] ; 

    coeff->coefficients_z[2] = 3.0 * (pos_ctrl_1[2] - pos_init[2]) ; 
    coeff->coefficients_z[1] = 3.0 * (pos_ctrl_2[2] - pos_ctrl_1[2]) - coeff->coefficients_z[2] ; 
    coeff->coefficients_z[0] = pos_fin[2] - pos_init[2] - coeff->coefficients_z[2] - coeff->coefficients_z[1] ; 

    //CALCOLO DEL PUNTO DELLA CURVA IN RELAZIONE A t 

    float tSquared = t * t ; 
    float tCubed = tSquared * t ; 

    std::vector<double> result ; 
    result.resize(NumJointState) ; 

    result[0] = (coeff->coefficients_x[0] * tCubed) + (coeff->coefficients_x[1] * tSquared) + (coeff->coefficients_x[2] * t) + pos_init[0] ; 
    result[1] = (coeff->coefficients_y[0] * tCubed) + (coeff->coefficients_y[1] * tSquared) + (coeff->coefficients_y[2] * t) + pos_init[1] ; 
    result[2] = (coeff->coefficients_z[0] * tCubed) + (coeff->coefficients_z[1] * tSquared) + (coeff->coefficients_z[2] * t) + pos_init[2] ; 

return result ; 
}

int main(int argc,char **argv) {
    
}


