#ifndef CAMERA_H
#define CAMERA_H

#include "../Input.h"
#include "../Object.h"
#include <glm/gtc/matrix_transform.hpp>

// An abstraction to stay away from window-system specific input methods
enum CameraMovement { CAM_FORWARD, CAM_BACKWARD, CAM_LEFT, CAM_RIGHT, CAM_UP, CAM_DOWN };

using namespace glm;

class Camera : public Object
{
public:
    Camera(Application* app);
    
    mat4 GetViewMatrix();
    virtual mat4 GetProjectionMatrix(int scrWidth, int scrHeight) = 0;

    virtual void LookAt(const vec3& center) = 0;    
    // TODO: remove this methods from Camera class
    virtual void Translate(CameraMovement direction, float deltaTime) = 0;
    virtual void ProcessInput(Input* input, float deltaTime) = 0;
    
    vec3 position_;
    
    vec3 front_;
    vec3 up_;
    vec3 right_;

    float zoom_;
    
    float movementSpeed_;
};
#endif
