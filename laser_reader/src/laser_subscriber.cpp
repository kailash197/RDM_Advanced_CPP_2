#include "ros/forwards.h"
#include "ros/node_handle.h"
#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>

class LaserSubscriberNode {
private:
  const sensor_msgs::LaserScan *laser_scan = nullptr;

protected:
  ros::NodeHandle nh_;
  ros::Subscriber laser_subscriber;
  void laser_callback(const sensor_msgs::LaserScanConstPtr &msg);
  void init_laser_subscriber();

public:
  LaserSubscriberNode();
  ~LaserSubscriberNode(){};
};

LaserSubscriberNode::LaserSubscriberNode() {
  ros::NodeHandle nh_;
  init_laser_subscriber();
  ROS_INFO("Laser Subscriber Node Initiated.");
}

void LaserSubscriberNode::init_laser_subscriber() {
  laser_subscriber = nh_.subscribe("/kobuki/laser/scan", 100,
                                   &LaserSubscriberNode::laser_callback, this);
  ROS_INFO("Laser Subscriber Initiated.");
}

void LaserSubscriberNode::laser_callback(
    const sensor_msgs::LaserScanConstPtr &msg) {
  laser_scan = msg.get();
  int front_index = 360;

  float distance = laser_scan->ranges[front_index];
  ROS_INFO("Distance at front: %f", distance);
}

int main(int argc, char **argv) {
  ros::init(argc, argv, "laser_subscriber_node");
  LaserSubscriberNode laser_node;
  ros::spin();
  return 0;
}