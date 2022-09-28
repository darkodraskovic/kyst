#include "Camera.h"

#include <iostream>

mat4 Camera::GetViewMatrix(const vec3& position) { return glm::lookAt(position, position + front_, up_); }
