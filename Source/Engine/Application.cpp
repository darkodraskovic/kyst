#include <iostream>

#include "Core.h"
#include "Application.h"
#include "Input.h"
#include "Scene/Viewport.h"

using namespace glm;

Application::Application() {};

void Application::SetWindowSize(const uvec2& size)
{
    windowSize_ = size;
}
    
const uvec2& Application::GetWindowSize()
{
    return windowSize_;
}

void Application::SetWindowPosition(const ivec2& position)
{
    windowPosition_ = position;
}
    
const ivec2& Application::GetWindowPosition()
{
    return windowPosition_;
}


int Application::Init()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // glfw window creation
    // --------------------
    window_ = glfwCreateWindow(windowSize_.x, windowSize_.y, "Camera", NULL, NULL);
    if (window_ == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwSetWindowPos(window_, windowPosition_.x, windowPosition_.y);    
    glfwMakeContextCurrent(window_);
    glfwSetFramebufferSizeCallback(window_, FramebufferSizeCallback);
    
    glfwSetInputMode(window_, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window_, MouseCallback);
    glfwSetScrollCallback(window_, ScrollCallback);
    
    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // configure global opengl state and init screen frambuffer
    // -----------------------------
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);

    // configure input and mouse position
    // -----------------------------
    input_ = new Input(window_);
    input_->lastMouseX_ = MouseData::positionX = windowSize_.x / 2;
    input_->lastMouseY_ = MouseData::positionY = windowSize_.y / 2;
    
    return 0;
};

void Application::ProcessInput(float deltaTime)
{
    if(glfwGetKey(window_, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window_, true);
    }

    input_->ProcessMouseMovement();
}

void Application::Update()
{
    float currentFrame = glfwGetTime();
    deltaTime_ = currentFrame - lastFrame_;
    lastFrame_ = currentFrame;

    glfwPollEvents();
    ProcessInput(deltaTime_);

    for(auto it = viewports_.begin(); it != viewports_.end(); ++it) {
        (*it)->Update(deltaTime_);
    }
    glfwSwapBuffers(window_);
}

float Application::GetDeltaTime() { return deltaTime_; }

Input* Application::GetInput() { return input_; }

Viewport* Application::AddViewport()
{
    auto viewport = std::make_shared<Viewport>(this);
    viewport->Init(GetWindowSize());
    AddViewport(viewport);
    return viewport.get();
}

void Application::AddViewport(std::shared_ptr<Viewport> viewport)
{
    viewports_.push_back(viewport);
    viewport->application_ = this;
}

bool Application::ShouldClose()
{
    return glfwWindowShouldClose(window_);    
};

void Application::Terminate()
{
    viewports_.clear();
    delete input_;
    glfwTerminate();
};

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void FramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void MouseCallback(GLFWwindow* window, double posX, double posY)
{
    MouseData::positionX = posX;
    MouseData::positionY = posY;
}

void ScrollCallback(GLFWwindow* window, double scrollX, double scrollY)
{
    MouseData::scrollX = scrollX;
    MouseData::scrollY = scrollY;
}
