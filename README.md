# RT1_2nd_assignment

# Purpose
I learned how to use ROS expecially in Pub/Sub communications and services.

# Tasks
①Robot can drive in the circuit automatically without crashing on the walls.
<br>
②An user can change the speed of the robot.

# Explanation about the situation and implementation
The blue dot in the circuit is the robot controlled in this assignment.
<br>
There are two nodes I developped: driving_node in control.cpp and speed_server_node in interaction.cpp.
<br>
A.Driving_node is developped for controlling the movement of the robot.
<br>
B.Speed_server_node is developped for changing the speed of the robot and resetting the position of the robot depending on the user inputs.

<img width="772" alt="ros_stage" src="https://user-images.githubusercontent.com/46062824/145958992-266706c8-2900-4d03-b4f2-cdf08531265c.png">

# Flowchart
![RT1_2_flowchart](https://user-images.githubusercontent.com/46062824/146186598-33f5dcfd-0092-40b7-878b-9e562c1dd977.JPG)

# How to execute
<img width="1402" alt="terminal×4" src="https://user-images.githubusercontent.com/46062824/146006462-8eb17c5e-ea8a-4541-b6eb-e9bb1c22b2a5.png">
<br>
1. Preparation
roscore &
<br>
catkin_make
<br>
2. Running
<br>
You can run the program with 3 nodes in each terminals respectively.
<br>
rosrun stage_ros stageros $(rospack find second_assignment)/world/my_world.world
<br>
rosrun second_assignment driving_node
<br>
rosrun second_assignment speed_server_node

```
With services
```

# The expalanation about each nodes
A.control console(driving_node)
With pub-sub communications, I implemented the function of automatic driving. After running the node, the robot will drive. In this terminal, the modes and the speeds are displayed continually. There are four modes depending on the movement of the robot: straight, turn right, turn left and decrease. When the robot doesn't detect anything in front of it, it will move without decreasing the speed. On the other hand, when the robot detects something in front of it, it will decrease the speed. Also, in this case, depending on the place of the wall, the robot will decide the turning direction, such as turning right and turning left.

B.server console(speed_server_node)
With services, I implemented the function of the change of the speeds and resetting the position. You can give the robot four kinds of commands. One is the command for the change of the speeds. You can increase the speed when you input a, and decrease it when you input d. Another is the command for moving the robot into its original place. You can restart the movement of the robot from the original point anytime when you input r.
<br>
You can set the robot's speed from 0.0 to 5.0. You can increase or decrese the speed every 0.5 speeds 

# How to execute
I made the folder called "second_assignment" to realize the tasks. I added many comments in the code, so I would like you to read. 

<br>
Mainly, I did two things. ①One was to get the information on golden boxes in the function of "find_token." (Line71-92) ②The other was implementation of catching silver boxes and avoiding the wall composed of golden boxes done in main function. (Line95-137) Each of the thresholds related to distances and angles is decided experimentally.
<br>
①Getting the information on golden boxes
<img width="1026" alt="スクリーンショット 2021-11-04 15 18 16" src="https://user-images.githubusercontent.com/46062824/140330702-965d2a2b-c6c2-47a6-afee-f88a67b7d82f.png">

<br>
②Implementation of catching silver boxes and avoiding the wall composed of golden boxes

# rqt-graph
I made the folder called "second_assignment." Driving node can get the user input from speed server node with the speed.srv.
<img width="1382" alt="RT2_rqt" src="https://user-images.githubusercontent.com/46062824/146010312-9e4327dd-0b36-4c1c-b1f4-5632a9c72ed9.png">

# Result on YouTube
Result is shown in the video below. I recommend you that you should change the resolution into 1080p to read the characters in the terminals.
<br>
[![](https://img.youtube.com/vi/FFKL9n6XOKk/0.jpg)](https://www.youtube.com/watch?v=FFKL9n6XOKk)
