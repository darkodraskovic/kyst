#include "Engine/Application.h"
#include "Engine/Scene/Viewport.h"
#include "Engine/Scene/Scene.h"
#include "Engine/VecConsts.h"
#include "Engine/Scene/Scene.h"
#include "Engine/Scene/Entity.h"

#include "MazeGen.h"
#include "ShapeFactory/ShapeUtils.h"

using namespace Kyst;
using namespace Kyst::VecConsts;
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

    viewport->GetScene()->clearColor_ = vec4(ShapeUtils::Hex2rgb("99B898"), 1.0);

    auto* camComponent = viewport->GetScene()->cameraComponent_;
    auto* camEntity = camComponent->GetEntity();

    camEntity->position_.z = 9.0f;
    camEntity->position_.y = 1.0f;

    viewport->AddEffect("Shaders/Effects/Noop.fs");
    // viewport->AddEffect("Shaders/Effects/Inversion.fs");
    // viewport->AddEffect("Shaders/Effects/Remove.fs");

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

    viewport->GetScene()->cameraComponent_->GetCamera()->LookAt(ZERO + UP, camEntity->position_, camEntity->rotation_);
  }

};

int main() {
  App app;

  app.Init();

  app.Run();

  app.Terminate();

  return 0;
}
