#ifndef MAIN_SUBSCRIBER_FUNCTION_H
#define MAIN_SUBSCRIBER_FUNCTION_H

#include "ros/node_handle.h"
#include <ros/ros.h>
#include <sensor_msgs/Image.h>
#include <string>

class TopicSubscriberFuntion {
  ros::NodeHandle *nh_;
  ros::Subscriber subscriber_;
  std::string subscriber_topic;

public:
  TopicSubscriberFuntion() { ROS_INFO("TopicSubscriberFuntionNode created."); }
  ~TopicSubscriberFuntion() {
    delete nh_;
    ROS_INFO("TopicSubscriberFuntionNode destroyed.");
  };

  template <typename MessageType>
  void init(ros::NodeHandle &node_handle, std::string topic) {
    nh_ = &node_handle;
    subscriber_topic = topic;
    if (ros::console::set_logger_level(ROSCONSOLE_DEFAULT_NAME,
                                       ros::console::levels::Info)) {
      ros::console::notifyLoggerLevelsChanged();
    }
    subscriber_ = nh_->subscribe(
        subscriber_topic, 100,
        &TopicSubscriberFuntion::subscriberCallback<MessageType>, this);
    ROS_INFO("Main Topic Subscriber Function Node initialized.");
  }
  template <typename MessageType>
  void subscriberCallback(const typename MessageType::ConstPtr &msg) {
    ROS_INFO_STREAM(
        "Call Back Topic Image Data[0]=" << static_cast<int>(msg->data[0]));
  }
};

#endif
/*user:~/catkin_ws/src$ rosmsg show sensor_msgs/Image
std_msgs/Header header
  uint32 seq
  time stamp
  string frame_id
uint32 height
uint32 width
string encoding
uint8 is_bigendian
uint32 step
uint8[] data
// the uint8 is an alias of unsigned char, therefore needs casting to int
*/