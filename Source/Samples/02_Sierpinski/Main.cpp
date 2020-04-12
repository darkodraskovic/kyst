#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "VecConsts.h"
#include "Application.h"
#include "EntityFactory.h"
#include "ShapeUitls.h"

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

    // app.clearColor_ = vec4(ShapeUtils::Hex2rgb("2A363B"), 1.0);
    app.clearColor_ = vec4(ShapeUtils::Hex2rgb("99B898"), 1.0);
    // glEnable(GL_LINE_SMOOTH);
    glLineWidth(2.0f);
    
    EntityFactory eFactory(&app);
    // Application CONTENT
    // ---------------------------------------------------------------------------
    
    app.camera_.position_.z = 4.0f;

    float limit = 0.05;

    eFactory.color1_ = ShapeUtils::Hex2rgb("E84A5F");
    eFactory.color2_ = ShapeUtils::Hex2rgb("FF847C");
    eFactory.color3_ = ShapeUtils::Hex2rgb("FECEAB");
    auto e1 = eFactory.CreateLineGasket(4, vec2(-limit, limit), true, true);
    eFactory.SetColor(eFactory.color3_);
    auto e2 = eFactory.CreateSnowflake(3);
    e2->SetScale(0.1f);
    e2->Translate(ONE);
    // auto e1 = eFactory.CreateTriGasket(3, vec2(-limit, limit), true, true);
    
    // Application loop
    // ---------------------------------------------------------------------------
    while (!app.ShouldClose())
    {

        float time = glfwGetTime();

        e1->Rotate(quarter_pi<float>() * app.deltaTime_ / 2, UP);
        app.Update();
    }

    // Application termination
    // ---------------------------------------------------------------------------
    app.Terminate();
    return 0;
}
