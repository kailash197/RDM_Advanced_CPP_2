cmake_minimum_required(VERSION 3.0.2)
project(unit6_exercises)
set(CMAKE_CXX_COMPILER "/usr/bin/clang++")
set(CMAKE_C_COMPILER "/usr/bin/clang")

add_compile_options(-std=c++17)
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
add_library(magic_tsub_class_library
  src/topic_subscriber_class.cpp
)

add_library(magic_tsub_function_library
  src/topic_subscriber_function.cpp
)

## Create executables
add_executable(main_magic_printer_node src/main_magic_printer.cpp)
add_executable(main_topic_function_node src/main_topic_subscriber_function.cpp)
add_executable(main_topic_class_node src/main_topic_subscriber_class.cpp)
add_executable(main_pcl_topic_subscriber_node src/main_pcl_topic_subscriber.cpp)


## Specify libraries to link a library or executable target against
target_link_libraries(main_magic_printer_node magic_printer_library ${catkin_LIBRARIES})
target_link_libraries(main_topic_function_node magic_tsub_function_library ${catkin_LIBRARIES})
target_link_libraries(main_topic_class_node magic_tsub_class_library ${catkin_LIBRARIES})
target_link_libraries(main_pcl_topic_subscriber_node magic_tsub_function_library ${catkin_LIBRARIES})


add_executable(basic_example_u6_specialization_node src/basic_example_u6_specialization.cpp)
target_link_libraries(basic_example_u6_specialization_node
	${catkin_LIBRARIES}
)

add_executable(basic_example_u6_specialization_functions_node src/basic_example_u6_specialization_functions.cpp)
target_link_libraries(basic_example_u6_specialization_functions_node
	${catkin_LIBRARIES}
)

add_library(specialised_example_library src/specialised_example.cpp)
add_executable(main_specialised_example_node src/main_specialised_example.cpp)
target_link_libraries(main_specialised_example_node specialised_example_library ${catkin_LIBRARIES})