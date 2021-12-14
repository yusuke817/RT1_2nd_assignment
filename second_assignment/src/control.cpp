#include <ros/ros.h>
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/Twist.h>
#include <sensor_msgs/LaserScan.h>
#include <tf/transform_datatypes.h>
#include "std_srvs/Empty.h"
#include "second_assignment/speed.h"
#include "second_assignment/speedup.h"

ros::ServiceClient client;
ros::Publisher pub;
geometry_msgs::Twist vel;

std_srvs::Empty res_server;
float dist_th = 1.5;
float sup = 0;
float speedup = 0;
float output = 0;
float plus = 0;
float original = 0;

/*
void ScanCallback (const sensor_msgs::LaserScan::ConstPtr &msg);
void SpeedCallback (const second_assignment::speedup::ConstPtr &aaa);
double sensor(double u[]);
*/

float sensor(float u[])
{
	float urg = 100;
	for(int j=0; j<90; j++)
	{
		if(u[j]<urg)
		{
			urg =u[j];
		} 
	}
	return urg;
}

void ScanCallback(const sensor_msgs::LaserScan::ConstPtr &msg) {

	int ranges = msg->ranges.size();
	float s[ranges];
	for(int i =0; i<ranges; i++)
	{
		s[i]=msg->ranges[i];
	}
	
	float right[101];
	float front[91];
	float left[101];
	
	for (int k = 0; k <= 100; k++)
	{
		right[k] = s[k];
	}
	for (int k = 300; k <= 390; k++)
	{
		front[k-300] = s[k];
	} 
	for (int k = 620; k <= 720; k++)
	{
		left[k-620] = s[k];
	}
	
	if(sensor(front) <= dist_th)
	{
		if(sensor(right)-sensor(left)> 0)
		{
			ROS_INFO("Turn right");
			vel.linear.x = 0.5;
			vel.angular.z = -1.0;
		}
		else if(sensor(right)-sensor(left)< 0)
		{			
			ROS_INFO("Turn left");			
			vel.linear.x = 0.5;
			vel.angular.z = +1.0;		
		}
		else
		{		
			ROS_INFO("Decrease");				
			vel.linear.x = 0.1;
			vel.angular.z = 0.0;		
		}
		
	}
	
	else //if (sensor(front) > dist_th)
	{
		ROS_INFO("straight");
		vel.linear.x =  1.0 + plus;
		vel.angular.z = 0.0;
	}
	
	ROS_INFO("%f", vel.linear.x);
	pub.publish(vel);
}

bool SpeedService(second_assignment::speed::Request &req, second_assignment::speed::Response &res) {
	ROS_INFO("serviceget");
	if (req.input != -1000.0){
	plus = req.input;
	res.output = plus;
	ROS_INFO("change");
	}
	else{
	ros::service::call("/reset_positions", res_server);
	ROS_INFO("reset");
	plus = 0;
	original=0.0;
	} 
	return true;
}

int main(int argc, char **argv)
{
	ROS_INFO("main");
    	ros::init(argc, argv, "driving_node");
	ros::NodeHandle nh;
	ros::Subscriber sub = nh.subscribe("/base_scan", 1, ScanCallback);
	pub = nh.advertise<geometry_msgs::Twist> ("/cmd_vel", 1);
	ros::ServiceServer service =  nh.advertiseService("/speed", SpeedService);
	//client = nh.serviceClient<second_assignment::speed>("/speed");
	//ros::ServiceClient client = n.serviceClient<second_assignment::speed:>("add_speed");
	//beginner_tutorials::AddTwoInts srv;
	//srv.request.a = atoll(argv[1]);
	//ros::Subscriber sub2 = nh.subscribe("/speedup", 1, SpeedCallback);	  
	ros::spin();
	return 0;
}

/*
void ScanCallback (const sensor_msgs::LaserScan::ConstPtr &msg);
//void SpeedCallback (const second_assignment::speedup::ConstPtr &aaa);
float sensor(float u[]);

int main(int argc, char **argv)
{
	ROS_INFO("main");
    	ros::init(argc, argv, "driving_node");
	ros::NodeHandle nh;
	pub = nh.advertise<geometry_msgs::Twist> ("/cmd_vel", 1); 
	ros::Subscriber sub = nh.subscribe("/base_scan", 1, ScanCallback);  
	ros::spin();
	return 0;
}

float sensor(float u[])
{
	float urg = 100;
	for(int j=0; j<50; j++)
	{
		if(u[j]<urg)
		{
			urg =u[j];
		} 
	}
	return urg;
}

void ScanCallback(const sensor_msgs::LaserScan::ConstPtr &msg) {

	geometry_msgs::Twist vel;
	int ranges = msg->ranges.size();
	float s[ranges];
	for(int i =0; i<ranges; i++)
	{
		s[i]=msg->ranges[i];
	}
	
	float right[101];
	float front[91];
	float left[101];
	
	for (int k = 0; k <= 100; k++)
	{
		right[k] = s[k];
	}
	for (int k = 300; k <= 390; k++)
	{
		front[k-300] = s[k];
	}
	for (int k = 620; k <= 720; k++)
	{
		left[k-620] = s[k];
	}
	
	if(sensor(front) <= dist_th)
	{
		if(sensor(right)-sensor(left)> 0)
		{
			vel.linear.x = 0.1;
			vel.angular.z = -1.0;
		}
		else if(sensor(right)-sensor(left)< 0)
		{						
			vel.linear.x = 0.1;
			vel.angular.z = +1.0;		
		}
		else
		{						
			vel.linear.x = 0.1;
			vel.angular.z = 0.0;		
		}
		
	}
	
	else //if (sensor(front) > dist_th)
	{
		vel.linear.x =  2.0 + speedup;
		vel.angular.z = 0.0;
	}

	pub.publish(vel);
}
*/


 // vscode://vscode.github-authentication/did-authenticate?windowid=3&code=edd27752a2f889193233&state=6b3b3d8d-a362-4139-92fa-7c3e158b6ae4
 	//ROS_INFO("@[%f]", output); 
