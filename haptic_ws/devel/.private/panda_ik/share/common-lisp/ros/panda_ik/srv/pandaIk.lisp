; Auto-generated. Do not edit!


(cl:in-package panda_ik-srv)


;//! \htmlinclude pandaIk-request.msg.html

(cl:defclass <pandaIk-request> (roslisp-msg-protocol:ros-message)
  ((reference_pose
    :reader reference_pose
    :initarg :reference_pose
    :type geometry_msgs-msg:Pose
    :initform (cl:make-instance 'geometry_msgs-msg:Pose))
   (seed_joints
    :reader seed_joints
    :initarg :seed_joints
    :type sensor_msgs-msg:JointState
    :initform (cl:make-instance 'sensor_msgs-msg:JointState)))
)

(cl:defclass pandaIk-request (<pandaIk-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <pandaIk-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'pandaIk-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name panda_ik-srv:<pandaIk-request> is deprecated: use panda_ik-srv:pandaIk-request instead.")))

(cl:ensure-generic-function 'reference_pose-val :lambda-list '(m))
(cl:defmethod reference_pose-val ((m <pandaIk-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader panda_ik-srv:reference_pose-val is deprecated.  Use panda_ik-srv:reference_pose instead.")
  (reference_pose m))

(cl:ensure-generic-function 'seed_joints-val :lambda-list '(m))
(cl:defmethod seed_joints-val ((m <pandaIk-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader panda_ik-srv:seed_joints-val is deprecated.  Use panda_ik-srv:seed_joints instead.")
  (seed_joints m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <pandaIk-request>) ostream)
  "Serializes a message object of type '<pandaIk-request>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'reference_pose) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'seed_joints) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <pandaIk-request>) istream)
  "Deserializes a message object of type '<pandaIk-request>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'reference_pose) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'seed_joints) istream)
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<pandaIk-request>)))
  "Returns string type for a service object of type '<pandaIk-request>"
  "panda_ik/pandaIkRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'pandaIk-request)))
  "Returns string type for a service object of type 'pandaIk-request"
  "panda_ik/pandaIkRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<pandaIk-request>)))
  "Returns md5sum for a message object of type '<pandaIk-request>"
  "65f8d44d8abe540af29b0f9c556cdb12")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'pandaIk-request)))
  "Returns md5sum for a message object of type 'pandaIk-request"
  "65f8d44d8abe540af29b0f9c556cdb12")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<pandaIk-request>)))
  "Returns full string definition for message of type '<pandaIk-request>"
  (cl:format cl:nil "geometry_msgs/Pose reference_pose~%sensor_msgs/JointState seed_joints~%~%================================================================================~%MSG: geometry_msgs/Pose~%# A representation of pose in free space, composed of position and orientation. ~%Point position~%Quaternion orientation~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%================================================================================~%MSG: geometry_msgs/Quaternion~%# This represents an orientation in free space in quaternion form.~%~%float64 x~%float64 y~%float64 z~%float64 w~%~%================================================================================~%MSG: sensor_msgs/JointState~%# This is a message that holds data to describe the state of a set of torque controlled joints. ~%#~%# The state of each joint (revolute or prismatic) is defined by:~%#  * the position of the joint (rad or m),~%#  * the velocity of the joint (rad/s or m/s) and ~%#  * the effort that is applied in the joint (Nm or N).~%#~%# Each joint is uniquely identified by its name~%# The header specifies the time at which the joint states were recorded. All the joint states~%# in one message have to be recorded at the same time.~%#~%# This message consists of a multiple arrays, one for each part of the joint state. ~%# The goal is to make each of the fields optional. When e.g. your joints have no~%# effort associated with them, you can leave the effort array empty. ~%#~%# All arrays in this message should have the same size, or be empty.~%# This is the only way to uniquely associate the joint name with the correct~%# states.~%~%~%Header header~%~%string[] name~%float64[] position~%float64[] velocity~%float64[] effort~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'pandaIk-request)))
  "Returns full string definition for message of type 'pandaIk-request"
  (cl:format cl:nil "geometry_msgs/Pose reference_pose~%sensor_msgs/JointState seed_joints~%~%================================================================================~%MSG: geometry_msgs/Pose~%# A representation of pose in free space, composed of position and orientation. ~%Point position~%Quaternion orientation~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%================================================================================~%MSG: geometry_msgs/Quaternion~%# This represents an orientation in free space in quaternion form.~%~%float64 x~%float64 y~%float64 z~%float64 w~%~%================================================================================~%MSG: sensor_msgs/JointState~%# This is a message that holds data to describe the state of a set of torque controlled joints. ~%#~%# The state of each joint (revolute or prismatic) is defined by:~%#  * the position of the joint (rad or m),~%#  * the velocity of the joint (rad/s or m/s) and ~%#  * the effort that is applied in the joint (Nm or N).~%#~%# Each joint is uniquely identified by its name~%# The header specifies the time at which the joint states were recorded. All the joint states~%# in one message have to be recorded at the same time.~%#~%# This message consists of a multiple arrays, one for each part of the joint state. ~%# The goal is to make each of the fields optional. When e.g. your joints have no~%# effort associated with them, you can leave the effort array empty. ~%#~%# All arrays in this message should have the same size, or be empty.~%# This is the only way to uniquely associate the joint name with the correct~%# states.~%~%~%Header header~%~%string[] name~%float64[] position~%float64[] velocity~%float64[] effort~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <pandaIk-request>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'reference_pose))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'seed_joints))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <pandaIk-request>))
  "Converts a ROS message object to a list"
  (cl:list 'pandaIk-request
    (cl:cons ':reference_pose (reference_pose msg))
    (cl:cons ':seed_joints (seed_joints msg))
))
;//! \htmlinclude pandaIk-response.msg.html

(cl:defclass <pandaIk-response> (roslisp-msg-protocol:ros-message)
  ((solution
    :reader solution
    :initarg :solution
    :type sensor_msgs-msg:JointState
    :initform (cl:make-instance 'sensor_msgs-msg:JointState))
   (success
    :reader success
    :initarg :success
    :type cl:boolean
    :initform cl:nil))
)

(cl:defclass pandaIk-response (<pandaIk-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <pandaIk-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'pandaIk-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name panda_ik-srv:<pandaIk-response> is deprecated: use panda_ik-srv:pandaIk-response instead.")))

(cl:ensure-generic-function 'solution-val :lambda-list '(m))
(cl:defmethod solution-val ((m <pandaIk-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader panda_ik-srv:solution-val is deprecated.  Use panda_ik-srv:solution instead.")
  (solution m))

(cl:ensure-generic-function 'success-val :lambda-list '(m))
(cl:defmethod success-val ((m <pandaIk-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader panda_ik-srv:success-val is deprecated.  Use panda_ik-srv:success instead.")
  (success m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <pandaIk-response>) ostream)
  "Serializes a message object of type '<pandaIk-response>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'solution) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'success) 1 0)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <pandaIk-response>) istream)
  "Deserializes a message object of type '<pandaIk-response>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'solution) istream)
    (cl:setf (cl:slot-value msg 'success) (cl:not (cl:zerop (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<pandaIk-response>)))
  "Returns string type for a service object of type '<pandaIk-response>"
  "panda_ik/pandaIkResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'pandaIk-response)))
  "Returns string type for a service object of type 'pandaIk-response"
  "panda_ik/pandaIkResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<pandaIk-response>)))
  "Returns md5sum for a message object of type '<pandaIk-response>"
  "65f8d44d8abe540af29b0f9c556cdb12")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'pandaIk-response)))
  "Returns md5sum for a message object of type 'pandaIk-response"
  "65f8d44d8abe540af29b0f9c556cdb12")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<pandaIk-response>)))
  "Returns full string definition for message of type '<pandaIk-response>"
  (cl:format cl:nil "sensor_msgs/JointState solution~%bool success~%~%================================================================================~%MSG: sensor_msgs/JointState~%# This is a message that holds data to describe the state of a set of torque controlled joints. ~%#~%# The state of each joint (revolute or prismatic) is defined by:~%#  * the position of the joint (rad or m),~%#  * the velocity of the joint (rad/s or m/s) and ~%#  * the effort that is applied in the joint (Nm or N).~%#~%# Each joint is uniquely identified by its name~%# The header specifies the time at which the joint states were recorded. All the joint states~%# in one message have to be recorded at the same time.~%#~%# This message consists of a multiple arrays, one for each part of the joint state. ~%# The goal is to make each of the fields optional. When e.g. your joints have no~%# effort associated with them, you can leave the effort array empty. ~%#~%# All arrays in this message should have the same size, or be empty.~%# This is the only way to uniquely associate the joint name with the correct~%# states.~%~%~%Header header~%~%string[] name~%float64[] position~%float64[] velocity~%float64[] effort~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'pandaIk-response)))
  "Returns full string definition for message of type 'pandaIk-response"
  (cl:format cl:nil "sensor_msgs/JointState solution~%bool success~%~%================================================================================~%MSG: sensor_msgs/JointState~%# This is a message that holds data to describe the state of a set of torque controlled joints. ~%#~%# The state of each joint (revolute or prismatic) is defined by:~%#  * the position of the joint (rad or m),~%#  * the velocity of the joint (rad/s or m/s) and ~%#  * the effort that is applied in the joint (Nm or N).~%#~%# Each joint is uniquely identified by its name~%# The header specifies the time at which the joint states were recorded. All the joint states~%# in one message have to be recorded at the same time.~%#~%# This message consists of a multiple arrays, one for each part of the joint state. ~%# The goal is to make each of the fields optional. When e.g. your joints have no~%# effort associated with them, you can leave the effort array empty. ~%#~%# All arrays in this message should have the same size, or be empty.~%# This is the only way to uniquely associate the joint name with the correct~%# states.~%~%~%Header header~%~%string[] name~%float64[] position~%float64[] velocity~%float64[] effort~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <pandaIk-response>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'solution))
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <pandaIk-response>))
  "Converts a ROS message object to a list"
  (cl:list 'pandaIk-response
    (cl:cons ':solution (solution msg))
    (cl:cons ':success (success msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'pandaIk)))
  'pandaIk-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'pandaIk)))
  'pandaIk-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'pandaIk)))
  "Returns string type for a service object of type '<pandaIk>"
  "panda_ik/pandaIk")