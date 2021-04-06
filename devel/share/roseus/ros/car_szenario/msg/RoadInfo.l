;; Auto-generated. Do not edit!


(when (boundp 'car_szenario::RoadInfo)
  (if (not (find-package "CAR_SZENARIO"))
    (make-package "CAR_SZENARIO"))
  (shadow 'RoadInfo (find-package "CAR_SZENARIO")))
(unless (find-package "CAR_SZENARIO::ROADINFO")
  (make-package "CAR_SZENARIO::ROADINFO"))

(in-package "ROS")
;;//! \htmlinclude RoadInfo.msg.html
(if (not (find-package "GEOMETRY_MSGS"))
  (ros::roseus-add-msgs "geometry_msgs"))


(defclass car_szenario::RoadInfo
  :super ros::object
  :slots (_szeneType _startPoints _endPoints ))

(defmethod car_szenario::RoadInfo
  (:init
   (&key
    ((:szeneType __szeneType) "")
    ((:startPoints __startPoints) (let (r) (dotimes (i 0) (push (instance geometry_msgs::Point :init) r)) r))
    ((:endPoints __endPoints) (let (r) (dotimes (i 0) (push (instance geometry_msgs::Point :init) r)) r))
    )
   (send-super :init)
   (setq _szeneType (string __szeneType))
   (setq _startPoints __startPoints)
   (setq _endPoints __endPoints)
   self)
  (:szeneType
   (&optional __szeneType)
   (if __szeneType (setq _szeneType __szeneType)) _szeneType)
  (:startPoints
   (&rest __startPoints)
   (if (keywordp (car __startPoints))
       (send* _startPoints __startPoints)
     (progn
       (if __startPoints (setq _startPoints (car __startPoints)))
       _startPoints)))
  (:endPoints
   (&rest __endPoints)
   (if (keywordp (car __endPoints))
       (send* _endPoints __endPoints)
     (progn
       (if __endPoints (setq _endPoints (car __endPoints)))
       _endPoints)))
  (:serialization-length
   ()
   (+
    ;; string _szeneType
    4 (length _szeneType)
    ;; geometry_msgs/Point[] _startPoints
    (apply #'+ (send-all _startPoints :serialization-length)) 4
    ;; geometry_msgs/Point[] _endPoints
    (apply #'+ (send-all _endPoints :serialization-length)) 4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; string _szeneType
       (write-long (length _szeneType) s) (princ _szeneType s)
     ;; geometry_msgs/Point[] _startPoints
     (write-long (length _startPoints) s)
     (dolist (elem _startPoints)
       (send elem :serialize s)
       )
     ;; geometry_msgs/Point[] _endPoints
     (write-long (length _endPoints) s)
     (dolist (elem _endPoints)
       (send elem :serialize s)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; string _szeneType
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _szeneType (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;; geometry_msgs/Point[] _startPoints
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _startPoints (let (r) (dotimes (i n) (push (instance geometry_msgs::Point :init) r)) r))
     (dolist (elem- _startPoints)
     (send elem- :deserialize buf ptr-) (incf ptr- (send elem- :serialization-length))
     ))
   ;; geometry_msgs/Point[] _endPoints
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _endPoints (let (r) (dotimes (i n) (push (instance geometry_msgs::Point :init) r)) r))
     (dolist (elem- _endPoints)
     (send elem- :deserialize buf ptr-) (incf ptr- (send elem- :serialization-length))
     ))
   ;;
   self)
  )

(setf (get car_szenario::RoadInfo :md5sum-) "d73c6909833f4f488b467a9cd08b32f8")
(setf (get car_szenario::RoadInfo :datatype-) "car_szenario/RoadInfo")
(setf (get car_szenario::RoadInfo :definition-)
      "# Represents a part/szene of a map with start- and endpoints of markings in szene

string szeneType
geometry_msgs/Point[] startPoints
geometry_msgs/Point[] endPoints

================================================================================
MSG: geometry_msgs/Point
# This contains the position of a point in free space
float64 x
float64 y
float64 z

")



(provide :car_szenario/RoadInfo "d73c6909833f4f488b467a9cd08b32f8")


