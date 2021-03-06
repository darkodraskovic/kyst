#ifndef APPLICATION_H
#define APPLICATION_H

#include <memory>
#include <string>
#include <vector>

#include <glm/glm.hpp>

#include "ResourceManager.h"
#include "Input.h"

using namespace glm;

void FramebufferSizeCallback(GLFWwindow* window, int width, int height);

class Viewport;

class Application
{
public:
    Application();
        
    virtual int Init();
    virtual void ProcessInput();
    virtual void Update(float deltaTime);    
    void Run();
    bool ShouldClose();
    void Close();
    void Terminate();
    
    float GetDeltaTime();
    Input* GetInput();
    
    void SetWindowSize(const uvec2& size);
    const uvec2& GetWindowSize();
    void SetWindowPosition(const ivec2& size);
    const ivec2& GetWindowPosition();

    ResourceManager resourceManager_;
    GLFWwindow* window_;

    Viewport* AddViewport(bool perspective = true, int width = 0, int height = 0);
    void AddViewport(std::shared_ptr<Viewport> viewport);

protected:
    std::vector<std::shared_ptr<Viewport>> viewports_;
    Input* input_;
    float deltaTime_ = 0.0f;

private:
    friend void FramebufferSizeCallback(GLFWwindow* window, int width, int height);
    friend void MouseCallback(GLFWwindow* window, double posX, double posY);
    friend void ScrollCallback(GLFWwindow* window, double scrollX, double scrollY);

    float lastFrame_ = 0.0f;

    uvec2 windowSize_{1152,720};
    ivec2 windowPosition_{0,0};
};

#endif
