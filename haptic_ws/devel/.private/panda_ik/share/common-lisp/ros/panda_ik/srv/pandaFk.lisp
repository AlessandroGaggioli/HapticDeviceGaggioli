; Auto-generated. Do not edit!


(cl:in-package panda_ik-srv)


;//! \htmlinclude pandaFk-request.msg.html

(cl:defclass <pandaFk-request> (roslisp-msg-protocol:ros-message)
  ((reference_joints
    :reader reference_joints
    :initarg :reference_joints
    :type sensor_msgs-msg:JointState
    :initform (cl:make-instance 'sensor_msgs-msg:JointState)))
)

(cl:defclass pandaFk-request (<pandaFk-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <pandaFk-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'pandaFk-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name panda_ik-srv:<pandaFk-request> is deprecated: use panda_ik-srv:pandaFk-request instead.")))

(cl:ensure-generic-function 'reference_joints-val :lambda-list '(m))
(cl:defmethod reference_joints-val ((m <pandaFk-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader panda_ik-srv:reference_joints-val is deprecated.  Use panda_ik-srv:reference_joints instead.")
  (reference_joints m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <pandaFk-request>) ostream)
  "Serializes a message object of type '<pandaFk-request>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'reference_joints) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <pandaFk-request>) istream)
  "Deserializes a message object of type '<pandaFk-request>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'reference_joints) istream)
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<pandaFk-request>)))
  "Returns string type for a service object of type '<pandaFk-request>"
  "panda_ik/pandaFkRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'pandaFk-request)))
  "Returns string type for a service object of type 'pandaFk-request"
  "panda_ik/pandaFkRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<pandaFk-request>)))
  "Returns md5sum for a message object of type '<pandaFk-request>"
  "cf41e0feb1f85dd54246ca565d37eb4f")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'pandaFk-request)))
  "Returns md5sum for a message object of type 'pandaFk-request"
  "cf41e0feb1f85dd54246ca565d37eb4f")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<pandaFk-request>)))
  "Returns full string definition for message of type '<pandaFk-request>"
  (cl:format cl:nil "sensor_msgs/JointState reference_joints~%~%================================================================================~%MSG: sensor_msgs/JointState~%# This is a message that holds data to describe the state of a set of torque controlled joints. ~%#~%# The state of each joint (revolute or prismatic) is defined by:~%#  * the position of the joint (rad or m),~%#  * the velocity of the joint (rad/s or m/s) and ~%#  * the effort that is applied in the joint (Nm or N).~%#~%# Each joint is uniquely identified by its name~%# The header specifies the time at which the joint states were recorded. All the joint states~%# in one message have to be recorded at the same time.~%#~%# This message consists of a multiple arrays, one for each part of the joint state. ~%# The goal is to make each of the fields optional. When e.g. your joints have no~%# effort associated with them, you can leave the effort array empty. ~%#~%# All arrays in this message should have the same size, or be empty.~%# This is the only way to uniquely associate the joint name with the correct~%# states.~%~%~%Header header~%~%string[] name~%float64[] position~%float64[] velocity~%float64[] effort~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'pandaFk-request)))
  "Returns full string definition for message of type 'pandaFk-request"
  (cl:format cl:nil "sensor_msgs/JointState reference_joints~%~%================================================================================~%MSG: sensor_msgs/JointState~%# This is a message that holds data to describe the state of a set of torque controlled joints. ~%#~%# The state of each joint (revolute or prismatic) is defined by:~%#  * the position of the joint (rad or m),~%#  * the velocity of the joint (rad/s or m/s) and ~%#  * the effort that is applied in the joint (Nm or N).~%#~%# Each joint is uniquely identified by its name~%# The header specifies the time at which the joint states were recorded. All the joint states~%# in one message have to be recorded at the same time.~%#~%# This message consists of a multiple arrays, one for each part of the joint state. ~%# The goal is to make each of the fields optional. When e.g. your joints have no~%# effort associated with them, you can leave the effort array empty. ~%#~%# All arrays in this message should have the same size, or be empty.~%# This is the only way to uniquely associate the joint name with the correct~%# states.~%~%~%Header header~%~%string[] name~%float64[] position~%float64[] velocity~%float64[] effort~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <pandaFk-request>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'reference_joints))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <pandaFk-request>))
  "Converts a ROS message object to a list"
  (cl:list 'pandaFk-request
    (cl:cons ':reference_joints (reference_joints msg))
))
;//! \htmlinclude pandaFk-response.msg.html

(cl:defclass <pandaFk-response> (roslisp-msg-protocol:ros-message)
  ((solution
    :reader solution
    :initarg :solution
    :type geometry_msgs-msg:Pose
    :initform (cl:make-instance 'geometry_msgs-msg:Pose)))
)

(cl:defclass pandaFk-response (<pandaFk-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <pandaFk-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'pandaFk-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name panda_ik-srv:<pandaFk-response> is deprecated: use panda_ik-srv:pandaFk-response instead.")))

(cl:ensure-generic-function 'solution-val :lambda-list '(m))
(cl:defmethod solution-val ((m <pandaFk-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader panda_ik-srv:solution-val is deprecated.  Use panda_ik-srv:solution instead.")
  (solution m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <pandaFk-response>) ostream)
  "Serializes a message object of type '<pandaFk-response>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'solution) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <pandaFk-response>) istream)
  "Deserializes a message object of type '<pandaFk-response>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'solution) istream)
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<pandaFk-response>)))
  "Returns string type for a service object of type '<pandaFk-response>"
  "panda_ik/pandaFkResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'pandaFk-response)))
  "Returns string type for a service object of type 'pandaFk-response"
  "panda_ik/pandaFkResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<pandaFk-response>)))
  "Returns md5sum for a message object of type '<pandaFk-response>"
  "cf41e0feb1f85dd54246ca565d37eb4f")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'pandaFk-response)))
  "Returns md5sum for a message object of type 'pandaFk-response"
  "cf41e0feb1f85dd54246ca565d37eb4f")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<pandaFk-response>)))
  "Returns full string definition for message of type '<pandaFk-response>"
  (cl:format cl:nil "geometry_msgs/Pose solution~%~%================================================================================~%MSG: geometry_msgs/Pose~%# A representation of pose in free space, composed of position and orientation. ~%Point position~%Quaternion orientation~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%================================================================================~%MSG: geometry_msgs/Quaternion~%# This represents an orientation in free space in quaternion form.~%~%float64 x~%float64 y~%float64 z~%float64 w~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'pandaFk-response)))
  "Returns full string definition for message of type 'pandaFk-response"
  (cl:format cl:nil "geometry_msgs/Pose solution~%~%================================================================================~%MSG: geometry_msgs/Pose~%# A representation of pose in free space, composed of position and orientation. ~%Point position~%Quaternion orientation~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%================================================================================~%MSG: geometry_msgs/Quaternion~%# This represents an orientation in free space in quaternion form.~%~%float64 x~%float64 y~%float64 z~%float64 w~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <pandaFk-response>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'solution))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <pandaFk-response>))
  "Converts a ROS message object to a list"
  (cl:list 'pandaFk-response
    (cl:cons ':solution (solution msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'pandaFk)))
  'pandaFk-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'pandaFk)))
  'pandaFk-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'pandaFk)))
  "Returns string type for a service object of type '<pandaFk>"
  "panda_ik/pandaFk")