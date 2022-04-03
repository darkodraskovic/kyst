#include "Input.h"

#include <iostream>

Input::MouseData Input::mouseData_;

Input::Input(GLFWwindow* window) : window_(window) {}

void Input::Process() {
  mouseData_.moveX_ = mouseData_.positionX_ - mouseData_.lastPositionX_;
  mouseData_.moveY_ = mouseData_.positionY_ - mouseData_.lastPositionY_;
  mouseData_.lastPositionX_ = mouseData_.positionX_;
  mouseData_.lastPositionY_ = mouseData_.positionY_;
};

void Input::Reset() { mouseData_.scrolled_ = false; };

bool Input::GetKey(unsigned int key) {
  return glfwGetKey(window_, key) == GLFW_PRESS;
}

void Input::MouseMoveCallback(GLFWwindow* window, double positionX,
                              double positionY) {
  mouseData_.positionX_ = positionX;
  mouseData_.positionY_ = positionY;
}

void Input::MouseScrollCallback(GLFWwindow* window, double scrollX,
                                double scrollY) {
  mouseData_.scrollX_ = scrollX;
  mouseData_.scrollY_ = scrollY;
  mouseData_.scrolled_ = true;
}
