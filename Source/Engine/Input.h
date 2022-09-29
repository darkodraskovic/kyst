#pragma once

#include "Core.h"

namespace Kyst {

class Input {
 public:
  struct MouseData {
    float moveX_, moveY_;
    float scrollX_, scrollY_;
    float lastPositionX_, lastPositionY_;
    float positionX_, positionY_;
    bool scrolled_;

    MouseData()
        : moveX_(0),
          moveY_(0),
          scrollX_(0),
          scrollY_(0),
          lastPositionX_(0),
          lastPositionY_(0),
          positionX_(0),
          positionY_(0),
          scrolled_(false) {}
  };

 public:
  Input(GLFWwindow* window);

  void Process();
  void Reset();
  bool GetKey(unsigned int key) const;

  static void MouseMoveCallback(GLFWwindow* window, double posX, double posY);
  static void MouseScrollCallback(GLFWwindow* window, double scrollX, double scrollY);

  static MouseData mouseData_;

 private:
  GLFWwindow* window_;
};

}  // namespace Kyst
