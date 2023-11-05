#include <ros/ros.h>
#include <std_msgs/Float64MultiArray.h>
#include <ros/package.h>

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include <time.h>
#include <vector>

void load_data(std::string file_name, std::vector<double> *data, std::string delimiter, unsigned int *size)
{
	data->clear();
	FILE *fp_in;
	const int buffer = 1000000;
	char *ptr, basic[buffer];
	fp_in = fopen(file_name.c_str(), "r");
	unsigned int row = 0, col = 0;
	while (fgets(basic, buffer, fp_in) != NULL)
	{
		row++;
		ptr = strtok(basic, delimiter.c_str());
		while (ptr != NULL) {
			data->push_back(atof(ptr));
			ptr = strtok(NULL, delimiter.c_str());
			col++;
		}
	}
	fclose(fp_in);
	if(size != NULL){
		size[0] = row;
		size[1] = (col/row);
	}
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "force_sensor_talker_node");
    ros::NodeHandle nh;

    ros::Publisher pub = nh.advertise<std_msgs::Float64MultiArray>("force_sensor", 1);

    ros::Rate loop_rate(10);

	std::string path = ros::package::getPath("force_sensor_talker");
	std::string file_name = path + "/data/force_data.csv";
	std::vector<double> data;
	uint data_size[2] = {0, 0};
	uint row, col;
	load_data(file_name, &data, ",", data_size);
	row = data_size[0];
	col = data_size[1];

    int indx = 0;
    while(ros::ok())
    {
        std_msgs::Float64MultiArray msg;

        msg.data.push_back(data[indx*col + 0]);
        msg.data.push_back(data[indx*col + 1]);
        msg.data.push_back(data[indx*col + 2]);
        msg.data.push_back(data[indx*col + 3]);
        msg.data.push_back(data[indx*col + 4]);
        msg.data.push_back(data[indx*col + 5]);

        ROS_INFO("%f, %f, %f, %f, %f, %f", msg.data[0], msg.data[1], msg.data[2], msg.data[3], msg.data[4], msg.data[5]);

        pub.publish(msg);

        ros::spinOnce();

        loop_rate.sleep();
        indx++;

		if(indx >= row)
			indx = 0;
    }
}