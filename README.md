# RT1_2nd_assignment

# Purpose and Summary
I created second_assignment package in order to learn how to use ROS expecially in Pub/Sub communications and services.

# Tasks
①Robot can drive in the circuit automatically without crashing on the walls.
<br>
②An user can change the speed of the robot.

# Explanation about the situation and implementation
The blue dot in the circuit is the robot controlled in this assignment.
<br>
There are two nodes I developped: driving_node in control.cpp and speed_server_node in interaction.cpp.
<br>
1. Driving_node is developped for controlling the movement of the robot.
2. Speed_server_node is developped for changing the speed of the robot and resetting the position of the robot depending on the user inputs.

<img width="772" alt="ros_stage" src="https://user-images.githubusercontent.com/46062824/145958992-266706c8-2900-4d03-b4f2-cdf08531265c.png">

# Flowchart
The flowchart of the program is shown below.
<br>

![RT1_2_flowchart](https://user-images.githubusercontent.com/46062824/146186598-33f5dcfd-0092-40b7-878b-9e562c1dd977.JPG)

# How to execute
The program can be run with 4 terminals shown below: main, stage_ros, the one for driving_node and the one for speed_server_node.
<img width="1402" alt="terminal×4" src="https://user-images.githubusercontent.com/46062824/146006462-8eb17c5e-ea8a-4541-b6eb-e9bb1c22b2a5.png">
<br>
1. Preparation

You should run ros itself and compile the program.

```
roscore &
catkin_make
```
2. Running

You should run the program with 3 nodes in each terminals respectively.

```
rosrun stage_ros stageros $(rospack find second_assignment)/world/my_world.world
```

```
rosrun second_assignment driving_node
```

```
rosrun second_assignment speed_server_node
```

# The expalanation about each nodes for operation

1. "driving_node" in control.cpp.

With pub-sub communications, I implemented the function of automatic driving. After running the node, the robot will drive. In this terminal, the modes and the speeds are displayed continually. There are four modes depending on the movement of the robot: straight, turn right, turn left and decrease. 
   - Driving stragightforward without decreasing the speed when the robot doesn't detect anything in front of it. 
   - Decreasing when the robot detects something in front of it. Also, in this case, depending on the place of the wall, the robot will decide the turning direction
     - Turning right when the robot is close to left wall.
     - Just decreasing when the robot is close to both left and right walls.
     - Turning left when the robot is close to right wall.

2. "speed_server_node" in interaction.cpp

With services, I implemented the function of the change of the speeds and resetting the position. You can give the robot four kinds of commands. You can set the robot's speed from 0.0 to 5.0. You can increase or decrese the speed every 0.5 speeds. 
<br>
  - 'a' for increasing the speed 
  - 'd' for increasing the speed
  - 'r' for resetting the postion and the speed. You can move the robot into its original place anytime.
  - 'f' for terminating the node itself. 

# How to develop each files

This program has two source codes: control.cpp and interaction.cpp.

1. control.cpp including "driving_node".

There are four functions in control.cpp
   - Driving stragightforward without decreasing the speed when the robot doesn't detect anything in front of it. 
   - Decreasing when the robot detects something in front of it. Also, in this case, depending on the place of the wall, the robot will decide the turning direction
     - Turning right when the robot is close to left wall.
     - Just decreasing when the robot is close to both left and right walls.
     - Turning left when the robot is close to right wall.

2. interaction.cpp including "speed_server_node" 

There is only one main function in interaction.cpp. There are three main processes: ①getting user input, ②storing the user input into the request of the server and ③sending a request to the server as a client.

With services, I implemented the function of the change of the speeds and resetting the position. You can give the robot four kinds of commands. You can set the robot's speed from 0.0 to 5.0. You can increase or decrese the speed every 0.5 speeds. 
<br>
  - 'a' for increasing the speed 
  - 'd' for increasing the speed
  - 'r' for resetting the postion and the speed. You can move the robot into its original place anytime.
  - 'f' for terminating the node itself. 

# rqt-graph
I made the folder called "second_assignment." I show you the realationships between the nodes in rqt-graph. Driving node sends the commands on the velocity to stageros node. Also, driving node can get the updated velocity based on user input from speed server node with the speed.srv.
<img width="1382" alt="RT2_rqt" src="https://user-images.githubusercontent.com/46062824/146010312-9e4327dd-0b36-4c1c-b1f4-5632a9c72ed9.png">

# Result on YouTube
Result is shown in the video below. I recommend you that you should change the resolution into 1080p to read the characters in the terminals.
<br>
[![](https://img.youtube.com/vi/FFKL9n6XOKk/0.jpg)](https://www.youtube.com/watch?v=FFKL9n6XOKk)
