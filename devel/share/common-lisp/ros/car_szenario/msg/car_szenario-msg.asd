
(cl:in-package :asdf)

(defsystem "car_szenario-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils :geometry_msgs-msg
)
  :components ((:file "_package")
    (:file "RoadInfo" :depends-on ("_package_RoadInfo"))
    (:file "_package_RoadInfo" :depends-on ("_package"))
  ))