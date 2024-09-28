#ifndef MAIN_SUBSCRIBER_FUNCTION_H
#define MAIN_SUBSCRIBER_FUNCTION_H

#include <ros/ros.h>
#include <sensor_msgs/Image.h>
#include <string>

class TopicSubscriberFuntion {
  ros::NodeHandle *nh_;
  ros::Subscriber subscriber_;
  std::string subscriber_topic;

public:
  TopicSubscriberFuntion(ros::NodeHandle &node_handle, const std::string topic);
  ~TopicSubscriberFuntion();

  void subscriberCallback(const sensor_msgs::ImageConstPtr &msg);
};

#endif