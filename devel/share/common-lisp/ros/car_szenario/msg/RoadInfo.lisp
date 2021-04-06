; Auto-generated. Do not edit!


(cl:in-package car_szenario-msg)


;//! \htmlinclude RoadInfo.msg.html

(cl:defclass <RoadInfo> (roslisp-msg-protocol:ros-message)
  ((szeneType
    :reader szeneType
    :initarg :szeneType
    :type cl:string
    :initform "")
   (startPoints
    :reader startPoints
    :initarg :startPoints
    :type (cl:vector geometry_msgs-msg:Point)
   :initform (cl:make-array 0 :element-type 'geometry_msgs-msg:Point :initial-element (cl:make-instance 'geometry_msgs-msg:Point)))
   (endPoints
    :reader endPoints
    :initarg :endPoints
    :type (cl:vector geometry_msgs-msg:Point)
   :initform (cl:make-array 0 :element-type 'geometry_msgs-msg:Point :initial-element (cl:make-instance 'geometry_msgs-msg:Point))))
)

(cl:defclass RoadInfo (<RoadInfo>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <RoadInfo>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'RoadInfo)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name car_szenario-msg:<RoadInfo> is deprecated: use car_szenario-msg:RoadInfo instead.")))

(cl:ensure-generic-function 'szeneType-val :lambda-list '(m))
(cl:defmethod szeneType-val ((m <RoadInfo>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader car_szenario-msg:szeneType-val is deprecated.  Use car_szenario-msg:szeneType instead.")
  (szeneType m))

(cl:ensure-generic-function 'startPoints-val :lambda-list '(m))
(cl:defmethod startPoints-val ((m <RoadInfo>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader car_szenario-msg:startPoints-val is deprecated.  Use car_szenario-msg:startPoints instead.")
  (startPoints m))

(cl:ensure-generic-function 'endPoints-val :lambda-list '(m))
(cl:defmethod endPoints-val ((m <RoadInfo>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader car_szenario-msg:endPoints-val is deprecated.  Use car_szenario-msg:endPoints instead.")
  (endPoints m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <RoadInfo>) ostream)
  "Serializes a message object of type '<RoadInfo>"
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'szeneType))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'szeneType))
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'startPoints))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (roslisp-msg-protocol:serialize ele ostream))
   (cl:slot-value msg 'startPoints))
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'endPoints))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (roslisp-msg-protocol:serialize ele ostream))
   (cl:slot-value msg 'endPoints))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <RoadInfo>) istream)
  "Deserializes a message object of type '<RoadInfo>"
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'szeneType) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'szeneType) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'startPoints) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'startPoints)))
    (cl:dotimes (i __ros_arr_len)
    (cl:setf (cl:aref vals i) (cl:make-instance 'geometry_msgs-msg:Point))
  (roslisp-msg-protocol:deserialize (cl:aref vals i) istream))))
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'endPoints) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'endPoints)))
    (cl:dotimes (i __ros_arr_len)
    (cl:setf (cl:aref vals i) (cl:make-instance 'geometry_msgs-msg:Point))
  (roslisp-msg-protocol:deserialize (cl:aref vals i) istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<RoadInfo>)))
  "Returns string type for a message object of type '<RoadInfo>"
  "car_szenario/RoadInfo")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'RoadInfo)))
  "Returns string type for a message object of type 'RoadInfo"
  "car_szenario/RoadInfo")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<RoadInfo>)))
  "Returns md5sum for a message object of type '<RoadInfo>"
  "d73c6909833f4f488b467a9cd08b32f8")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'RoadInfo)))
  "Returns md5sum for a message object of type 'RoadInfo"
  "d73c6909833f4f488b467a9cd08b32f8")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<RoadInfo>)))
  "Returns full string definition for message of type '<RoadInfo>"
  (cl:format cl:nil "# Represents a part/szene of a map with start- and endpoints of markings in szene~%~%string szeneType~%geometry_msgs/Point[] startPoints~%geometry_msgs/Point[] endPoints~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'RoadInfo)))
  "Returns full string definition for message of type 'RoadInfo"
  (cl:format cl:nil "# Represents a part/szene of a map with start- and endpoints of markings in szene~%~%string szeneType~%geometry_msgs/Point[] startPoints~%geometry_msgs/Point[] endPoints~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <RoadInfo>))
  (cl:+ 0
     4 (cl:length (cl:slot-value msg 'szeneType))
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'startPoints) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ (roslisp-msg-protocol:serialization-length ele))))
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'endPoints) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ (roslisp-msg-protocol:serialization-length ele))))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <RoadInfo>))
  "Converts a ROS message object to a list"
  (cl:list 'RoadInfo
    (cl:cons ':szeneType (szeneType msg))
    (cl:cons ':startPoints (startPoints msg))
    (cl:cons ':endPoints (endPoints msg))
))
