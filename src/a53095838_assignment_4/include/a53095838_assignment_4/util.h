#ifndef UTIL_HEADER_FILE
#define UTIL_HEADER_FILE

#include "../../../../devel/include/a53095838_assignment_4/cmd.h"
#include "std_msgs/String.h"
#include <ros/console.h>
#include <iostream>
#include <sstream>
#include "ros/ros.h"

using namespace std;
#define Image_channel "/camera/visible/image"
#define Control_channel "/processing_mode"

#define Control_Val_RAW 1
#define Control_Val_Farneback 2
#define Control_Val_MOG2 3

#define Control_Type int8_t

#endif /* UTIL_HEADER_FILE */
