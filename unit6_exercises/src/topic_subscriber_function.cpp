#include "../include/unit6_exercises/topic_subscriber_function.h"
#include "sensor_msgs/Image.h"

using namespace std;

TopicSubscriberFuntion::TopicSubscriberFuntion(ros::NodeHandle &node_handle,
                                               const string topic) {
  nh_ = &node_handle;
  subscriber_topic = topic;
  if (ros::console::set_logger_level(ROSCONSOLE_DEFAULT_NAME,
                                     ros::console::levels::Info)) {
    ros::console::notifyLoggerLevelsChanged();
  }
  subscriber_ = nh_->subscribe(
      subscriber_topic, 100, &TopicSubscriberFuntion::subscriberCallback, this);
  ROS_INFO("Main Topic Subscriber Function Node initialized.");
}

void TopicSubscriberFuntion::subscriberCallback(
    const sensor_msgs::ImageConstPtr &msg) {
  ROS_INFO_STREAM(
      "Call Back Topic Image Data[0]=" << static_cast<int>(msg->data[0]));
}

TopicSubscriberFuntion::~TopicSubscriberFuntion() {
  ROS_INFO("TopicSubscriberFuntion Destruction called.");
}

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