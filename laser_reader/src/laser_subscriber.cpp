#include "ros/forwards.h"
#include "ros/node_handle.h"
#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>
#include <utility>

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
  float printClosestObstacleDistance() const;
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
  printClosestObstacleDistance();
}

float LaserSubscriberNode::printClosestObstacleDistance() const {
  if (!laser_scan) {
    ROS_WARN("No laser scan data available.");
    return std::numeric_limits<float>::infinity();
  }

  float min_distance = std::numeric_limits<float>::infinity();
  int min_index = 0;

  for (int i = 0; i < 720; i++) {
    if (std::isfinite(laser_scan->ranges[i]) &&
        laser_scan->ranges[i] < min_distance) {
      min_distance = laser_scan->ranges[i];
      min_index = i;
    }
  }

  float closest_ang =
      laser_scan->angle_min + min_index * laser_scan->angle_increment;
  ROS_INFO("Closest obstacle distance: %f at angle: %f", min_distance,
           closest_ang);

  return closest_ang;
}

int main(int argc, char **argv) {
  ros::init(argc, argv, "laser_subscriber_node");
  LaserSubscriberNode laser_node;
  ros::spin();
  return 0;
}