#include <iostream>
#include <algorithm>
#include <memory>
#include <functional>

#include "Application.h"
#include "Camera.h"
#include "Entity.h"
#include "Framebuffer.h"
#include "Input.h"
#include "Viewport.h"

using namespace glm;

bool Application::processMouseMovement_ = false;
bool Application::processMouseScroll_ = false;

Application::Application() {};

Application& Application::Instance()
{
    static Application* instance = new Application();
    return *instance;
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
    using namespace std::placeholders;
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
    input_->lastMouseX_ = (float)windowSize_.x / 2;
    input_->lastMouseY_ = (float)windowSize_.y / 2;

    return 0;
};

void Application::ProcessInput(float deltaTime)
{
    if(glfwGetKey(window_, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window_, true);
    }
    
    if (input_->GetKey(GLFW_KEY_W)) camera_->ProcessKeyboard(CAM_FORWARD, deltaTime);
    if (input_->GetKey(GLFW_KEY_S)) camera_->ProcessKeyboard(CAM_BACKWARD, deltaTime);
    if (input_->GetKey(GLFW_KEY_A)) camera_->ProcessKeyboard(CAM_LEFT, deltaTime);
    if (input_->GetKey(GLFW_KEY_D)) camera_->ProcessKeyboard(CAM_RIGHT, deltaTime);
    if (input_->GetKey(GLFW_KEY_E)) camera_->ProcessKeyboard(CAM_UP, deltaTime);
    if (input_->GetKey(GLFW_KEY_Q)) camera_->ProcessKeyboard(CAM_DOWN, deltaTime);

    if (Application::processMouseMovement_) {
        input_->ProcessMouseMovement();
        camera_->ProcessMouseMovement(input_->mouseOffsetX_, input_->mouseOffsetY_);
        Application::processMouseMovement_ = false;
    }

    if (Application::processMouseScroll_) {
        camera_->ProcessMouseScroll(MouseData::scrollY);
        Application::processMouseScroll_ = false;
    }
}

void Application::Update()
{
    float currentFrame = glfwGetTime();
    deltaTime_ = currentFrame - lastFrame_;
    lastFrame_ = currentFrame;

    ProcessInput(deltaTime_);

    for(auto it = viewports_.begin(); it != viewports_.end(); ++it) {
        (*it)->Update(deltaTime_);
    }
    
    // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
    // -------------------------------------------------------------------------------
    glfwSwapBuffers(window_);
    glfwPollEvents();
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
    Application::processMouseMovement_ = true;
};

void ScrollCallback(GLFWwindow* window, double offsetX, double offsetY)
{
    MouseData::scrollX = offsetX;
    MouseData::scrollY = offsetY;
    Application::processMouseScroll_ = true;
}
