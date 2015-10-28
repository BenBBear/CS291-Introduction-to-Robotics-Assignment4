#include "../include/a53095838_assignment_4/util.h"
#define FRAME(i,j) frame->data[j*frame->width+i]
#define show(x) cv::imshow("view", md(x))

Control_Type mode = Control_Val_MOG2;

cv::Mat md(cv::Mat image){
    // impement motion detection here, based on that blog
    // should be done
    return image;
}

void mog2(cv::Mat image){
    cv::Mat fore;
    cv::Mat back;
    cv::BackgroundSubtractorMOG2 bg;
    bg.set ("nmixtures", 3);
    bg.set("detectShadows",1);   
    bg.operator()(image,fore);
    bg.getBackgroundImage (back);
    cv::imshow("view", md(fore));
}

static void drawOptFlowMap(const cv::Mat& flow, cv::Mat& cflowmap, int step,
                           double, const cv::Scalar& color)
{
    for(int y = 0; y < cflowmap.rows; y += step)
        for(int x = 0; x < cflowmap.cols; x += step)
        {
            const cv::Point2f& fxy = flow.at<cv::Point2f>(y, x);
            line(cflowmap, cv::Point(x,y), cv::Point(cvRound(x+fxy.x), cvRound(y+fxy.y)),
                 color);
            circle(cflowmap, cv::Point(x,y), 2, color, -1);
        }
}

cv::Mat prevgray;
void farneback(cv::Mat image){    
    cv::Mat goutput,coutput,output;
    cv::Mat gray;
    try{    
        cvtColor(image, gray, cv::COLOR_BGR2GRAY);
        if(!prevgray.empty()){
            cv::calcOpticalFlowFarneback(prevgray,gray,goutput,0.5, 3, 15, 3, 5, 1.2, 0);
            cvtColor(prevgray, coutput, cv::COLOR_GRAY2BGR);
            drawOptFlowMap(goutput, coutput, 16, 1.5, cv::Scalar(0, 255, 0));
            cv::imshow("view", coutput)
        }
        swap(prevgray,gray);
    }catch(...){
        ROS_ERROR("Error Occur");
    }
    return;
}

bool control_callback(a53095838_assignment_4::cmd::Request &req,a53095838_assignment_4::cmd::Response &res){
    res.success = true;
    mode = req.mode;        
    return true;
}



void gscam_callback (const sensor_msgs::ImageConstPtr& frame){
    cv::Mat image = cv_bridge::toCvShare(frame, "bgr8")->image;
    switch(mode){
    case Control_Val_RAW:
        show(image);
        break;
    case Control_Val_Farneback:
        farneback(image);
        break;
    case Control_Val_MOG2:
        mog2(image);
        break;
    default:
        show(image);
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
