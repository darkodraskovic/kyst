#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "VecConsts.h"
#include "Application.h"
#include "EntityFactory.h"

using namespace VecConsts;

Application app;

int main()
{
    // Application init
    // ---------------------------------------------------------------------------    
    
    if (app.Init() < 0)
    {
        std::cout << "Failed to create an OpenGL app" << std::endl;
        return -1;
    };

    EntityFactory eFactory(&app);
    // Application CONTENT
    // ---------------------------------------------------------------------------
    
    app.camera_.position_.z = 4.0f;

    float limit = 0.05;

    eFactory.color1_ = YELLOW;
    auto e1 = eFactory.CreateLineGasket(4, vec2(-limit, limit), true, true);
    // auto e1 = eFactory.CreateTriGasket(3, vec2(-limit, limit), true, true);
    
    // Application loop
    // ---------------------------------------------------------------------------
    while (!app.ShouldClose())
    {

        float time = glfwGetTime();

        e1->Rotate(quarter_pi<float>() * app.deltaTime_, UP);
        app.Update();
    }

    // Application termination
    // ---------------------------------------------------------------------------
    app.Terminate();
    return 0;
}
