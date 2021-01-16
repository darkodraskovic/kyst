#include "Input.h"
#include <iostream>

namespace MouseData
{
    float moveX{0}, moveY{0};
    float scrollX{0}, scrollY{0};
    float lastPositionX{0}, lastPositionY{0};
    float positionX{0}, positionY{0};
    bool scrolled{false};
}

Input::Input(GLFWwindow *window) : window_(window) {}

void Input::Process()
{
    using namespace MouseData;
    moveX = positionX - lastPositionX;
    moveY = positionY - lastPositionY;
    lastPositionX = positionX;
    lastPositionY = positionY;
};

void Input::Reset() { MouseData::scrolled = false; };

bool Input::GetKey(unsigned int key)
{
    return glfwGetKey(window_, key) == GLFW_PRESS;
}

void Input::MouseMoveCallback(GLFWwindow* window, double posX, double posY)
{
    MouseData::positionX = posX;
    MouseData::positionY = posY;
}

void Input::MouseScrollCallback(GLFWwindow* window, double scrX, double scrY)
{
    using namespace MouseData;
    scrollX = scrX;
    scrollY = scrY;
    scrolled = true;
}
