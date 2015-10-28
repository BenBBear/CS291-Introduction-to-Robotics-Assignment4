#include "../include/a53095838_assignment_4/util.h"
#define FRAME(i,j) frame->data[j*frame->width+i]
#define RAW() cv::imshow("view", image)

Control_Type mode = Control_Val_RAW;

bool control_callback(a53095838_assignment_4::cmd::Request &req,a53095838_assignment_4::cmd::Response &res){
    res.success = true;
    mode = req.mode;        
    return true;
}



void gscam_callback (const sensor_msgs::ImageConstPtr& frame){
    cv::Mat image = cv_bridge::toCvShare(frame, "bgr8")->image;
    switch(mode){
    case Control_Val_RAW:
        RAW();
        break;
    case Control_Val_Farneback:
        
        break;
    case Control_Val_MOG2:
        
        break;
    default:
        RAW();
    }    
}


int main(int argc, char **argv){
    string node_name = "motion";
    ros::init(argc, argv, node_name);
    ros::NodeHandle n;
    // service to subscribe "motion_processing_type"
    ros::ServiceServer service = n.advertiseService(Control_channel, control_callback);
    ros::Subscriber gscam_sub = n.subscribe(Image_channel, 1, gscam_callback);

    cv::namedWindow("view");
    cv::startWindowThread();
    ros::spin();
    cv::destroyWindow("view");
    return 0;
}
