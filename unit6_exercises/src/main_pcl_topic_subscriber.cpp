#include "../include/unit6_exercises/topic_subscriber_function.h"
#include "ros/node_handle.h"
#include <ros/ros.h>
#include <sensor_msgs/PointCloud2.h>
#include <string>

int main(int argc, char **argv) {
  ros::init(argc, argv, "PCL_TOPIC_SUBSCRIBER_NODE");
  ros::NodeHandle nh;
  std::string subscriber_topic = "/camera/depth_registered/points";
  TopicSubscriberFuntion pcl_top_sub_node;
  pcl_top_sub_node.init<sensor_msgs::PointCloud2>(nh, subscriber_topic);
  ros::spin();
  return 0;
}