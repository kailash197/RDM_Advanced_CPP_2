#include "../include/unit6_exercises/topic_subscriber_class.h"
#include "sensor_msgs/Image.h"

int main(int argc, char **argv) {
  ros::init(argc, argv, "Topic_subscriber_node");
  ros::NodeHandle nh;
  TopicSubscriberNode<sensor_msgs::Image> topic_subscriber_node(
      nh, "/camera/rgb/image_raw");
  ros::spin();
  return 0;
}