#ifndef INPUT_H
#define INPUT_H

#include "Core.h"

namespace MouseData
{
    extern float moveX, moveY;
    extern float scrollX, scrollY;
    extern float lastPositionX, lastPositionY;
    extern float positionX, positionY;
    extern bool scrolled;
}

class Input
{
public:
    Input(GLFWwindow* window);

    void Process();
    void Reset();
    bool GetKey(unsigned int key);

    static void MouseMoveCallback(GLFWwindow* window, double posX, double posY);
    static void MouseScrollCallback(GLFWwindow* window, double scrollX, double scrollY);

private:
    GLFWwindow* window_;
};

#endif /* INPUT_H */
