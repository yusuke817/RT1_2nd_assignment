#include <ros/ros.h>
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/Twist.h>
#include <sensor_msgs/LaserScan.h>
#include <tf/transform_datatypes.h>
#include "std_srvs/Empty.h"
#include "second_assignment/speed.h"
#include "second_assignment/speedup.h"

ros::ServiceClient client;
ros::Publisher pub; //init publisher
geometry_msgs::Twist vel;

std_srvs::Empty res_server;
float dist_th = 1.5;// the threshold of the distance between the robot and walls
float sup = 0;
float speedup = 0;
float output = 0;
float plus = 0;
float original = 0;

//calculating the shortest distance in the array values collected with laser sensors
float sensor(float u[])
{
	float urg = 100;
	for(int j=0; j<90; j++)
	{
		if(u[j]<urg)
		{
		// updating the distance
			urg =u[j];
		} 
	}
	// returning the distance
	return urg;
}

// Execcuting in receiving the message from laser sensor
void ScanCallback(const sensor_msgs::LaserScan::ConstPtr &msg) {

	int ranges = msg->ranges.size();
	float s[ranges];
	for(int i =0; i<ranges; i++)
	{
		s[i]=msg->ranges[i];
	}
	// to get the information on the distance in each sectons: right, front and left.
	float right[101];
	float front[91];
	float left[101];
	
	// right section
	for (int k = 0; k <= 100; k++)
	{
		right[k] = s[k];
	}
	// front section
	for (int k = 300; k <= 390; k++)
	{
		front[k-300] = s[k];
	} 
	// left section
	for (int k = 620; k <= 720; k++)
	{
		left[k-620] = s[k];
	}
	
	// when the robot is close to the wall, the robot will decrease the speed.
	if(sensor(front) <= dist_th)
	{
		// left wall is close
		if(sensor(right)-sensor(left)> 0)
		{
			ROS_INFO("Turn right");
			vel.linear.x = 0.5;
			vel.angular.z = -1.0;
		}
		// right wall is close
		else if(sensor(right)-sensor(left)< 0)
		{			
			ROS_INFO("Turn left");			
			vel.linear.x = 0.5;
			vel.angular.z = +1.0;		
		}
		// both walls are close
		else
		{		
			ROS_INFO("Decrease");				
			vel.linear.x = 0.1;
			vel.angular.z = 0.0;		
		}
		
	}
	
	// robot is not close to the wall
	else
	{
		ROS_INFO("straight");
		vel.linear.x =  1.0 + plus;
		vel.angular.z = 0.0;
	}
	
	// observing the linear velocity 
	ROS_INFO("%f", vel.linear.x);
	// publishing the velocity 
	pub.publish(vel);
}

//executing when speed_server node calls the services
bool SpeedService(second_assignment::speed::Request &req, second_assignment::speed::Response &res) {
	ROS_INFO("serviceget");
	// except "reset", the increment of the speed is updated
	if (req.input != -1000.0){
	plus = req.input;
	res.output = plus;
	ROS_INFO("change");
	}
	// in reset, resetting the position and the speed is done
	else{
	// resetting the position is done with the service call
	ros::service::call("/reset_positions", res_server);
	ROS_INFO("reset");
	// resetting the speed is done as well
	plus = 0;
	original=0.0;
	} 
	return true;
}

int main(int argc, char **argv)
{
	ROS_INFO("main");
	
	//initializing the node and setting up the node hundle
    	ros::init(argc, argv, "driving_node");
	ros::NodeHandle nh;
	
	//subscribing /base_scan topics
	ros::Subscriber sub = nh.subscribe("/base_scan", 1, ScanCallback);
	pub = nh.advertise<geometry_msgs::Twist> ("/cmd_vel", 1);
	// advertising the "speed" services to the client
	ros::ServiceServer service =  nh.advertiseService("/speed", SpeedService);
	ros::spin();
	return 0;
}
