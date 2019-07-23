#!/bin/bash

CATKIN_DIR=/home/workspace/catkin_ws
WORLD_DIR=$CATKIN_DIR/src/RoboND-HomeServiceRobot-Project/world/

# Load environment variables
source $CATKIN_DIR/devel/setup.bash;

# Launch the turtlebot in the customized world
xterm -e "roslaunch turtlebot_gazebo turtlebot_world.launch world_file:=$WORLD_DIR/l.world " &
sleep 5

# Start gmapping
xterm -e "roslaunch turtlebot_gazebo gmapping_demo.launch custom_gmapping_launch_file:=$CATKIN_DIR/src/RoboND-HomeServiceRobot-Project/turtlebot_simulator/turtlebot_gazebo/launch/gmapping.launch" &
sleep 5

# Start RViz to visualize navigation
xterm -e "roslaunch turtlebot_rviz_launchers view_navigation.launch" &
sleep 5

# Start keyboard control
xterm -e "rosrun wall_follower wall_follower_node" &
sleep 5

# Launch template
#xterm -e "" &
#sleep 5
