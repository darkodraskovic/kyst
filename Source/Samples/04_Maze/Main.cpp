#include "VecConsts.h"
#include "Application.h"
#include "MazeGen.h"
#include "ShapeUtils.h"

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
    
    // glEnable(GL_LINE_SMOOTH);
    glLineWidth(2.0f);

    // Viewport
    // ---------------------------------------------------------------------------
    
    auto viewport = std::make_shared<Viewport>();
    app.viewports_.push_back(viewport);

    viewport->scene_->clearColor_ = vec4(ShapeUtils::Hex2rgb("99B898"), 1.0);
    
    app.camera_ = viewport->scene_->camera_;
    app.camera_->position_.z = 9.0f;
    app.camera_->position_.y = 1.0f;

    viewport->AddEffect("../Shaders/Effects/Noop.fs");
    viewport->AddEffect("../Shaders/Effects/Inversion.fs");
    // viewport->AddEffect("../Shaders/Effects/Remove.fs");
    
    // Application CONTENT
    // ---------------------------------------------------------------------------
    

    auto color1_ = ShapeUtils::Hex2rgb("E84A5F");
    auto color2_ = ShapeUtils::Hex2rgb("FF847C");
    auto color3_ = ShapeUtils::Hex2rgb("FECEAB");
    
    auto mazeGen = new MazeGen(viewport->scene_.get());
    mazeGen->CreateMaze(12, 8, color1_);
    auto maze = mazeGen->CreateMaze(6, 18, color2_);
    maze->position_.x = -2;
    maze = mazeGen->CreateMaze(20, 6, color3_);
    maze->position_.y = -1.75;
    maze->position_.x = -2;

    // Reset POINTERS
    // ---------------------------------------------------------------------------
    
    maze.reset();    
    viewport.reset();

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
