#include "../include/unit6_exercises/topic_subscriber_function.h"
#include "ros/node_handle.h"
#include "sensor_msgs/Image.h"

int main(int argc, char **argv) {
  ros::init(argc, argv, "Topic_subscriber_node");
  ros::NodeHandle nh;
  TopicSubscriberFuntion topic_subscriber_node;
  topic_subscriber_node.init<sensor_msgs::Image>(nh, "/camera/rgb/image_raw");
  ros::spin();

  return 0;
}