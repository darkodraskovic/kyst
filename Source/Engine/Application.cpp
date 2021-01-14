#include "Core.h"
#include "Application.h"
#include "Input.h"
#include "Scene/Scene.h"
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
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // glfw window creation
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
    glfwSetCursorPosCallback(window_, Input::MouseMoveCallback);
    glfwSetScrollCallback(window_, Input::MouseScrollCallback);
    
    // glad: load all OpenGL function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // configure global opengl state and init screen frambuffer
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);

    // configure input and mouse position
    input_ = new Input(window_);
    MouseData::lastPositionX = MouseData::positionX = windowSize_.x / 2;
    MouseData::lastPositionY = MouseData::positionY = windowSize_.y / 2;
    
    return 0;
};

void Application::Update()
{
    float currentFrame = glfwGetTime();
    deltaTime_ = currentFrame - lastFrame_;
    lastFrame_ = currentFrame;

    glfwPollEvents();
    input_->Process();

    for(auto it = viewports_.begin(); it != viewports_.end(); ++it) {
        (*it)->Update(deltaTime_);
    }
    
    glfwSwapBuffers(window_);
    // input_->Reset();
}

float Application::GetDeltaTime() { return deltaTime_; }

Input* Application::GetInput() { return input_; }

Viewport* Application::AddViewport(bool perspective, int width, int height) {
    if (!width) width = windowSize_.x;
    if (!height) height = windowSize_.y;
    auto viewport = Viewport::Create(this, perspective, width, height);
    AddViewport(shared_ptr<Viewport>(viewport));
    return viewport;
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

void FramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
