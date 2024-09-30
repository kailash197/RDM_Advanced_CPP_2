#pragma once

#include "ros/node_handle.h"
#include <sensor_msgs/Image.h>

using namespace std;
template <typename MessageType> class TopicSubscriberNode {
  ros::NodeHandle *nh_;
  ros::Subscriber subscriber_;
  std::string subscriber_topic;

public:
  TopicSubscriberNode(ros::NodeHandle &ros_node, const string subs_topic) {
    subscriber_topic = subs_topic;
    nh_ = &ros_node;
    if (ros::console::set_logger_level(ROSCONSOLE_DEFAULT_NAME,
                                       ros::console::levels::Info)) {
      ros::console::notifyLoggerLevelsChanged();
    }
    subscriber_ = nh_->subscribe(
        subscriber_topic, 100,
        &TopicSubscriberNode<MessageType>::subscriberCallback, this);
    ROS_INFO("TopicSubscriberNode constructor is called");
  }

  ~TopicSubscriberNode() {
    ROS_INFO("TopicSubscriberNode Destructor is called");
  }

  //   template <typename MessageType>
  void subscriberCallback(const typename MessageType::ConstPtr &msg) {
    ROS_INFO_STREAM(
        "Call Back Topic Image Data[0]=" << static_cast<int>(msg->data[0]));
  }
};