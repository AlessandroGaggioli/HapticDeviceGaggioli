// Auto-generated. Do not edit!

// (in-package panda_ik.srv)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;
let sensor_msgs = _finder('sensor_msgs');

//-----------------------------------------------------------

let geometry_msgs = _finder('geometry_msgs');

//-----------------------------------------------------------

class pandaFkRequest {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.reference_joints = null;
    }
    else {
      if (initObj.hasOwnProperty('reference_joints')) {
        this.reference_joints = initObj.reference_joints
      }
      else {
        this.reference_joints = new sensor_msgs.msg.JointState();
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type pandaFkRequest
    // Serialize message field [reference_joints]
    bufferOffset = sensor_msgs.msg.JointState.serialize(obj.reference_joints, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type pandaFkRequest
    let len;
    let data = new pandaFkRequest(null);
    // Deserialize message field [reference_joints]
    data.reference_joints = sensor_msgs.msg.JointState.deserialize(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += sensor_msgs.msg.JointState.getMessageSize(object.reference_joints);
    return length;
  }

  static datatype() {
    // Returns string type for a service object
    return 'panda_ik/pandaFkRequest';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '35eb9f09e3dd7d140ed4199613734c94';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    sensor_msgs/JointState reference_joints
    
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
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new pandaFkRequest(null);
    if (msg.reference_joints !== undefined) {
      resolved.reference_joints = sensor_msgs.msg.JointState.Resolve(msg.reference_joints)
    }
    else {
      resolved.reference_joints = new sensor_msgs.msg.JointState()
    }

    return resolved;
    }
};

class pandaFkResponse {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.solution = null;
    }
    else {
      if (initObj.hasOwnProperty('solution')) {
        this.solution = initObj.solution
      }
      else {
        this.solution = new geometry_msgs.msg.Pose();
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type pandaFkResponse
    // Serialize message field [solution]
    bufferOffset = geometry_msgs.msg.Pose.serialize(obj.solution, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type pandaFkResponse
    let len;
    let data = new pandaFkResponse(null);
    // Deserialize message field [solution]
    data.solution = geometry_msgs.msg.Pose.deserialize(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 56;
  }

  static datatype() {
    // Returns string type for a service object
    return 'panda_ik/pandaFkResponse';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '3595aa8695ee087c6cee665c0f6958e2';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
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
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new pandaFkResponse(null);
    if (msg.solution !== undefined) {
      resolved.solution = geometry_msgs.msg.Pose.Resolve(msg.solution)
    }
    else {
      resolved.solution = new geometry_msgs.msg.Pose()
    }

    return resolved;
    }
};

module.exports = {
  Request: pandaFkRequest,
  Response: pandaFkResponse,
  md5sum() { return 'cf41e0feb1f85dd54246ca565d37eb4f'; },
  datatype() { return 'panda_ik/pandaFk'; }
};
