#include "../include/a53095838_assignment_4/util.h"
#define FRAME(i,j) frame->data[j*frame->width+i]
#define show(x) cv::imshow("view", x)
#define MOG2_THRESHOLD 500

Control_Type mode = Control_Val_MOG2;

void mog2_md(cv::Mat fore, cv::Mat origin)
{
    cv::imshow("view", fore);
	
}


void fb_md(cv::Mat flow, cv::Mat origin){
    cv::imshow("view", flow);    
}


cv::BackgroundSubtractorMOG2 bg(4,16.0f);
void mog2(cv::Mat image)
{
    //cv::Mat fore;
    cv::Mat back;
    cv::Mat buff1;
    bg.operator()(image, buff1);
    bg.set("nmixtures",5);     
    bg.getBackgroundImage(back);

    // cv::Mat buff2;
//     cv::GaussianBlur(buff1, buff2, cv::Size(9, 9), 0, 0);
//     cv::threshold(buff2, buff1, 64, 255, cv::THRESH_BINARY);

//     cv::Mat erode_kernel = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(11, 11));
//     cv::Mat dilate_kernel = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(11, 11));

//     cv::erode(buff1, buff2, erode_kernel);
//     cv::dilate(buff2, buff1, dilate_kernel);

//     std::vector<std::vector<cv::Point> > contours;
//     cv::Scalar color(255, 255, 255);
//     cv::findContours(buff1, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
// //	cv::drawContours(buff1, contours, -1, color);

//     std::vector<cv::Rect> boundingRects(contours.size());

//     for (int i = 0 ;i < contours.size(); ++i)
//     {
//         boundingRects[i] = cv::boundingRect(contours[i]);	
//         cv::rectangle(image, boundingRects[i], color, 2, 8, 0);
//     }
//     show(image);

    cv::Mat buff2;
    cv::GaussianBlur(buff1, buff2, cv::Size(9, 9), 0, 0);
    cv::threshold(buff2, buff1, 64, 255, cv::THRESH_BINARY);
    std::vector<std::vector<cv::Point> > contours;
    std::vector<cv::Rect> rects;
    cv::Scalar color(255, 255, 255);
    cv::findContours(buff1, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
    cv::drawContours(buff1, contours, -1, color);
    for (uint i=0; i < contours.size(); i++) {
        cv::Rect rect = cv::boundingRect(contours[i]);
        
        if(rect.width*rect.height> MOG2_THRESHOLD){
            // ROS_INFO("%d",rect.width*rect.height);
            rects.push_back(rect);
            cv::rectangle(image, cvPoint(rect.x, rect.y), cvPoint(rect.x+rect.width, rect.y+rect.height), cvScalar(0, 0, 255, 0), 2, 8, 0);
        }
    }
    show(image);

}

void flow2speed(const cv::Mat& flow, cv::Mat& speed) // converts a velocity field to a grayscale speed image
{
    speed.create(flow.rows, flow.cols, CV_32F);

    float*  flowArray = (float*)( flow.data);
    float* speedArray = (float*)(speed.data);
    
    for (int x = 0; x < flow.cols; ++x)
    {
		for (int y = 0; y < flow.rows; ++y)
		{
            float u = flowArray[2*(flow.rows*x + y) + 0];
            float v = flowArray[2*(flow.rows*x + y) + 1];
            float u2 = u*u,v2 = v*v;
            if(v2 + u2 > 1)            
                speedArray[flow.rows*x + y] = u2+v2;
            else
                speedArray[flow.rows*x + y] = 0;
        }
    }
}


cv::Mat prevgray;
void farneback(cv::Mat image)
{
    cv::Mat goutput,coutput,output;
    cv::Mat gray;
	cv::Mat buff1, buff2;
    try{    
        cvtColor(image, gray, cv::COLOR_BGR2GRAY);
        if(!prevgray.empty()){
            cv::calcOpticalFlowFarneback(prevgray,gray,goutput,0.5, 3, 15, 3, 5, 1.2, 0);
            flow2speed(goutput, buff1);

		    cv::GaussianBlur(buff1, buff2, cv::Size(9, 9), 0, 0);
		    cv::threshold(buff2, buff1, 4, 100, cv::THRESH_BINARY);
			buff1.convertTo(buff2, CV_8UC1);

		    std::vector<std::vector<cv::Point> > contours;
		    std::vector<cv::Rect> rects;
		    cv::Scalar color(255, 255, 255);
		    cv::findContours(buff2, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
//		    cv::drawContours(buff2, contours, -1, color);
		    for (uint i=0; i < contours.size(); i++)
			{
		        cv::Rect rect = cv::boundingRect(contours[i]);
        
				if(rect.width*rect.height> MOG2_THRESHOLD)
				{
					rects.push_back(rect);
					cv::rectangle(image, cvPoint(rect.x, rect.y), cvPoint(rect.x+rect.width, rect.y+rect.height), cvScalar(0, 0, 255, 0), 2, 8, 0);
				}
			}
            show(image);
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

    // cv::namedWindow("other");
    // cv::startWindowThread();

    
    
    ros::spin();
    cv::destroyWindow("view");
    // cv::destroyWindow("other");
    return 0;
}
