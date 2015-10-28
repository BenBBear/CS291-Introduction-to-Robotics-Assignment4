#include "../include/a53095838_assignment_4/util.h"

bool control_callback(a53095838_assignment_4::cmd::Request &req,a53095838_assignment_4::cmd::Response &res){
    res.success = true;
    switch(req.mode){
    case Control_Val_Farneback:

        break;
    case Control_Val_MOG2:
        break;
    case Control_Val_RAW:

        break;        
    }
    
    return true;
}


int main(int argc, char **argv){
    string node_name = "motion";
    ros::init(argc, argv, node_name);
    ros::NodeHandle n;
    // service to subscribe "motion_processing_type"
    ros::ServiceServer service = n.advertiseService(Control_channel, control_callback);
    ros::spin();        
    return 0;
}
