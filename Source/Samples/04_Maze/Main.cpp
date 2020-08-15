#include "VecConsts.h"
#include "Application.h"
#include "MazeGen.h"
#include "ShapeUtils.h"
#include "Viewport.h"

using namespace VecConsts;

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
    
    auto cam = viewport->GetScene()->camera_;
    cam->position_.z = 9.0f;
    cam->position_.y = 1.0f;

    viewport->AddEffect("../Shaders/Effects/Noop.fs");
    viewport->AddEffect("../Shaders/Effects/Inversion.fs");
    // viewport->AddEffect("../Shaders/Effects/Remove.fs");
    
    // Application CONTENT
    // ---------------------------------------------------------------------------
    

    auto color1_ = ShapeUtils::Hex2rgb("E84A5F");
    auto color2_ = ShapeUtils::Hex2rgb("FF847C");
    auto color3_ = ShapeUtils::Hex2rgb("FECEAB");
    
    auto mazeGen = new MazeGen(viewport->GetScene());
    mazeGen->CreateMaze(12, 8, color1_);
    auto maze = mazeGen->CreateMaze(6, 18, color2_);
    maze->position_.x = -2;
    maze = mazeGen->CreateMaze(20, 6, color3_);
    maze->position_.y = -1.75;
    maze->position_.x = -2;
    maze.reset();    

    cam->LookAt(ZERO + UP);
    // Application loop
    // ---------------------------------------------------------------------------
    int i = 0;
    while (!app.ShouldClose())
    {
        cam->ProcessInput(app.GetInput(), app.GetDeltaTime());
        app.Update();
    }

    // Application termination
    // ---------------------------------------------------------------------------
    app.Terminate();

    return 0;
}
