// Auto-generated. Do not edit!

// (in-package car_szenario.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;
let geometry_msgs = _finder('geometry_msgs');

//-----------------------------------------------------------

class RoadInfo {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.szeneType = null;
      this.startPoints = null;
      this.endPoints = null;
    }
    else {
      if (initObj.hasOwnProperty('szeneType')) {
        this.szeneType = initObj.szeneType
      }
      else {
        this.szeneType = '';
      }
      if (initObj.hasOwnProperty('startPoints')) {
        this.startPoints = initObj.startPoints
      }
      else {
        this.startPoints = [];
      }
      if (initObj.hasOwnProperty('endPoints')) {
        this.endPoints = initObj.endPoints
      }
      else {
        this.endPoints = [];
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type RoadInfo
    // Serialize message field [szeneType]
    bufferOffset = _serializer.string(obj.szeneType, buffer, bufferOffset);
    // Serialize message field [startPoints]
    // Serialize the length for message field [startPoints]
    bufferOffset = _serializer.uint32(obj.startPoints.length, buffer, bufferOffset);
    obj.startPoints.forEach((val) => {
      bufferOffset = geometry_msgs.msg.Point.serialize(val, buffer, bufferOffset);
    });
    // Serialize message field [endPoints]
    // Serialize the length for message field [endPoints]
    bufferOffset = _serializer.uint32(obj.endPoints.length, buffer, bufferOffset);
    obj.endPoints.forEach((val) => {
      bufferOffset = geometry_msgs.msg.Point.serialize(val, buffer, bufferOffset);
    });
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type RoadInfo
    let len;
    let data = new RoadInfo(null);
    // Deserialize message field [szeneType]
    data.szeneType = _deserializer.string(buffer, bufferOffset);
    // Deserialize message field [startPoints]
    // Deserialize array length for message field [startPoints]
    len = _deserializer.uint32(buffer, bufferOffset);
    data.startPoints = new Array(len);
    for (let i = 0; i < len; ++i) {
      data.startPoints[i] = geometry_msgs.msg.Point.deserialize(buffer, bufferOffset)
    }
    // Deserialize message field [endPoints]
    // Deserialize array length for message field [endPoints]
    len = _deserializer.uint32(buffer, bufferOffset);
    data.endPoints = new Array(len);
    for (let i = 0; i < len; ++i) {
      data.endPoints[i] = geometry_msgs.msg.Point.deserialize(buffer, bufferOffset)
    }
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += object.szeneType.length;
    length += 24 * object.startPoints.length;
    length += 24 * object.endPoints.length;
    return length + 12;
  }

  static datatype() {
    // Returns string type for a message object
    return 'car_szenario/RoadInfo';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'd73c6909833f4f488b467a9cd08b32f8';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    # Represents a part/szene of a map with start- and endpoints of markings in szene
    
    string szeneType
    geometry_msgs/Point[] startPoints
    geometry_msgs/Point[] endPoints
    
    ================================================================================
    MSG: geometry_msgs/Point
    # This contains the position of a point in free space
    float64 x
    float64 y
    float64 z
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new RoadInfo(null);
    if (msg.szeneType !== undefined) {
      resolved.szeneType = msg.szeneType;
    }
    else {
      resolved.szeneType = ''
    }

    if (msg.startPoints !== undefined) {
      resolved.startPoints = new Array(msg.startPoints.length);
      for (let i = 0; i < resolved.startPoints.length; ++i) {
        resolved.startPoints[i] = geometry_msgs.msg.Point.Resolve(msg.startPoints[i]);
      }
    }
    else {
      resolved.startPoints = []
    }

    if (msg.endPoints !== undefined) {
      resolved.endPoints = new Array(msg.endPoints.length);
      for (let i = 0; i < resolved.endPoints.length; ++i) {
        resolved.endPoints[i] = geometry_msgs.msg.Point.Resolve(msg.endPoints[i]);
      }
    }
    else {
      resolved.endPoints = []
    }

    return resolved;
    }
};

module.exports = RoadInfo;
