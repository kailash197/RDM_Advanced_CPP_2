#ifndef MAGIC_PRINTER_H
#define MAGIC_PRINTER_H

#include <ros/ros.h>

using namespace std;

class MagicPrinter {
public:
  MagicPrinter(ros::NodeHandle &ros_node);
  ~MagicPrinter();

  template <typename T> void PrintGeneric(T in_value) {
    ROS_INFO_STREAM("Generic Value=" << in_value);
  };

private:
  ros::NodeHandle *m_ros_node_object;
};

#endif