#include <ros/ros.h>
#include <std_msgs/Float64MultiArray.h>

void cbEncoderSensor(const std_msgs::Float64MultiArray &msg){
    ROS_INFO("encoder data : %f, %f, %f, %f, %f, %f", msg.data[0], msg.data[1], msg.data[2], msg.data[3], msg.data[4], msg.data[5]);
}

void cbForceSensor(const std_msgs::Float64MultiArray &msg){
    ROS_INFO("force data : %f, %f, %f, %f, %f, %f", msg.data[0], msg.data[1], msg.data[2], msg.data[3], msg.data[4], msg.data[5]);
}

void cbDrivingTorque(const std_msgs::Float64MultiArray &msg){
    ROS_INFO("driving torque : %f, %f, %f, %f, %f, %f", msg.data[0], msg.data[1], msg.data[2], msg.data[3], msg.data[4], msg.data[5]);
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "driving_torque_listener_node");
    ros::NodeHandle nh;

    ros::Rate loop_rate(10);

    ros::Subscriber subEncoder = nh.subscribe("/encoder_sensor", 1, cbEncoderSensor);
    ros::Subscriber subForce = nh.subscribe("/force_sensor", 1, cbForceSensor);
    ros::Subscriber subDrivingTorque = nh.subscribe("/driving_torque", 1, cbDrivingTorque);

    ros::spin();
}