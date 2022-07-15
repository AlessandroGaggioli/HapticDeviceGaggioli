;; Auto-generated. Do not edit!


(when (boundp 'panda_ik::pandaIk)
  (if (not (find-package "PANDA_IK"))
    (make-package "PANDA_IK"))
  (shadow 'pandaIk (find-package "PANDA_IK")))
(unless (find-package "PANDA_IK::PANDAIK")
  (make-package "PANDA_IK::PANDAIK"))
(unless (find-package "PANDA_IK::PANDAIKREQUEST")
  (make-package "PANDA_IK::PANDAIKREQUEST"))
(unless (find-package "PANDA_IK::PANDAIKRESPONSE")
  (make-package "PANDA_IK::PANDAIKRESPONSE"))

(in-package "ROS")

(if (not (find-package "GEOMETRY_MSGS"))
  (ros::roseus-add-msgs "geometry_msgs"))
(if (not (find-package "SENSOR_MSGS"))
  (ros::roseus-add-msgs "sensor_msgs"))


(if (not (find-package "SENSOR_MSGS"))
  (ros::roseus-add-msgs "sensor_msgs"))


(defclass panda_ik::pandaIkRequest
  :super ros::object
  :slots (_reference_pose _seed_joints ))

(defmethod panda_ik::pandaIkRequest
  (:init
   (&key
    ((:reference_pose __reference_pose) (instance geometry_msgs::Pose :init))
    ((:seed_joints __seed_joints) (instance sensor_msgs::JointState :init))
    )
   (send-super :init)
   (setq _reference_pose __reference_pose)
   (setq _seed_joints __seed_joints)
   self)
  (:reference_pose
   (&rest __reference_pose)
   (if (keywordp (car __reference_pose))
       (send* _reference_pose __reference_pose)
     (progn
       (if __reference_pose (setq _reference_pose (car __reference_pose)))
       _reference_pose)))
  (:seed_joints
   (&rest __seed_joints)
   (if (keywordp (car __seed_joints))
       (send* _seed_joints __seed_joints)
     (progn
       (if __seed_joints (setq _seed_joints (car __seed_joints)))
       _seed_joints)))
  (:serialization-length
   ()
   (+
    ;; geometry_msgs/Pose _reference_pose
    (send _reference_pose :serialization-length)
    ;; sensor_msgs/JointState _seed_joints
    (send _seed_joints :serialization-length)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; geometry_msgs/Pose _reference_pose
       (send _reference_pose :serialize s)
     ;; sensor_msgs/JointState _seed_joints
       (send _seed_joints :serialize s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; geometry_msgs/Pose _reference_pose
     (send _reference_pose :deserialize buf ptr-) (incf ptr- (send _reference_pose :serialization-length))
   ;; sensor_msgs/JointState _seed_joints
     (send _seed_joints :deserialize buf ptr-) (incf ptr- (send _seed_joints :serialization-length))
   ;;
   self)
  )

(defclass panda_ik::pandaIkResponse
  :super ros::object
  :slots (_solution _success ))

(defmethod panda_ik::pandaIkResponse
  (:init
   (&key
    ((:solution __solution) (instance sensor_msgs::JointState :init))
    ((:success __success) nil)
    )
   (send-super :init)
   (setq _solution __solution)
   (setq _success __success)
   self)
  (:solution
   (&rest __solution)
   (if (keywordp (car __solution))
       (send* _solution __solution)
     (progn
       (if __solution (setq _solution (car __solution)))
       _solution)))
  (:success
   (&optional (__success :null))
   (if (not (eq __success :null)) (setq _success __success)) _success)
  (:serialization-length
   ()
   (+
    ;; sensor_msgs/JointState _solution
    (send _solution :serialization-length)
    ;; bool _success
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; sensor_msgs/JointState _solution
       (send _solution :serialize s)
     ;; bool _success
       (if _success (write-byte -1 s) (write-byte 0 s))
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; sensor_msgs/JointState _solution
     (send _solution :deserialize buf ptr-) (incf ptr- (send _solution :serialization-length))
   ;; bool _success
     (setq _success (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;;
   self)
  )

(defclass panda_ik::pandaIk
  :super ros::object
  :slots ())

(setf (get panda_ik::pandaIk :md5sum-) "65f8d44d8abe540af29b0f9c556cdb12")
(setf (get panda_ik::pandaIk :datatype-) "panda_ik/pandaIk")
(setf (get panda_ik::pandaIk :request) panda_ik::pandaIkRequest)
(setf (get panda_ik::pandaIk :response) panda_ik::pandaIkResponse)

(defmethod panda_ik::pandaIkRequest
  (:response () (instance panda_ik::pandaIkResponse :init)))

(setf (get panda_ik::pandaIkRequest :md5sum-) "65f8d44d8abe540af29b0f9c556cdb12")
(setf (get panda_ik::pandaIkRequest :datatype-) "panda_ik/pandaIkRequest")
(setf (get panda_ik::pandaIkRequest :definition-)
      "geometry_msgs/Pose reference_pose
sensor_msgs/JointState seed_joints

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
sensor_msgs/JointState solution
bool success

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
")

(setf (get panda_ik::pandaIkResponse :md5sum-) "65f8d44d8abe540af29b0f9c556cdb12")
(setf (get panda_ik::pandaIkResponse :datatype-) "panda_ik/pandaIkResponse")
(setf (get panda_ik::pandaIkResponse :definition-)
      "geometry_msgs/Pose reference_pose
sensor_msgs/JointState seed_joints

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
sensor_msgs/JointState solution
bool success

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
")



(provide :panda_ik/pandaIk "65f8d44d8abe540af29b0f9c556cdb12")


