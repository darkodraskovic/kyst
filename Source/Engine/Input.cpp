#include "Input.h"

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
    if(glfwGetKey(window_, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window_, true);
    }

    ProcessMouseMovement();
};

void Input::Reset() { MouseData::scrolled = false; };

void Input::ProcessMouseMovement()
{
    using namespace MouseData;
    moveX = positionX - lastPositionX;
    moveY = positionY - lastPositionY;
    lastPositionX = positionX;
    lastPositionY = positionY;
}

bool Input::GetKey(unsigned int key)
{
    return glfwGetKey(window_, key) == GLFW_PRESS;
}

void Input::MouseMoveCallback(GLFWwindow* window, double posX, double posY)
{
    MouseData::positionX = posX;
    MouseData::positionY = posY;
}

void Input::MouseScrollCallback(GLFWwindow* window, double scrollX, double scrollY)
{
    using namespace MouseData;
    scrollX = scrollX;
    scrollY = scrollY;
    scrolled = true;
}
