// Auto-generated. Do not edit!

// (in-package panda_ik.srv)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;
let geometry_msgs = _finder('geometry_msgs');
let sensor_msgs = _finder('sensor_msgs');

//-----------------------------------------------------------


//-----------------------------------------------------------

class pandaIkRequest {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.reference_pose = null;
      this.seed_joints = null;
    }
    else {
      if (initObj.hasOwnProperty('reference_pose')) {
        this.reference_pose = initObj.reference_pose
      }
      else {
        this.reference_pose = new geometry_msgs.msg.Pose();
      }
      if (initObj.hasOwnProperty('seed_joints')) {
        this.seed_joints = initObj.seed_joints
      }
      else {
        this.seed_joints = new sensor_msgs.msg.JointState();
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type pandaIkRequest
    // Serialize message field [reference_pose]
    bufferOffset = geometry_msgs.msg.Pose.serialize(obj.reference_pose, buffer, bufferOffset);
    // Serialize message field [seed_joints]
    bufferOffset = sensor_msgs.msg.JointState.serialize(obj.seed_joints, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type pandaIkRequest
    let len;
    let data = new pandaIkRequest(null);
    // Deserialize message field [reference_pose]
    data.reference_pose = geometry_msgs.msg.Pose.deserialize(buffer, bufferOffset);
    // Deserialize message field [seed_joints]
    data.seed_joints = sensor_msgs.msg.JointState.deserialize(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += sensor_msgs.msg.JointState.getMessageSize(object.seed_joints);
    return length + 56;
  }

  static datatype() {
    // Returns string type for a service object
    return 'panda_ik/pandaIkRequest';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'b2acb58c4e6d61c85039d7bc6cff7d6d';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    geometry_msgs/Pose reference_pose
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
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new pandaIkRequest(null);
    if (msg.reference_pose !== undefined) {
      resolved.reference_pose = geometry_msgs.msg.Pose.Resolve(msg.reference_pose)
    }
    else {
      resolved.reference_pose = new geometry_msgs.msg.Pose()
    }

    if (msg.seed_joints !== undefined) {
      resolved.seed_joints = sensor_msgs.msg.JointState.Resolve(msg.seed_joints)
    }
    else {
      resolved.seed_joints = new sensor_msgs.msg.JointState()
    }

    return resolved;
    }
};

class pandaIkResponse {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.solution = null;
      this.success = null;
    }
    else {
      if (initObj.hasOwnProperty('solution')) {
        this.solution = initObj.solution
      }
      else {
        this.solution = new sensor_msgs.msg.JointState();
      }
      if (initObj.hasOwnProperty('success')) {
        this.success = initObj.success
      }
      else {
        this.success = false;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type pandaIkResponse
    // Serialize message field [solution]
    bufferOffset = sensor_msgs.msg.JointState.serialize(obj.solution, buffer, bufferOffset);
    // Serialize message field [success]
    bufferOffset = _serializer.bool(obj.success, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type pandaIkResponse
    let len;
    let data = new pandaIkResponse(null);
    // Deserialize message field [solution]
    data.solution = sensor_msgs.msg.JointState.deserialize(buffer, bufferOffset);
    // Deserialize message field [success]
    data.success = _deserializer.bool(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += sensor_msgs.msg.JointState.getMessageSize(object.solution);
    return length + 1;
  }

  static datatype() {
    // Returns string type for a service object
    return 'panda_ik/pandaIkResponse';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'd492d07fea71104fe59769bb19fedae3';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
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
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new pandaIkResponse(null);
    if (msg.solution !== undefined) {
      resolved.solution = sensor_msgs.msg.JointState.Resolve(msg.solution)
    }
    else {
      resolved.solution = new sensor_msgs.msg.JointState()
    }

    if (msg.success !== undefined) {
      resolved.success = msg.success;
    }
    else {
      resolved.success = false
    }

    return resolved;
    }
};

module.exports = {
  Request: pandaIkRequest,
  Response: pandaIkResponse,
  md5sum() { return '65f8d44d8abe540af29b0f9c556cdb12'; },
  datatype() { return 'panda_ik/pandaIk'; }
};
