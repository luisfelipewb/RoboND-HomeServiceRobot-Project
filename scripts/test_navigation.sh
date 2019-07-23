#!/bin/bash

CATKIN_DIR=/home/workspace/catkin_ws
WORLD_DIR=$CATKIN_DIR/src/RoboND-HomeServiceRobot-Project/world/

# Load environment variables
source $CATKIN_DIR/devel/setup.bash;

# Launch the turtlebot in the customized world
xterm -e "roslaunch turtlebot_gazebo turtlebot_world.launch world_file:=$WORLD_DIR/lf.world " &
sleep 5

# Start amcl
xterm -e "roslaunch turtlebot_gazebo amcl_demo.launch map_file:=$WORLD_DIR/map_lf.yaml" &
sleep 5

# Start RViz to visualize navigation
xterm -e "roslaunch turtlebot_rviz_launchers view_navigation.launch" &
sleep 5

# Launch template
#xterm -e "" &
#sleep 5
