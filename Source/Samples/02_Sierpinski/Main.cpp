#include <algorithm>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/gtc/random.hpp>

#include "VecConsts.h"
#include "Application.h"
#include "EntityFactory.h"
#include "ShapeUtils.h"
#include "Mover.h"
#include "Particle.h"

using namespace VecConsts;

int main()
{
    // Application init
    // ---------------------------------------------------------------------------    

    Application& app = Application::Instance();
    
    if (app.Init() < 0)
    {
        std::cout << "Failed to create an OpenGL app" << std::endl;
        return -1;
    };

    app.clearColor_ = vec4(ShapeUtils::Hex2rgb("99B898"), 1.0);
    
    // glEnable(GL_LINE_SMOOTH);
    glLineWidth(2.0f);
    
    app.camera_.position_.z = 7.0f;
    app.camera_.position_.y = 1.0f;

    // Application CONTENT
    // ---------------------------------------------------------------------------
    
    auto eFactory = new EntityFactory();
    
    eFactory->color1_ = ShapeUtils::Hex2rgb("E84A5F");
    eFactory->color2_ = ShapeUtils::Hex2rgb("FF847C");
    eFactory->color3_ = ShapeUtils::Hex2rgb("FECEAB");
    float limit = 0.05;
    eFactory->CreateLineGasket(4, vec2(-limit, limit), true, true);
    eFactory->CreateSnowflakeEmitter();
    eFactory->CreateMaze(12, 8);

    app.AddEffect("../Shaders/Effects/Noop.fs");
    app.AddEffect("../Shaders/Effects/Inversion.fs");

    // Application loop
    // ---------------------------------------------------------------------------
    int i = 0;
    while (!app.ShouldClose())
    {
        app.Update();
    }

    // Application termination
    // ---------------------------------------------------------------------------
    app.Terminate();

    return 0;
}
