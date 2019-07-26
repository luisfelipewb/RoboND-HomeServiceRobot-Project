#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include <std_msgs/String.h>

class Listener
{
public:
  int status;

  Listener(void) {
    status = 0;
  }

  void callback(const std_msgs::String::ConstPtr& msg);
};

void Listener::callback(const std_msgs::String::ConstPtr& msg)
{
  ROS_INFO("Listener received: [%s]", msg->data.c_str());
  status++;
}


int main( int argc, char** argv )
{
  ros::init(argc, argv, "add_markers");
  ros::NodeHandle n;
  ros::Rate r(0.5);
  ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);

  Listener listener;
  ros::Subscriber marker_sub = n.subscribe<std_msgs::String>("location",10, &Listener::callback, &listener);

  uint32_t shape = visualization_msgs::Marker::CUBE;

  visualization_msgs::Marker marker;
  marker.header.frame_id = "/map";
  marker.header.stamp = ros::Time::now();

  marker.ns = "add_markers";
  marker.id = 0;

  marker.type = shape;
  marker.type = shape;

  marker.pose.position.x = 4;
  marker.pose.position.y = 4;
  marker.pose.position.z = 0;
  marker.pose.orientation.x = 0.0;
  marker.pose.orientation.y = 0.0;
  marker.pose.orientation.z = 0.0;
  marker.pose.orientation.w = 1.0;

  marker.scale.x = 0.5;
  marker.scale.y = 0.5;
  marker.scale.z = 0.5;

  marker.color.r = 1.0f;
  marker.color.g = 0.0f;
  marker.color.b = 1.0f;
  marker.color.a = 0.9;

  marker.lifetime = ros::Duration();

  //pick up zone marker
  marker.action = visualization_msgs::Marker::ADD;
  marker_pub.publish(marker);

    while (marker_pub.getNumSubscribers() < 1)
    {
      if (!ros::ok())
      {
        return 0;
      }
      ROS_WARN_ONCE("Please create a subscriber to the marker");
      sleep(1);
    }


    //pick up zone marker
    marker.action = visualization_msgs::Marker::ADD;
    marker_pub.publish(marker);

  while (ros::ok())
  {
    ros::spinOnce();
    if( listener.status == 1 )
    {
      //hide marker after reaching
      marker.action = visualization_msgs::Marker::DELETE;
      marker_pub.publish(marker);
    }
    else if ( listener.status == 2 )
    {
      //drop zone marker
      marker.pose.position.x = 2;
      marker.pose.position.y = 0;
      marker.action = visualization_msgs::Marker::ADD;
      marker_pub.publish(marker);
    }

    r.sleep();
  }
}
