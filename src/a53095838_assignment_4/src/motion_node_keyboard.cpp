#include "../include/a53095838_assignment_4/util.h"
#define SLEEP 4

bool change_mode(ros::ServiceClient client, Control_Type mode){
    a53095838_assignment_4::cmd srv;
    srv.request.mode = mode;
    return client.call(srv);
};

int main(int argc, char **argv){
    string node_name = "motion_keyboard";
    ros::init(argc, argv, node_name);
    ros::NodeHandle n;
    ros::service::waitForService(Control_channel);   
    ros::ServiceClient client = n.serviceClient<a53095838_assignment_4::cmd>(Control_channel);
    Control_Type mode;
    
    
    ros::Duration duration(SLEEP);
    duration.sleep();
    cout <<"\n\n===============================================";
    cout << "\nHello, please choose a video processing mode.";
    while(ros::ok()){
        cout<<"\nAvailable modes:\n";
        cout<<"    ["<<Control_Val_EXIT<<"] Exit\n";
        cout<<"    ["<<Control_Val_RAW<<"] Raw Camera Mode\n";
        cout<<"    ["<<Control_Val_Farneback<<"] Farneback Mode\n";
        cout<<"    ["<<Control_Val_MOG2<<"] MOG2 Mode\n";
        cout<<"You Choice:";
        cin >> mode;
        cout << "Ok, you choose mode:[" << mode <<"]\nSending Commands....";
        mode -= 48; // "number" -> number, ascii
        if(mode == Control_Val_EXIT){
            break;
        }        
        if(change_mode(client, mode)){
            cout<<"Mode changed successfully";
        }else{
            cout<<"Mode change failed";
        }
        cout<<"\n-------------------------";
    }
    cout << "Good Bye\n\n\n\n";
    
    return 0;
}
