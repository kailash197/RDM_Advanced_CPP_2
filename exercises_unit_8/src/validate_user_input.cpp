#include "../../modern_cpp_course/robot_commander/include/robot_commander/robot_commander.h"

#include <exception>
#include <iostream>
#include <ros/ros.h>

class WrongTurnException : public std::exception {
public:
  const char *what() const throw() {
    return "Wrong Turn. Enter turn velocity between -1 and 0.";
  }
};

int main(int argc, char **argv) {
  ros::init(argc, argv, "exercise_8_1");

  RobotCommander my_robot;

  int n = 0;

  while (n < 5) {

    float turn_velocity;
    std::cout << "Enter turn velocity: " << std::endl;

    // Check if input failed (not a number)
    if (std::cin.fail()) {
      std::cin.clear();           // Clear the error flags
      std::cin.ignore(256, '\n'); // Discard invalid input
      std::cout << "Invalid input. Please enter a valid decimal number."
                << std::endl;
      continue; // Skip this iteration and prompt for input again
    }

    try {

      std::cin >> turn_velocity;

      if (std::cin.fail()) {
        throw 'x';
      } else if (turn_velocity > -1.0 && turn_velocity < 0) {
        my_robot.turn(turn_velocity, 5);
      } else if (turn_velocity > 0 || turn_velocity < -1.0) {
        WrongTurnException e;
        throw e;
      } else
        throw 'x';
    } catch (WrongTurnException exc) {
      std::cout << exc.what() << std::endl;
    } catch (...) {
      std::cout << "Please enter a valid decimal number." << std::endl;
      std::cin.clear();
      std::cin.ignore(256, '\n');
    }

    n++;
  }

  return 0;
}