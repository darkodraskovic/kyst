#include "Engine/Application.h"
#include "Engine/Scene/Viewport.h"
#include "Engine/VecConsts.h"
#include "MazeGen.h"
#include "ShapeFactory/ShapeUtils.h"

using namespace VecConsts;
using namespace ShapeFactory;

class App : public Application {
 public:
  virtual void Init() {
    Application::Init();

    // glEnable(GL_LINE_SMOOTH);
    glLineWidth(2.0f);

    // Viewport
    // ---------------------------------------------------------------------------

    auto viewport = AddViewport(true);

    viewport->scene_->clearColor_ = vec4(ShapeUtils::Hex2rgb("99B898"), 1.0);

    auto cam = viewport->scene_->camera_;
    cam->position_.z = 9.0f;
    cam->position_.y = 1.0f;

    viewport->AddEffect("Shaders/Effects/Noop.fs");
    viewport->AddEffect("Shaders/Effects/Inversion.fs");
    // viewport->AddEffect("Shaders/Effects/Remove.fs");

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
    maze.reset();

    cam->LookAt(ZERO + UP);
  }

  virtual void Update(float deltaTime) {
    viewports_[0]->scene_->camera_->Update(deltaTime_);
    Application::Update(deltaTime);
  }
};

int main() {
  App app;

  app.Init();

  app.Run();

  app.Terminate();

  return 0;
}
