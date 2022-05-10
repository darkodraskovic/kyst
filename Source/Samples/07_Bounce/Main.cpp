#include <cassert>
#include <glm/ext/scalar_constants.hpp>
#include <glm/fwd.hpp>
#include <iostream>

#include "Assert.h"
#include "Engine/Application.h"
#include "Engine/Graphics/Material2D.h"
#include "Engine/Scene/Entity.h"
#include "Engine/VecConsts.h"
#include "ShapeFactory/Shape2DFactory.h"
using namespace VecConsts;

using namespace ShapeFactory;

class App : public Application {
 public:
  virtual void Init() {
    Application::Init();

    auto viewport = AddViewport(true);
    auto cam = viewport->scene_->camera_;
    cam->position_.z = 5;
    cam->LookAt(ZERO);

    auto material = new Material2D();
    material->color_ = GREEN;
    auto mesh = Shape2DFactory::SolidEllipse(ZERO, ONE * 2.f);
    mesh->Generate(material->shader_->id_);
    auto entity = new Entity(mesh, material);
    viewport->scene_->AddEntity(entity);
  }

  virtual void Update(float deltaTime) {
    viewports_[0]->scene_->camera_->Update(deltaTime_);
    Application::Update(deltaTime);
  }
};

int main() {
  assertColllide();

  App app;

  app.Init();

  app.Run();

  app.Terminate();

  return 0;
}
