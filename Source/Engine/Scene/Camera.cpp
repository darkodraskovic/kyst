#include <iostream>

#include "Camera.h"

Camera::Camera(Application* app) : Object(app)
{
    position_ = vec3(0.0f, 0.0f, 0.0f);
    
    
    up_ = vec3(0.0f, 1.0f, 0.0f);
    front_ = vec3(0.0f, 0.0f, -1.0f);
    
    movementSpeed_ = 5.0f;
    zoom_ = 1.0f;
}

mat4 Camera::GetViewMatrix()
{
    return glm::lookAt(position_, position_ + front_, up_);
}
