#include "Engine/Application.h"
#include "Engine/VecConsts.h"
#include "Engine/Scene/Viewport.h"
#include "ShapeFactory/ShapeUtils.h"
#include "EntityFactory.h"

using namespace VecConsts;
using namespace ShapeFactory;

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

    // glEnable(GL_LINE_SMOOTH);
    glLineWidth(2.0f);
    
    // Viewport
    // ---------------------------------------------------------------------------
    
    auto viewport = app.AddViewport();
    
    viewport->GetScene()->clearColor_ = vec4(ShapeUtils::Hex2rgb("99B898"), 1.0);
    // viewport->AddEffect("Shaders/Effects/Noop.fs");
    // viewport->AddEffect("Shaders/Effects/Inversion.fs");
    // viewport->AddEffect("Shaders/Effects/Remove.fs");

    viewport->GetScene()->camera_->position_.z = 7.0f;
    viewport->GetScene()->camera_->position_.y = 5.0f;
    
    // Application CONTENT
    // ---------------------------------------------------------------------------

    
    auto eFactory = new EntityFactory(viewport->GetScene());
    
    eFactory->color1_ = ShapeUtils::Hex2rgb("E84A5F");
    eFactory->color2_ = ShapeUtils::Hex2rgb("FF847C");
    eFactory->color3_ = ShapeUtils::Hex2rgb("FECEAB");
    float limit = 0.05;
    eFactory->CreateLineGasket(4, vec2(-limit, limit), true, true);
    // eFactory->CreateTriGasket(4, vec2(-limit, limit), true, true);
    eFactory->CreateSnowflakeEmitter();

    viewport->GetScene()->camera_->LookAt(ZERO);  
    // Application loop
    // ---------------------------------------------------------------------------
    int i = 0;
    while (!app.ShouldClose())
    {
        viewport->GetScene()->camera_->ProcessInput(app.GetInput(), app.GetDeltaTime());
        app.Update();
    }

    // Application termination
    // ---------------------------------------------------------------------------
    app.Terminate();

    return 0;
}
