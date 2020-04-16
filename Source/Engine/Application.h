#ifndef APPLICATION_H
#define APPLICATION_H

#include <vector>
#include <memory>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "ResourceManager.h"
#include "Entity.h"
#include "Camera.h"

class Application
{
public:
    int Init();
    void ProcessInput(float deltaTime);
    void Render(float deltaTime);
    void Update();
    bool ShouldClose();
    void Terminate();
    static Application& Instance();

    ResourceManager resourceManager_;
    
    std::vector<std::shared_ptr<Entity>> entities_;
    GLFWwindow* window_;
    ivec2 windowPosition_ = vec2(0,0);
    uvec2 windowSize_ = vec2(1152,720);
    Camera camera_;

    float deltaTime_ = 0.0f;	// Time between current frame and last frame
    float lastFrame_ = 0.0f; // Time of last frame
    vec4 clearColor_ = vec4(0.2f, 0.3f, 0.3f, 1.0f);

private:
    Application();    
};

#endif
