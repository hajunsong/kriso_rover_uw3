#include <ros/ros.h>

int main(int argc, char** argv){
    ros::init(argc, argv, "rover_uw3_node");

    ros::NodeHandle nh;

    ros::AsyncSpinner spinner(4);
    spinner.start();

    ros::waitForShutdown();

    return 0;
}