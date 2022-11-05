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

void ProdottoMatrici(double M1[3][3],double M2[3][3],double prodotto[3][3]) {
    int k ; 
    for(int i=0;i<3;i++) {
        for(int j=0;j<3;j++) {
            prodotto[i][j] =0 ; 
            for(k=0;k<3;k++) {
                prodotto[i][j] += M1[i][k] * M2[k][j] ; 
            }
        }
    }
} 

 double sgn(double a) {
        double ret  ; 
        if(a>=0) ret = 1.0 ; 
        else ret = -1.0 ; 
    return ret ; 
    }

std::vector<double> ConvertOrientation(std::vector<double> haptic_joint,std::vector<double> pos_robot) {

    //--- calcolo orientamento end effector rispetto haptic ------------------------------------
    double q1 = haptic_joint[0] ; 
    double q2 = haptic_joint[1] ; 
    double q3 = haptic_joint[2] ;
    double q4 =  haptic_joint[3] ; 
    double q5 = haptic_joint[4] ;
    double q6 = haptic_joint[5]  ;
    double RotationMatrix_EndEffectorHaptic[3][3] ;  
    RotationMatrix_EndEffectorHaptic[0][0] = - cos(q6)*(sin(q1)*sin(q5) + cos(q5)*(cos(q4)*(cos(q1)*sin(q2)*sin(q3) - cos(q1)*cos(q2)*cos(q3)) + sin(q4)*(cos(q1)*cos(q2)*sin(q3) + cos(q1)*cos(q3)*sin(q2)))) - sin(q6)*(cos(q4)*(cos(q1)*cos(q2)*sin(q3) + cos(q1)*cos(q3)*sin(q2)) - sin(q4)*(cos(q1)*sin(q2)*sin(q3) - cos(q1)*cos(q2)*cos(q3))) ;   
    RotationMatrix_EndEffectorHaptic[0][1] = sin(q6)*(sin(q1)*sin(q5) + cos(q5)*(cos(q4)*(cos(q1)*sin(q2)*sin(q3) - cos(q1)*cos(q2)*cos(q3)) + sin(q4)*(cos(q1)*cos(q2)*sin(q3) + cos(q1)*cos(q3)*sin(q2)))) - cos(q6)*(cos(q4)*(cos(q1)*cos(q2)*sin(q3) + cos(q1)*cos(q3)*sin(q2)) - sin(q4)*(cos(q1)*sin(q2)*sin(q3) - cos(q1)*cos(q2)*cos(q3)));  cos(q5)*sin(q1) - sin(q5)*(cos(q4)*(cos(q1)*sin(q2)*sin(q3) - cos(q1)*cos(q2)*cos(q3)) + sin(q4)*(cos(q1)*cos(q2)*sin(q3) + cos(q1)*cos(q3)*sin(q2))), (0.1333*cos(q1)*cos(q2)) - (0.1333*cos(q1)*sin(q2)*sin(q3)) + (0.1333*cos(q1)*cos(q2)*cos(q3)) ;  
    RotationMatrix_EndEffectorHaptic[0][2] = cos(q5)*sin(q1) - sin(q5)*(cos(q4)*(cos(q1)*sin(q2)*sin(q3) - cos(q1)*cos(q2)*cos(q3)) + sin(q4)*(cos(q1)*cos(q2)*sin(q3) + cos(q1)*cos(q3)*sin(q2))) ; 
    RotationMatrix_EndEffectorHaptic[1][0] = cos(q6)*(cos(q1)*sin(q5) - cos(q5)*(cos(q4)*(sin(q1)*sin(q2)*sin(q3) - cos(q2)*cos(q3)*sin(q1)) + sin(q4)*(cos(q2)*sin(q1)*sin(q3) + cos(q3)*sin(q1)*sin(q2)))) - sin(q6)*(cos(q4)*(cos(q2)*sin(q1)*sin(q3) + cos(q3)*sin(q1)*sin(q2)) - sin(q4)*(sin(q1)*sin(q2)*sin(q3) - cos(q2)*cos(q3)*sin(q1))); 
    RotationMatrix_EndEffectorHaptic[1][1] = - sin(q6)*(cos(q1)*sin(q5) - cos(q5)*(cos(q4)*(sin(q1)*sin(q2)*sin(q3) - cos(q2)*cos(q3)*sin(q1)) + sin(q4)*(cos(q2)*sin(q1)*sin(q3) + cos(q3)*sin(q1)*sin(q2)))) - cos(q6)*(cos(q4)*(cos(q2)*sin(q1)*sin(q3) + cos(q3)*sin(q1)*sin(q2)) - sin(q4)*(sin(q1)*sin(q2)*sin(q3) - cos(q2)*cos(q3)*sin(q1))); 
    RotationMatrix_EndEffectorHaptic[1][2] = - cos(q1)*cos(q5) - sin(q5)*(cos(q4)*(sin(q1)*sin(q2)*sin(q3) - cos(q2)*cos(q3)*sin(q1)) + sin(q4)*(cos(q2)*sin(q1)*sin(q3) + cos(q3)*sin(q1)*sin(q2))); 
    RotationMatrix_EndEffectorHaptic[2][0] = sin(q6)*(cos(q4)*(cos(q2)*cos(q3) - sin(q2)*sin(q3)) - sin(q4)*(cos(q2)*sin(q3) + cos(q3)*sin(q2))) + cos(q5)*cos(q6)*(cos(q4)*(cos(q2)*sin(q3) + cos(q3)*sin(q2)) + sin(q4)*(cos(q2)*cos(q3) - sin(q2)*sin(q3)));  
    RotationMatrix_EndEffectorHaptic[2][1] = cos(q6)*(cos(q4)*(cos(q2)*cos(q3) - sin(q2)*sin(q3)) - sin(q4)*(cos(q2)*sin(q3) + cos(q3)*sin(q2))) - cos(q5)*sin(q6)*(cos(q4)*(cos(q2)*sin(q3) + cos(q3)*sin(q2)) + sin(q4)*(cos(q2)*cos(q3) - sin(q2)*sin(q3)));                                                                             
    RotationMatrix_EndEffectorHaptic[2][2] =  sin(q5)*(cos(q4)*(cos(q2)*sin(q3) + cos(q3)*sin(q2)) + sin(q4)*(cos(q2)*cos(q3) - sin(q2)*sin(q3))) ;       

    //------------------------------------------------------------------------------------------
    /*--- matrice di trasformazione orientamento haptic - robot, 
    che rende l'orientamento dell'haptic "concorde" con quello del robot : 
    
    ----------------------------------------------------------------------------------------------------------  */
    double RotationMatrix_Haptic_Robot[3][3] ; 
    for(int i=0;i<3;i++) {
        for(int j=0;j<3;j++) {
            RotationMatrix_Haptic_Robot[i][j] = 0 ; 
            if((i==0 && j==2)||(i==1 && j==0)||(i==2 && j==1)) RotationMatrix_Haptic_Robot[i][j] = 1 ; 
        }
    }

    double Rot_y_90[3][3] ; 
    for(int i=0;i<3;i++) {
        for(int j=0;j<3;j++) {
            Rot_y_90[i][j]=0 ; 
            if((i==0 && j==2)||(i==1 && j==1)) Rot_y_90[i][j] = 1 ; 
            else if((i==2 && j==0)) Rot_y_90[i][j] = -1 ; 
        }
    } 

    //--- prodotto matriciale tra orientamento rispetto haptic e matrice di trasformazione --------------------------
    double Orientation_EndEffectorRobot[3][3] ; 
    double temp[3][3] ; 
    double temp2[3][3] ; 
    
    ProdottoMatrici(RotationMatrix_Haptic_Robot,RotationMatrix_EndEffectorHaptic,temp) ; 
    ProdottoMatrici(Rot_y_90,temp,temp2) ; 
    ProdottoMatrici(Rot_y_90,temp2,Orientation_EndEffectorRobot) ; 
 
    //calcolo quaternione corrispondente all'orientamento 
    std::vector<double> quaternion ; 
    quaternion.resize(4) ; 
    quaternion[3] = 0.5 * sqrt(Orientation_EndEffectorRobot[0][0]+Orientation_EndEffectorRobot[1][1]+Orientation_EndEffectorRobot[2][2]+1) ; 
    quaternion[0] = 0.5 * sgn(Orientation_EndEffectorRobot[2][1]-Orientation_EndEffectorRobot[1][2]) * sqrt(Orientation_EndEffectorRobot[0][0]-Orientation_EndEffectorRobot[1][1]-Orientation_EndEffectorRobot[2][2]+1) ; 
    quaternion[1] = 0.5 * sgn(Orientation_EndEffectorRobot[0][2]-Orientation_EndEffectorRobot[2][0]) * sqrt(Orientation_EndEffectorRobot[1][1]-Orientation_EndEffectorRobot[2][2]-Orientation_EndEffectorRobot[0][0]+1) ; 
    quaternion[2] = 0.5 * sgn(Orientation_EndEffectorRobot[1][0]-Orientation_EndEffectorRobot[0][1]) * sqrt(Orientation_EndEffectorRobot[2][2]-Orientation_EndEffectorRobot[0][0]-Orientation_EndEffectorRobot[1][1]+1) ; 

    
 return quaternion ; 
}

int main(int argc,char **argv) {
    std::vector<double> haptic_joint = {-0,0.26888954639434814, -0.6397024393081665,4.280513318377086, -3.1470788061599047, 2.3388831337266645} ; 
    std::vector<double> robot_pos = {0.306912 , -1.03551e-05 , 0.590178 , -1, -0.00019153, 0.000497322, 6.63308e-06} ; 

    std::vector<double> quaternion ; 
    quaternion.resize(4) ; 
    quaternion = ConvertOrientation(haptic_joint,robot_pos) ; 

    std::cout <<"QUATERNION_ORIENTATION \n" ; 
    for(int i=0;i<4;i++) {
        std::cout <<quaternion[i] <<std::endl ; 
    }

return 0 ; 
}