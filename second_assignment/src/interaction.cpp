#include <ros/ros.h>
//#include <nav_msgs/Odometry.h>
//#include <geometry_msgs/Twist.h>
//#include <sensor_msgs/LaserScan.h>
#include "second_assignment/speed.h"
//#include "second_assignment/speedup.h"
#include "std_srvs/Empty.h"
//#include "std_srvs/EmptyResponse.h"

float original = 0.0;
float speedmeter = 0.0;

int main (int argc, char **argv) 
{
	ros::init(argc, argv, "speed_server_node"); 
	ros::NodeHandle nh;
	ros::ServiceClient client = nh.serviceClient<second_assignment::speed>("/speed");
	second_assignment::speed speed_srv;
	char s;
	
	while(1){
	std::cout << "Increase: a or Decrease: d or Reset: z or Finish: f?\n";
	std::cin >> s;
	
	if(s == 'a'){
		if(original > -100.0 && original <=3.5){
		original += 0.5;
		ROS_INFO("increase");
		speed_srv.request.input = original;
	 	//client.waitForExistence();
		client.call(speed_srv);
		//speedmeter=speed_srv.response.output+1.0;
		//ROS_INFO("speed= %.1f+1.0", speed_srv.response.output);
		//ROS_INFO("speed= %.1f+1.0", speed_srv.response.output);
		//continue;
		}
		else{
		ROS_INFO("Maximum speed: 5.0");
		//ROS_INFO("original= %.1f", original);
		speed_srv.request.input = original;
		client.call(speed_srv);
		//continue;		
		}
		
	}
	else if(s == 'd'){
		if(original >=-0.5){
		original -= 0.5;
		ROS_INFO("decrease");
		speed_srv.request.input = original;
	 	//client.waitForExistence();
		client.call(speed_srv);
		//speedmeter=speed_srv.response.output+1.0;
		//ROS_INFO("speed= %.1f", speed_srv.response.output);
		//continue;
		}
		else{
		ROS_INFO("stop");
		speed_srv.request.input = original;
		client.call(speed_srv);
		//continue;		
		}		
	}
	else if(s == 'z'){
		original = -1000;
		ROS_INFO("position & speed reset: 1.0");
		speed_srv.request.input = original;
	 	//client.waitForExistence();
		client.call(speed_srv);
		original = 0.0;
		//continue;
	}
	
	else if(s == 'f'){
		break;
		//continue;
	}
	
	else{
		std::cout << "input again\n";
		//continue;
	}
	
	//pub = nh.advertise<second_assignment::speedup>("/speedup", 100);   
	//client = nh.serviceClient<second_assignment::speed>("/speed");
	//ros::Subscriber sub = nh.subscribe("/base_scan", 1, CommandCallback);
	
	ros::spinOnce();
	}
	return 0;
}
