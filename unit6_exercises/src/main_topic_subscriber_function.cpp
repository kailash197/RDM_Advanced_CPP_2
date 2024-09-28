#include "../include/unit6_exercises/topic_subscriber_function.h"
#include "ros/node_handle.h"

int main(int argc, char **argv) {
  ros::init(argc, argv, "Topic_subscriber_node");
  ros::NodeHandle nh;
  TopicSubscriberFuntion node(nh, "/camera/rgb/image_raw");
  ros::spin();

  return 0;
}