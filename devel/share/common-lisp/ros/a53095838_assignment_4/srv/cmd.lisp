; Auto-generated. Do not edit!


(cl:in-package a53095838_assignment_4-srv)


;//! \htmlinclude cmd-request.msg.html

(cl:defclass <cmd-request> (roslisp-msg-protocol:ros-message)
  ((mode
    :reader mode
    :initarg :mode
    :type cl:fixnum
    :initform 0))
)

(cl:defclass cmd-request (<cmd-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <cmd-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'cmd-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name a53095838_assignment_4-srv:<cmd-request> is deprecated: use a53095838_assignment_4-srv:cmd-request instead.")))

(cl:ensure-generic-function 'mode-val :lambda-list '(m))
(cl:defmethod mode-val ((m <cmd-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader a53095838_assignment_4-srv:mode-val is deprecated.  Use a53095838_assignment_4-srv:mode instead.")
  (mode m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <cmd-request>) ostream)
  "Serializes a message object of type '<cmd-request>"
  (cl:let* ((signed (cl:slot-value msg 'mode)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 256) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    )
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <cmd-request>) istream)
  "Deserializes a message object of type '<cmd-request>"
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'mode) (cl:if (cl:< unsigned 128) unsigned (cl:- unsigned 256))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<cmd-request>)))
  "Returns string type for a service object of type '<cmd-request>"
  "a53095838_assignment_4/cmdRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'cmd-request)))
  "Returns string type for a service object of type 'cmd-request"
  "a53095838_assignment_4/cmdRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<cmd-request>)))
  "Returns md5sum for a message object of type '<cmd-request>"
  "5da578ca824a6682cf704b593bb1a59e")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'cmd-request)))
  "Returns md5sum for a message object of type 'cmd-request"
  "5da578ca824a6682cf704b593bb1a59e")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<cmd-request>)))
  "Returns full string definition for message of type '<cmd-request>"
  (cl:format cl:nil "int8 mode~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'cmd-request)))
  "Returns full string definition for message of type 'cmd-request"
  (cl:format cl:nil "int8 mode~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <cmd-request>))
  (cl:+ 0
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <cmd-request>))
  "Converts a ROS message object to a list"
  (cl:list 'cmd-request
    (cl:cons ':mode (mode msg))
))
;//! \htmlinclude cmd-response.msg.html

(cl:defclass <cmd-response> (roslisp-msg-protocol:ros-message)
  ((success
    :reader success
    :initarg :success
    :type cl:boolean
    :initform cl:nil))
)

(cl:defclass cmd-response (<cmd-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <cmd-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'cmd-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name a53095838_assignment_4-srv:<cmd-response> is deprecated: use a53095838_assignment_4-srv:cmd-response instead.")))

(cl:ensure-generic-function 'success-val :lambda-list '(m))
(cl:defmethod success-val ((m <cmd-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader a53095838_assignment_4-srv:success-val is deprecated.  Use a53095838_assignment_4-srv:success instead.")
  (success m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <cmd-response>) ostream)
  "Serializes a message object of type '<cmd-response>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'success) 1 0)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <cmd-response>) istream)
  "Deserializes a message object of type '<cmd-response>"
    (cl:setf (cl:slot-value msg 'success) (cl:not (cl:zerop (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<cmd-response>)))
  "Returns string type for a service object of type '<cmd-response>"
  "a53095838_assignment_4/cmdResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'cmd-response)))
  "Returns string type for a service object of type 'cmd-response"
  "a53095838_assignment_4/cmdResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<cmd-response>)))
  "Returns md5sum for a message object of type '<cmd-response>"
  "5da578ca824a6682cf704b593bb1a59e")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'cmd-response)))
  "Returns md5sum for a message object of type 'cmd-response"
  "5da578ca824a6682cf704b593bb1a59e")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<cmd-response>)))
  "Returns full string definition for message of type '<cmd-response>"
  (cl:format cl:nil "bool success~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'cmd-response)))
  "Returns full string definition for message of type 'cmd-response"
  (cl:format cl:nil "bool success~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <cmd-response>))
  (cl:+ 0
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <cmd-response>))
  "Converts a ROS message object to a list"
  (cl:list 'cmd-response
    (cl:cons ':success (success msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'cmd)))
  'cmd-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'cmd)))
  'cmd-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'cmd)))
  "Returns string type for a service object of type '<cmd>"
  "a53095838_assignment_4/cmd")