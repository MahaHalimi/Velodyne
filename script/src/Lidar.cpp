#include "ros/ros.h"
#include "sensor_msgs/PointCloud2.h"
#include "std_msgs/Float32.h"
#include "std_msgs/Bool.h"
#include "sensor_msgs/PointCloud.h"
#include "sensor_msgs/point_cloud_conversion.h"
#include "std_msgs/Float64.h"
#include <limits>
#include <math.h>
#include <vector>
#include <stdio.h>


void DataLidar(const sensor_msgs::PointCloud2& msg)
{
	sensor_msgs::PointCloud out_cloud;
	sensor_msgs::convertPointCloud2ToPointCloud(msg, out_cloud);

	std::vector<float> x_vect;
	std::vector<float> y_vect;
	std::vector<float> z_vect;

	float angle_max =  105.;
	float angle_min =  70.;


	for(int i = 0 ; i < out_cloud.points.size(); ++i)
	{
		float x = out_cloud.points[i].x;
	    float y = out_cloud.points[i].y;
	    float z = out_cloud.points[i].z;
	    float dist = std::sqrt(x*x+y*y);
	    float angle = (atan2(y,x)*180./M_PI);

        if(angle > angle_min and angle < angle_max)
		{		    
		  	ROS_INFO("Hello");
		    x_vect.push_back(x);
		    y_vect.push_back(y);
		    z_vect.push_back(z);

		/*	if ( x_vect.size()> 20 || z_vect.size()> 20)

			{ 
				//changer de direction 

			}
		*/	

		}
		else
		{
			ROS_INFO("Je ne vois pas de points");
		}






	}
}


int main(int argc, char **argv)
{

	ros::init(argc, argv, "Lidar_node");

	ros::NodeHandle n;
	ros::Subscriber sub_cloud = n.subscribe("/velodyne_points", 1000, DataLidar);
	ros::Rate loop_rate(10);
	ros::spin();

	return 0;
}








