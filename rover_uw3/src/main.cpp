#include <ros/ros.h>
#include <std_msgs/Float64MultiArray.h>

#include "robotarm.h"

static int cnt = 0;
static std::vector<double> encoder;
static double force[6];

void cbEncoderSensor(const std_msgs::Float64MultiArray &msg){
    // ROS_INFO("encoder data : %f, %f, %f, %f, %f, %f", msg.data[0], msg.data[1], msg.data[2], msg.data[3], msg.data[4], msg.data[5]);
    for(uint i = 0; i < 6; i++){
        encoder.push_back(msg.data[i]);
    }
    if(encoder.size() > 18){
        encoder.erase(encoder.begin(), encoder.begin()+6);
    }
}

void cbForceSensor(const std_msgs::Float64MultiArray &msg){
    // ROS_INFO("force data : %f, %f, %f, %f, %f, %f", msg.data[0], msg.data[1], msg.data[2], msg.data[3], msg.data[4], msg.data[5]);
    memcpy(force, msg.data.data(), sizeof(double)*6);
}

int main(int argc, char** argv){
    ros::init(argc, argv, "rover_uw3_node");

    ros::NodeHandle nh;

    ros::Rate loop_rate(100);

    ros::Subscriber subEncoder = nh.subscribe("/encoder_sensor", 1, cbEncoderSensor);
    ros::Subscriber subForce = nh.subscribe("/force_sensor", 1, cbForceSensor);

    ros::Publisher pubJoint = nh.advertise<std_msgs::Float64MultiArray>("joint_driving_torque", 1);

    RobotArm robotArm(6, 6);
    double driving_torque[6] = {0,};

    while(ros::ok())
    {
        // ROS_INFO("force data : %f, %f, %f, %f, %f, %f", force[0], force[1], force[2], force[3], force[4], force[5]);

        // if(encoder.size() >= 6)
        //     ROS_INFO("encoder cur    data : %f, %f, %f, %f, %f, %f", encoder[0], encoder[1], encoder[2], encoder[3], encoder[4], encoder[5]);
        // if(encoder.size() >= 12)
        //     ROS_INFO("encoder prev 1 data : %f, %f, %f, %f, %f, %f", encoder[6], encoder[7], encoder[8], encoder[9], encoder[10], encoder[11]);
        if(encoder.size() >= 18){
            // ROS_INFO("encoder prev 2 data : %f, %f, %f, %f, %f, %f", encoder[12], encoder[13], encoder[14], encoder[15], encoder[16], encoder[17]);
            
            robotArm.run(encoder.data(), force, driving_torque);
            
            ROS_INFO("driving_torque : %f, %f, %f, %f, %f, %f", driving_torque[0], driving_torque[1], driving_torque[2], driving_torque[3], driving_torque[4], driving_torque[5]);
            
            std_msgs::Float64MultiArray msg;

            for(uint i = 0; i < 6; i++){
                msg.data.push_back(driving_torque[i]);
            }

            pubJoint.publish(msg);
        }


        ros::spinOnce();

        loop_rate.sleep();
    }

    return 0;
}