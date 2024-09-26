#include "../include/laser_reader/laser_reader.h"
// #include "robot_management/laser_turtle.h"
#include "sensor_msgs/LaserScan.h"
#include <ros/ros.h>

// TurtleClass constructor make changes in the constructor as per definition
TurtleClass::TurtleClass() {
  n = ros::NodeHandle("~");
  laser_sub =
      n.subscribe("/kobuki/laser/scan", 10, &TurtleClass::laser_callback, this);
  ROS_INFO("Initializing node.");
  usleep(2000000);

  //   last_ten_scans = new float *[10];
  for (int i = 0; i < 10; i++) {
    last_ten_scans[i] = new float[720];
  }
}

TurtleClass::~TurtleClass() {
  for (int i = 0; i < 10; i++) {
    delete[] last_ten_scans[i];
  }
}

void TurtleClass::laser_callback(const sensor_msgs::LaserScan::ConstPtr &msg) {
  float angle_min = msg->angle_min;
  float angle_max = msg->angle_max;
  float angle_increment = msg->angle_increment;
  int front_index = (angle_max + std::fabs(angle_min)) / (2 * angle_increment);
  front_index = 360;

  //   for (float val : msg->ranges) {
  //     // *(last_laser_ranges++) = val; // ptr goes out of range in second
  //     cycle
  //   }

  // shift pointers to make first pointer free for last_laser_ranges
  for (int i = 9; i > 0; i--) {
    for (int j = 0; j < 720; j++) {
      last_ten_scans[i][j] = last_ten_scans[i - 1][j];
    }
  }

  for (int j = 0; j < 720; j++) {
    last_ten_scans[0][j] = msg->ranges[j];
  }
  ROS_INFO("Distance at front of robot for last 10 scans");
  for (int i = 0; i < 10; i++) {
    ROS_INFO("Scan %d, Front distance: %lf", i,
             *(last_ten_scans[i] + front_index));
  }
}

int main(int argc, char **argv) {
  ros::init(argc, argv, "rosbot_class_node");

  TurtleClass tc = TurtleClass();
  ros::spin();

  return 0;
}