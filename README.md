# RT1_2nd_assignment

# Purpose
①Robot can drive in the circuit automatically without crashing on the walls.
<br>
②An user can change the speed of the robot.

# Explanation about the situation and implementation
The blue dot in the circuit is the robot controlled in this assignment.
<br>
There are two nodes I developped: driving_node and speed_server_node.
<br>
A.Driving_node is developped for controlling the movement of the robot.
<br>
B.Speed_server_node is developped for changing the speed of the robot and moving the robot to the initial position depending on the user inputs.

# Flowchart
[]([![Flowchart](https://i.gyazo.com/23ec5ad130141480e6bdb4d353887a55.jpg)](https://gyazo.com/23ec5ad130141480e6bdb4d353887a55))
![IMG_7638](https://user-images.githubusercontent.com/46062824/141991529-b14621de-ef71-4b3e-ae31-452906d890df.jpg)
<img width="288" alt="スクリーンショット 2021-11-16 14 10 54" src="https://user-images.githubusercontent.com/46062824/141991388-f6305256-7f0a-4914-846e-fbd821e94354.png">

# How to execute
roscore

catkin_make

rosrun second_assignment driving_node
rosrun second_assignment speed_server_node

# How to operate the robot
A.control console(driving_node)


B.server console(speed_server_node)
You do not input anything

C.input console(UI_node)
You can give the robot four kinds of commands. One is the command for the change of the speeds. You can increase the speed when you input a, and decrease it when you input d. The other is the command for moving the robot into its original place. You can restart the movement of the robot from the original point anytime when you input r.

# How to execute
I made the file called "rt_1101" to realize the tasks. I added many comments in the code, so I would like you to read. 

<br>
Mainly, I did two things. ①One was to get the information on golden boxes in the function of "find_token." (Line71-92) ②The other was implementation of catching silver boxes and avoiding the wall composed of golden boxes done in main function. (Line95-137) Each of the thresholds related to distances and angles is decided experimentally.
<br>
①Getting the information on golden boxes
<img width="1026" alt="スクリーンショット 2021-11-04 15 18 16" src="https://user-images.githubusercontent.com/46062824/140330702-965d2a2b-c6c2-47a6-afee-f88a67b7d82f.png">

<br>
②Implementation of catching silver boxes and avoiding the wall composed of golden boxes
<img width="1086" alt="スクリーンショット 2021-11-04 15 22 05" src="https://user-images.githubusercontent.com/46062824/140331404-b354c099-3601-4ae9-a7f3-1a78e9ff0350.png">
<img width="912" alt="スクリーンショット 2021-11-04 15 24 05" src="https://user-images.githubusercontent.com/46062824/140331417-4a72510d-57bc-4b91-9917-746d4e75997c.png">

# Result on YouTube
Result is shown in the video below.
<br>
[![](https://www.youtube.com/watch?v=FFKL9n6XOKk)
