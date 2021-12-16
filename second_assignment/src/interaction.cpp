#include <ros/ros.h>
#include "second_assignment/speed.h"
#include "std_srvs/Empty.h"

float original = 0.0;
float speedmeter = 0.0;

int main (int argc, char **argv) 
{
	ros::init(argc, argv, "speed_server_node"); 
	ros::NodeHandle nh;
	//calling the service
	ros::ServiceClient client = nh.serviceClient<second_assignment::speed>("/speed");
	second_assignment::speed speed_srv;
	char s;
	
	while(1){
	//guide for users
	std::cout << "Increase: a or Decrease: d or Reset: z or Finish: f?\n";
	//getting the user input
	std::cin >> s;
	
	// when users want to increase the speed
	if(s == 'a'){
		//liniting the range of the speed
		if(original > -100.0 && original <=3.5){
		// increasing the speed
		original += 0.5;
		ROS_INFO("increase");
		//storing the user input into the request of the server
		speed_srv.request.input = original;
		//sending a request to the server
		client.call(speed_srv);
		}
		//stopping the increase when the speed is too much
		else{
		ROS_INFO("Maximum speed: 5.0");
		speed_srv.request.input = original;
		client.call(speed_srv);	
		}
		
	}
	// when users want to decrease the speed
	else if(s == 'd'){
		if(original >=-0.5){
		// decreasing the speed
		original -= 0.5;
		ROS_INFO("decrease");
		speed_srv.request.input = original;
		client.call(speed_srv);
		}
		//stopping the decrease when the speed is too small
		else{
		ROS_INFO("stop");
		speed_srv.request.input = original;
		client.call(speed_srv);	
		}		
	}
	// when users want to reset the position and the speed
	else if(s == 'z'){
		// changing the "original" value to change the mode into the initial state
		original = -1000;
		ROS_INFO("position & speed reset: 1.0");
		speed_srv.request.input = original;
		client.call(speed_srv);
		original = 0.0;
	}
	
	// when users want to finish the node itself
	else if(s == 'f'){
		break;
	}
	
	//If users cannot give the right four commands shown above, they will be requested their user commands again
	else{
		std::cout << "input again\n";
	}
	
	ros::spinOnce();
	}
	return 0;
}
