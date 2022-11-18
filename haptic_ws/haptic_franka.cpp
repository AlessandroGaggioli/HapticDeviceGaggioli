#include "ros/ros.h"
#include "tf/transform_broadcaster.h"
#include "sensor_msgs/JointState.h"
//#include "franka_core_msgs/JointCommand.h"
/*#include "panda_ik/pandaIk.h"
#include "panda_ik/pandaFk.h" */
#include <iostream>
#include <Eigen/Dense>
#include <kdl/frames.hpp>
#include <string>
#include <cmath>
#include <tf2_ros/transform_listener.h>
#include <geometry_msgs/TransformStamped.h>
#include "geometry_msgs/PointStamped.h" 
#include "tf2_ros/message_filter.h"
#include "message_filters/subscriber.h"
#include "tf2_geometry_msgs/tf2_geometry_msgs.h"

#define frequence 50

ros::Subscriber sub_haptic_joints  ; 
ros::Subscriber sub_haptic_pose ; 
ros::Subscriber sub_static_transform ; 

std::vector<double> haptic_joints ; 
std::vector<double> haptic_pose ; 

void GeomagicJointsCallback(const sensor_msgs::JointState& msg) {
    //---------------------------------------------------------
    // callback del subscriber per leggere i giunti dell'haptic 
    //----------------------------------------------------------
    for(int i=0;i<6;i++) {
        haptic_joints[i]=msg.position[i] ; 
    }
}

void GeomagicPoseCallback(const sensor_msgs::JointState& msg)  {
    //---------------------------------------------------------
    // callback del subscriber per leggere le posizioni dell'haptic 
    //----------------------------------------------------------
    for(int i=0;i<3;i++) {
        haptic_pose[i]=msg.position[i] ; 
       // std::cout <<haptic_pose[i] <<std::endl ; 
    }
}

Eigen::MatrixXd MDH(double theta,double alfa,double d,double a) {ù
    //-----------------------------------------------------------
    //funzione che genera la matrice cinematica sui parametri DH
    //-----------------------------------------------------------
    Eigen::MatrixXd DH(4,4) ; 
    DH(0,0) = cos(theta) ; 
    DH(0,1) = -sin(theta)*cos(alfa) ; 
    DH(0,2) = sin(theta)*sin(alfa) ; 
    DH(0,3) = a*cos(theta) ; 
    DH(1,0) = sin(theta) ; 
    DH(1,1) = cos(theta)*cos(alfa) ; 
    DH(1,2) = -cos(theta)*sin(alfa) ; 
    DH(1,3) = a*sin(theta) ; 
    DH(2,0) = 0 ; 
    DH(3,0) = 0 ;
    DH(3,1) = 0 ; 
    DH(3,2) = 0 ; 
    DH(2,1) = sin(alfa) ; 
    DH(2,2) = cos(alfa) ; 
    DH(2,3) = d ; 
    DH(3,3) = 1 ; 

return DH ; 
}

std::vector<double> ConvertWorkspace(std::vector<double> robot_pos,std::vector<double>haptic_pos,std::string mode ) {
    //------------------------------------------
    //funzione per convertire le posizioni x,y,z haptic e robot. Per passare da un workspace all'altro
    //-----------------------------------------

    std::vector<double> converted_pose ; 
    std::vector<double> temp ; 
    converted_pose.resize(7) ; 
    temp.resize(3) ; 

    /* converto le posizioni da haptic a robot 
        (Xfranka = Zhaptic ; Yfranka = Yhaptic; Zfranka=-Xhaptic)
        e da robot ad haptic */

    if(mode=="haptic_to_robot") {
        temp[0] = haptic_pos[2] ; 
        temp[1] = haptic_pos[1] ; 
        temp[2] = -haptic_pos[0] ; 
         for(int i=0;i<3;i++) converted_pose[i] = temp[i] ;
    }
    else if(mode=="robot_to_haptic") {
        temp[0] = -robot_pos[2] ; 
        temp[1] = robot_pos[1] ; 
        temp[2] = robot_pos[0] ; 

        for(int i=0;i<3;i++) converted_pose[i] = temp[i] ;
    }

return converted_pose ; 
}

std::vector<double> OffsetConvertWorkspace(std::vector<double> robot_pos,std::vector<double> haptic_pos) {
    //-------------------------------------------------------------------------------
    //funzione che calcola gli offset tra la posizione di franka e quella dell'haptic
    //------------------------------------------------------------------------------

    std::vector<double> offset ; 
    offset.resize(3) ; 
    std::vector<double> franka_offset ; 
    franka_offset.resize(7) ; 

    for(int i=0;i<3;i++) {
        offset[i] = robot_pos[i] - haptic_pos[i] ; 
        franka_offset[i] -= offset[i] ; 
    }
return franka_offset ; 
}

