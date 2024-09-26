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
  // an array of 720 pointers to float
  last_laser_ranges = new float[720];
}

/* CREATE THE CLASS DESTRUCTOR HERE */
TurtleClass::~TurtleClass() { delete last_laser_ranges; }

void TurtleClass::laser_callback(const sensor_msgs::LaserScan::ConstPtr &msg) {
  float angle_min = msg->angle_min;
  float angle_max = msg->angle_max;
  float angle_increment = msg->angle_increment;
  int front_index = (angle_max + std::fabs(angle_min)) / (2 * angle_increment);

  //   for (float val : msg->ranges) {
  //     // *(last_laser_ranges++) = val; // ptr goes out of range in second
  //     cycle
  //   }

  for (int i = 0; i < msg->ranges.size(); i++) {
    last_laser_ranges[i] = msg->ranges[i];
  }
  ROS_INFO("Distance at front of robot: %lf",
           *(last_laser_ranges + front_index));
  /* WRITE HERE YOUR CODE */
}

int main(int argc, char **argv) {
  ros::init(argc, argv, "rosbot_class_node");

  TurtleClass tc = TurtleClass();
  ros::spin();

  return 0;
}