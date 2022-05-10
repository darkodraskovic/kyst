#include <stdlib.h>

#include "Engine/Application.h"
#include "Engine/Scene/Viewport.h"
#include "Engine/VecConsts.h"
#include "EntityFactory.h"
#include "ShapeFactory/ShapeUtils.h"

using namespace VecConsts;
using namespace ShapeFactory;

class App : public Application {
 public:
  virtual void Init() {
    Application::Init();

    // glEnable(GL_LINE_SMOOTH);
    glLineWidth(2.0f);

    auto viewport = AddViewport(true);
    viewport->scene_->clearColor_ = vec4(ShapeUtils::Hex2rgb("99B898"), 1.0);
    // viewport->AddEffect("Shaders/Effects/Noop.fs");
    // viewport->AddEffect("Shaders/Effects/Inversion.fs");
    // viewport->AddEffect("Shaders/Effects/Remove.fs");

    viewport->scene_->camera_->position_.z = 7.0f;
    viewport->scene_->camera_->position_.y = 5.0f;

    auto eFactory = new EntityFactory(viewport->scene_.get());

    eFactory->color1_ = ShapeUtils::Hex2rgb("E84A5F");
    eFactory->color2_ = ShapeUtils::Hex2rgb("FF847C");
    eFactory->color3_ = ShapeUtils::Hex2rgb("FECEAB");
    float limit = 0.05;
    eFactory->CreateLineGasket(4, vec2(-limit, limit), true, true);
    // eFactory->CreateTriGasket(4, vec2(-limit, limit), true, true);
    eFactory->CreateSnowflakeEmitter();

    viewport->scene_->camera_->LookAt(ZERO);
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
