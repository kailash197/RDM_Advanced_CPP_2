cmake_minimum_required(VERSION 3.0.2)
project(unit6_exercises)

## Compile as C++11, supported in ROS Kinetic and newer
add_compile_options(-std=c++17)

## Find catkin macros and libraries
find_package(catkin REQUIRED COMPONENTS
  roscpp
  sensor_msgs
)

catkin_package(
  INCLUDE_DIRS include
  LIBRARIES ${PROJECT_NAME}
  CATKIN_DEPENDS roscpp sensor_msgs
)


include_directories(
 include
  ${catkin_INCLUDE_DIRS}
)

## Declare a C++ library
add_library(magic_printer_library
  src/magic_printer.cpp
)
# add_library(magic_tsub_class_library
#   src/topic_subscriber_class.cpp
# )
add_library(magic_tsub_function_library
  src/topic_subscriber_function.cpp
)

## Create executables
add_executable(main_magic_printer_node src/main_magic_printer.cpp)
add_executable(main_topic_function_node src/main_topic_subscriber_function.cpp)
# add_executable(main_topic_class_node src/main_topic_subscriber_class.cpp)

## Specify libraries to link a library or executable target against
target_link_libraries(main_magic_printer_node magic_printer_library ${catkin_LIBRARIES})
target_link_libraries(main_topic_function_node magic_tsub_function_library ${catkin_LIBRARIES})
# target_link_libraries(main_topic_class_node magic_tsub_class_library ${catkin_LIBRARIES})