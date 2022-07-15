
(cl:in-package :asdf)

(defsystem "panda_ik-srv"
  :depends-on (:roslisp-msg-protocol :roslisp-utils :geometry_msgs-msg
               :sensor_msgs-msg
)
  :components ((:file "_package")
    (:file "pandaFk" :depends-on ("_package_pandaFk"))
    (:file "_package_pandaFk" :depends-on ("_package"))
    (:file "pandaIk" :depends-on ("_package_pandaIk"))
    (:file "_package_pandaIk" :depends-on ("_package"))
  ))