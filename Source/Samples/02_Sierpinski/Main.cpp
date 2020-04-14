#include <algorithm>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/gtc/random.hpp>

#include "VecConsts.h"
#include "Application.h"
#include "EntityFactory.h"
#include "ShapeUitls.h"
#include "Mover.h"
#include "Particle.h"

using namespace VecConsts;

void createEntites();

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

    app.clearColor_ = vec4(ShapeUtils::Hex2rgb("99B898"), 1.0);
    
    // glEnable(GL_LINE_SMOOTH);
    glLineWidth(2.0f);
    

    // Application CONTENT
    // ---------------------------------------------------------------------------
    
    app.camera_.position_.z = 7.0f;
    app.camera_.position_.y = 1.0f;

    createEntites();
    
    // auto e1 = eFactory.CreateTriGasket(3, vec2(-limit, limit), true, true);


    EntityFactory* eFactory = new EntityFactory(&app);
    eFactory->color1_ = ShapeUtils::Hex2rgb("E84A5F");
    eFactory->color2_ = ShapeUtils::Hex2rgb("FF847C");
    eFactory->color3_ = ShapeUtils::Hex2rgb("FECEAB");
    float limit = 0.05;
    eFactory->CreateLineGasket(4, vec2(-limit, limit), true, true);

    // Application loop
    // ---------------------------------------------------------------------------
    int i = 0;
    while (!app.ShouldClose())
    {
        if (i%40 == 0) eFactory->CreateSnowflake(3);
        i++;
        app.Update();
    }

    delete eFactory;
    
    // Application termination
    // ---------------------------------------------------------------------------
    app.Terminate();
    return 0;
}

void createEntites()
{
    
}
