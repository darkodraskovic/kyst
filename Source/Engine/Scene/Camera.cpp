#include "Camera.h"

#include <iostream>

namespace Kyst {

mat4 Camera::GetViewMatrix(const vec3& position) { return glm::lookAt(position, position + front_, up_); }

}  // namespace Kyst
