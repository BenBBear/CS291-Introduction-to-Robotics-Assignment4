
(cl:in-package :asdf)

(defsystem "a53095838_assignment_4-srv"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "cmd" :depends-on ("_package_cmd"))
    (:file "_package_cmd" :depends-on ("_package"))
  ))