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

void ProdottoMatrici(double M1[3][3],double M2[3][3],double prodotto[3][3],int n) {
    int k ; 
    for(int i=0;i<n;i++) {
        for(int j=0;j<n;j++) {
            prodotto[i][j] =0 ; 
            for(k=0;k<n;k++) {
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
    double RotationMatrix_EndEffectorHaptic[3][3] ;  
    RotationMatrix_EndEffectorHaptic[0][0] = cos(q1)*cos(q2)*cos(q3) - cos(q1)*sin(q2)*sin(q3) ; 
    RotationMatrix_EndEffectorHaptic[0][1] = -cos(q1)*cos(q2)*sin(q3)-cos(q1)*cos(q3)*sin(q2) ; 
    RotationMatrix_EndEffectorHaptic[0][2] = sin(q1) ; 
    RotationMatrix_EndEffectorHaptic[1][0] = cos(q2)*cos(q3)*sin(q1) - sin(q1)*sin(q2)*sin(q3); 
    RotationMatrix_EndEffectorHaptic[1][1] = -cos(q2)*sin(q1)*sin(q3)-cos(q3)*sin(q1)*sin(q2) ; 
    RotationMatrix_EndEffectorHaptic[1][2] = -cos(q1) ; 
    RotationMatrix_EndEffectorHaptic[2][0] = cos(q2)*sin(q3) + cos(q3)*sin(q2) ; 
    RotationMatrix_EndEffectorHaptic[2][1] = cos(q2)*cos(q3) - sin(q2) * sin(q3) ; 
    RotationMatrix_EndEffectorHaptic[2][2] = 0 ; 

    //------------------------------------------------------------------------------------------
    /*--- matrice di trasformazione orientamento haptic - robot, 
    che rende l'orientamento dell'haptic "concorde" con quello del robot : 

    R = [0 1 0 ; 0 0 1 ; 1 0 0]^T = Rot(x,-90°) * Rot(z,-90°) 
    
    ----------------------------------------------------------------------------------------------------------  */
    double RotationMatrix_Haptic_Robot[3][3] ; 
    for(int i=0;i<3;i++) {
        for(int j=0;j<3;j++) {
            RotationMatrix_Haptic_Robot[i][j] = 0 ; 
            if((i==0 && j==1) || (i==1 && j==2) || (i==2 && j==0)) RotationMatrix_Haptic_Robot[i][j] = 1 ; 
        }
    }
    //--- prodotto matriciale tra orientamento rispetto haptic e matrice di trasformazione --------------------------
    double Orientation_EndEffectorRobot[3][3] ; 
    ProdottoMatrici(RotationMatrix_Haptic_Robot,RotationMatrix_EndEffectorHaptic,Orientation_EndEffectorRobot,3) ; 

    //calcolo quaternione corrispondente all'orientamento 
    std::vector<double> quaternion ; 
    quaternion.resize(4) ; 
    quaternion[3] = 0.5 * sqrt(Orientation_EndEffectorRobot[0][0]+Orientation_EndEffectorRobot[1][1]+Orientation_EndEffectorRobot[2][2]+1) ; 
    quaternion[0] = 0.5 * sgn(Orientation_EndEffectorRobot[2][1]-Orientation_EndEffectorRobot[1][2]) * sqrt(Orientation_EndEffectorRobot[0][0]-Orientation_EndEffectorRobot[1][1]-Orientation_EndEffectorRobot[2][2]+1) ; 
    quaternion[1] = 0.5 * sgn(Orientation_EndEffectorRobot[0][2]-Orientation_EndEffectorRobot[2][1]) * sqrt(Orientation_EndEffectorRobot[1][1]-Orientation_EndEffectorRobot[2][2]-Orientation_EndEffectorRobot[0][0]+1) ; 
    quaternion[2] = 0.5 * sgn(Orientation_EndEffectorRobot[1][0]-Orientation_EndEffectorRobot[0][1]) * sqrt(Orientation_EndEffectorRobot[2][2]-Orientation_EndEffectorRobot[0][0]-Orientation_EndEffectorRobot[1][1]+1) ; 
 

    //---------------------------------------------------------------------------------------------------------------
    //--- prodotto matriciale tra matrice trasformazione end effector-base robot-------------------------------------
    /*          robot_pos_link0[3] = transformStamped.transform.rotation.x ;
                robot_pos_link0[4] = transformStamped.transform.rotation.y  ;
                robot_pos_link0[5] = transformStamped.transform.rotation.z ;
                robot_pos_link0[6] = transformStamped.transform.rotation.w ; */ 
    /* double RotationMatrix_EndEffectorRobot[3][3] ; 
    double x = pos_robot[3] ; 
    double y = pos_robot[4] ; 
    double z = pos_robot[5] ; 
    double w = pos_robot[6] ; 
    RotationMatrix_EndEffectorRobot[0][0] = 1-2*y*y-2*z*z ; 
    RotationMatrix_EndEffectorRobot[0][1] = 2*x*y-2*w*z ; 
    RotationMatrix_EndEffectorRobot[0][2] = 2*x*z + 2*w*y ; 
    RotationMatrix_EndEffectorRobot[1][0] = 2*x*y + 2*w*z ; 
    RotationMatrix_EndEffectorRobot[1][1] = 1-2*x*x-2*z*z ; 
    RotationMatrix_EndEffectorRobot[1][2] = 2*y*z - 2*w*z ; 
    RotationMatrix_EndEffectorRobot[2][0] = 2*x*z - 2*w*y ; 
    RotationMatrix_EndEffectorRobot[2][1] = 2*y*z + 2*w*x ; 
    RotationMatrix_EndEffectorRobot[2][2] = 1-2*x*x-2*y*y ; 
    std::vector<double> Orientation_Robot[3][3] ; 
    ProdottoMatrici(Orientation_EndEffectorRobot,RotationMatrix_EndEffectorRobot,Orientation_Robot,3) ; 
    //----------------------------------------------------------------------------------------------------------
    std::vector<double> quaternion ; 
    quaternion.resize(4) ; 
    quaternion[3] = 0.5 * sqrt(Orientation_Robot[0][0]+Orientation_Robot[1][1]+Orientation_Robot[2][2]+1) ; 
    quaternion[0] = 0.5 * sgn(Orientation_Robot[2][1]-Orientation_Robot[1][2]) * sqrt(Orientation_Robot[0][0]-Orientation_Robot[1][1]-Orientation_Robot[2][2]+1) ; 
    quaternion[1] = 0.5 * sgn(Orientation_Robot[0][2]-Orientation_Robot[2][1]) * sqrt(Orientation_Robot[1][1]-Orientation_Robot[2][2]-Orientation_Robot[0][0]+1) ; 
    quaternion[2] = 0.5 * sgn(Orientation_Robot[1][0]-Orientation_Robot[0][1]) * sqrt(Orientation_Robot[2][2]-Orientation_Robot[0][0]Orientation_Robot[1][1]+1) ; */
 return quaternion ; 
}

int main(int argc,char **argv) {
    std::vector<double> haptic_joint = {0,0,0} ; 
    std::vector<double> robot_pos = {0.306912 , -1.03551e-05 , 0.590178 , -1, -0.00019153, 0.000497322, 6.63308e-06} ; 

    std::vector<double> quaternion ; 
    quaternion.resize(4) ; 
    quaternion = ConvertOrientation(haptic_joint,robot_pos) ; 

    for(int i=0;i<4;i++) {
        std::cout <<quaternion[i] <<std::endl ; 
    }

return 0 ; 
}