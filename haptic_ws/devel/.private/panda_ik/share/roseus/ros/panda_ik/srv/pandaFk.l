;; Auto-generated. Do not edit!


(when (boundp 'panda_ik::pandaFk)
  (if (not (find-package "PANDA_IK"))
    (make-package "PANDA_IK"))
  (shadow 'pandaFk (find-package "PANDA_IK")))
(unless (find-package "PANDA_IK::PANDAFK")
  (make-package "PANDA_IK::PANDAFK"))
(unless (find-package "PANDA_IK::PANDAFKREQUEST")
  (make-package "PANDA_IK::PANDAFKREQUEST"))
(unless (find-package "PANDA_IK::PANDAFKRESPONSE")
  (make-package "PANDA_IK::PANDAFKRESPONSE"))

(in-package "ROS")

(if (not (find-package "SENSOR_MSGS"))
  (ros::roseus-add-msgs "sensor_msgs"))


(if (not (find-package "GEOMETRY_MSGS"))
  (ros::roseus-add-msgs "geometry_msgs"))


(defclass panda_ik::pandaFkRequest
  :super ros::object
  :slots (_reference_joints ))

(defmethod panda_ik::pandaFkRequest
  (:init
   (&key
    ((:reference_joints __reference_joints) (instance sensor_msgs::JointState :init))
    )
   (send-super :init)
   (setq _reference_joints __reference_joints)
   self)
  (:reference_joints
   (&rest __reference_joints)
   (if (keywordp (car __reference_joints))
       (send* _reference_joints __reference_joints)
     (progn
       (if __reference_joints (setq _reference_joints (car __reference_joints)))
       _reference_joints)))
  (:serialization-length
   ()
   (+
    ;; sensor_msgs/JointState _reference_joints
    (send _reference_joints :serialization-length)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; sensor_msgs/JointState _reference_joints
       (send _reference_joints :serialize s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; sensor_msgs/JointState _reference_joints
     (send _reference_joints :deserialize buf ptr-) (incf ptr- (send _reference_joints :serialization-length))
   ;;
   self)
  )

(defclass panda_ik::pandaFkResponse
  :super ros::object
  :slots (_solution ))

(defmethod panda_ik::pandaFkResponse
  (:init
   (&key
    ((:solution __solution) (instance geometry_msgs::Pose :init))
    )
   (send-super :init)
   (setq _solution __solution)
   self)
  (:solution
   (&rest __solution)
   (if (keywordp (car __solution))
       (send* _solution __solution)
     (progn
       (if __solution (setq _solution (car __solution)))
       _solution)))
  (:serialization-length
   ()
   (+
    ;; geometry_msgs/Pose _solution
    (send _solution :serialization-length)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; geometry_msgs/Pose _solution
       (send _solution :serialize s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; geometry_msgs/Pose _solution
     (send _solution :deserialize buf ptr-) (incf ptr- (send _solution :serialization-length))
   ;;
   self)
  )

(defclass panda_ik::pandaFk
  :super ros::object
  :slots ())

(setf (get panda_ik::pandaFk :md5sum-) "cf41e0feb1f85dd54246ca565d37eb4f")
(setf (get panda_ik::pandaFk :datatype-) "panda_ik/pandaFk")
(setf (get panda_ik::pandaFk :request) panda_ik::pandaFkRequest)
(setf (get panda_ik::pandaFk :response) panda_ik::pandaFkResponse)

(defmethod panda_ik::pandaFkRequest
  (:response () (instance panda_ik::pandaFkResponse :init)))

(setf (get panda_ik::pandaFkRequest :md5sum-) "cf41e0feb1f85dd54246ca565d37eb4f")
(setf (get panda_ik::pandaFkRequest :datatype-) "panda_ik/pandaFkRequest")
(setf (get panda_ik::pandaFkRequest :definition-)
      "sensor_msgs/JointState reference_joints

================================================================================
MSG: sensor_msgs/JointState
# This is a message that holds data to describe the state of a set of torque controlled joints. 
#
# The state of each joint (revolute or prismatic) is defined by:
#  * the position of the joint (rad or m),
#  * the velocity of the joint (rad/s or m/s) and 
#  * the effort that is applied in the joint (Nm or N).
#
# Each joint is uniquely identified by its name
# The header specifies the time at which the joint states were recorded. All the joint states
# in one message have to be recorded at the same time.
#
# This message consists of a multiple arrays, one for each part of the joint state. 
# The goal is to make each of the fields optional. When e.g. your joints have no
# effort associated with them, you can leave the effort array empty. 
#
# All arrays in this message should have the same size, or be empty.
# This is the only way to uniquely associate the joint name with the correct
# states.


Header header

string[] name
float64[] position
float64[] velocity
float64[] effort

================================================================================
MSG: std_msgs/Header
# Standard metadata for higher-level stamped data types.
# This is generally used to communicate timestamped data 
# in a particular coordinate frame.
# 
# sequence ID: consecutively increasing ID 
uint32 seq
#Two-integer timestamp that is expressed as:
# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')
# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')
# time-handling sugar is provided by the client library
time stamp
#Frame this data is associated with
string frame_id
---
geometry_msgs/Pose solution

================================================================================
MSG: geometry_msgs/Pose
# A representation of pose in free space, composed of position and orientation. 
Point position
Quaternion orientation

================================================================================
MSG: geometry_msgs/Point
# This contains the position of a point in free space
float64 x
float64 y
float64 z

================================================================================
MSG: geometry_msgs/Quaternion
# This represents an orientation in free space in quaternion form.

float64 x
float64 y
float64 z
float64 w
")

(setf (get panda_ik::pandaFkResponse :md5sum-) "cf41e0feb1f85dd54246ca565d37eb4f")
(setf (get panda_ik::pandaFkResponse :datatype-) "panda_ik/pandaFkResponse")
(setf (get panda_ik::pandaFkResponse :definition-)
      "sensor_msgs/JointState reference_joints

================================================================================
MSG: sensor_msgs/JointState
# This is a message that holds data to describe the state of a set of torque controlled joints. 
#
# The state of each joint (revolute or prismatic) is defined by:
#  * the position of the joint (rad or m),
#  * the velocity of the joint (rad/s or m/s) and 
#  * the effort that is applied in the joint (Nm or N).
#
# Each joint is uniquely identified by its name
# The header specifies the time at which the joint states were recorded. All the joint states
# in one message have to be recorded at the same time.
#
# This message consists of a multiple arrays, one for each part of the joint state. 
# The goal is to make each of the fields optional. When e.g. your joints have no
# effort associated with them, you can leave the effort array empty. 
#
# All arrays in this message should have the same size, or be empty.
# This is the only way to uniquely associate the joint name with the correct
# states.


Header header

string[] name
float64[] position
float64[] velocity
float64[] effort

================================================================================
MSG: std_msgs/Header
# Standard metadata for higher-level stamped data types.
# This is generally used to communicate timestamped data 
# in a particular coordinate frame.
# 
# sequence ID: consecutively increasing ID 
uint32 seq
#Two-integer timestamp that is expressed as:
# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')
# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')
# time-handling sugar is provided by the client library
time stamp
#Frame this data is associated with
string frame_id
---
geometry_msgs/Pose solution

================================================================================
MSG: geometry_msgs/Pose
# A representation of pose in free space, composed of position and orientation. 
Point position
Quaternion orientation

================================================================================
MSG: geometry_msgs/Point
# This contains the position of a point in free space
float64 x
float64 y
float64 z

================================================================================
MSG: geometry_msgs/Quaternion
# This represents an orientation in free space in quaternion form.

float64 x
float64 y
float64 z
float64 w
")



(provide :panda_ik/pandaFk "cf41e0feb1f85dd54246ca565d37eb4f")