std::vector<double> ConvertOrientation(std::vector<double> haptic_joint) {

    //-----------------------------------------
    //funzione che converte l'orientamento dell'haptic rendendolo concorde a quello di franka
    //-----------------------------------------

    haptic_joint[3] -= 3.06095 ; 
    haptic_joint[4] -= -0.954675 ; 
    haptic_joint[5] -= 2.9704 ; 

    std::vector<double> alfa = {1.5708,0,-1.5708,-1.5708,+1.5708,0} ; 
    std::vector<double> a = {0,0.13335,0,0.13335,0,0} ; 
    std::vector<double> d = {0.11,0,0,0,0,0} ; 

    std::vector<Eigen::MatrixXd> DH_Matrix ; 
    DH_Matrix.resize(6) ; 

    for(int i=0;i<6;i++) {
        DH_Matrix[i]=MDH(haptic_joint[i],alfa[i],d[i],a[i]) ; 
    }
    Eigen::MatrixXd RotationMatrix(4,4) ;
    RotationMatrix = DH_Matrix[0] * DH_Matrix[1] ; 
    for(int i=2;i<6;i++) {
        RotationMatrix = RotationMatrix * DH_Matrix[i] ; 
    }

    Eigen::MatrixXd Rot_y_meno90(4,4); 

    Rot_y_meno90(2,0)=1 ; 
    Rot_y_meno90(1,1) = 1  ; 
    Rot_y_meno90(0,2) = -1 ; 

    //--- prodotto matriciale tra orientamento rispetto haptic e matrice di trasformazione --------------------------
    Eigen::MatrixXd  Orientation_EndEffectorRobot(4,4) ;  
    Orientation_EndEffectorRobot = Rot_y_meno90 * RotationMatrix  ; 

    //calcolo quaternione corrispondente all'orientamento 
    std::vector<double> quaternion ; 
    quaternion.resize(4) ;

    std::vector<double> R = {Orientation_EndEffectorRobot(0,0),Orientation_EndEffectorRobot(0,1),Orientation_EndEffectorRobot(0,2),Orientation_EndEffectorRobot(1,0),Orientation_EndEffectorRobot(1,1),Orientation_EndEffectorRobot(1,2),Orientation_EndEffectorRobot(2,0),Orientation_EndEffectorRobot(2,1),Orientation_EndEffectorRobot(2,2),Orientation_EndEffectorRobot(3,1),Orientation_EndEffectorRobot(3,2),Orientation_EndEffectorRobot(3,3)} ; 
    KDL::Rotation Rot ; 
    for(int i=0;i<9;i++) {
        Rot.data[i]=R[i]; 
    }
    Rot.GetQuaternion(quaternion[0],quaternion[1],quaternion[2],quaternion[3] ) ; 
    
 return quaternion ; 
}

int main(int argc,char **argv) {

    haptic_joints.resize(6) ; 
    haptic_pose.resize(3) ;
    std::vector<double> quaternion ; 
    quaternion.resize(4) ; 

    ros::init(argc,argv,"haptic_franka") ; 
    ros::NodeHandle n ; 
    ros::Rate loop_rate(frequence) ; 

    tf2_ros::Buffer tfBuffer ; 
    tf2_ros::TransformListener tfListener(tfBuffer) ;
    ros::Rate rate(10.0) ; 


    sub_haptic_joints = n.subscribe("Geomagic/joint_states",1,GeomagicJointsCallback) ; 
    sub_haptic_pose = n.subscribe("Geomagic/end_effector_pose",1,GeomagicPoseCallback) ; 

    std::vector<double> franka_pose ; 
    franka_pose.resize(7) ; 
    
    std::vector<double> haptic_franka_pose ; 
    haptic_franka_pose.resize(7) ;     

    std::vector<double> offset_franka_pose ; 
    offset_franka_pose.resize(7) ; 
    
    while(ros::ok()){

    geometry_msgs::TransformStamped transformStamped ;
                try{
                    transformStamped = tfBuffer.lookupTransform("panda_link0","panda_hand",ros::Time(0)) ;   
                }
                catch (tf2::TransformException &ex) {
                    ROS_WARN("%s",ex.what()) ; 
                    ros::Duration(1.0).sleep() ; 
                    continue ; 
                }

                franka_pose[0] = transformStamped.transform.translation.x ;
                franka_pose[1] = transformStamped.transform.translation.y ;
                franka_pose[2] = transformStamped.transform.translation.z ; 
                franka_pose[3] = transformStamped.transform.rotation.x ;
                franka_pose[4] = transformStamped.transform.rotation.y  ;
                franka_pose[5] = transformStamped.transform.rotation.z ;
                franka_pose[6] = transformStamped.transform.rotation.w ;

    quaternion = ConvertOrientation(haptic_joints) ; 
    haptic_franka_pose = ConvertWorkspace(haptic_franka_pose,haptic_pose,"haptic_to_robot") ; 
    for(int i=3;i<7;i++) {
        haptic_franka_pose[i] = quaternion[i-3] ; 
    }
    
    offset_franka_pose = OffsetConvertWorkspace(franka_pose,haptic_pose) ; 
    for(int i=3;i<7;i++) {
        offset_franka_pose[i] = quaternion[i-3] ; 
    }

    std::cout <<"HAPTIC_FRANKA POSE \n" ; 
    for(int i=0;i<7;i++) {
        std::cout <<haptic_franka_pose[i] <<std::endl ; 
    }    

    static tf::TransformBroadcaster br ; 
    tf::Transform transform ; 
    transform.setOrigin(tf::Vector3(haptic_franka_pose[0]/100,haptic_franka_pose[1]/100,haptic_franka_pose[2]/100)) ; 
   // transform.setOrigin(tf::Vector3(1,1,1))  ; 
    tf::Quaternion q(haptic_franka_pose[3],haptic_franka_pose[4],haptic_franka_pose[5],haptic_franka_pose[6]); 
  //  tf::Quaternion q(quaternion[0],quaternion[1],quaternion[2],quaternion[3]); 
    transform.setRotation(q) ; 
    transform.setRotation(q) ; 
    br.sendTransform(tf::StampedTransform(transform, ros::Time::now(),"panda_link0","EndEffector")) ; 


    ros::spinOnce() ; 
    loop_rate.sleep() ;
    }

return 0 ; 
}
