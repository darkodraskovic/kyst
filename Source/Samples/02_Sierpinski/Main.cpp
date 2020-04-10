#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Application.h"
#include "Sierpinski.h"

int main()
{
    // Application init
    // ---------------------------------------------------------------------------    
    Application app;
    if (app.Init() < 0)
    {
        std::cout << "Failed to create an OpenGL app" << std::endl;
        return -1;
    };

    // Application CONTENT
    // ---------------------------------------------------------------------------
    
    app.camera_.position_.z = 3.0f;

    auto gasket = std::make_shared<Sierpinski>();
    app.entities_.push_back(gasket);
    
    // Application loop
    // ---------------------------------------------------------------------------
    while (!app.ShouldClose())
    {

        float time = glfwGetTime();
        
        app.Update();
    }

    // Application termination
    // ---------------------------------------------------------------------------
    app.Terminate();
    return 0;
}
