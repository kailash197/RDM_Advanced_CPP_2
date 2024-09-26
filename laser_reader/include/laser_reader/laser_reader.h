#ifndef LASER_TURTLE_H
#define LASER_TURTLE_H
#include "sensor_msgs/LaserScan.h"
#include <ros/ros.h>

class TurtleClass {
private:
  ros::NodeHandle n;
  ros::Subscriber laser_sub;
  void laser_callback(const sensor_msgs::LaserScan::ConstPtr &laser_msg);

  float *last_ten_scans[10]; // create 10 pointers in stack
  //   float **last_ten_scans; //= new float *[10]; create in heap

public:
  TurtleClass();
  ~TurtleClass();
};

#endif