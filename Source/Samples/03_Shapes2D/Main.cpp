#include <iostream>
#include <memory>

#include "Engine/Application.h"
#include "Engine/Graphics/Material2D.h"
#include "Engine/Scene/Viewport.h"
#include "Engine/VecConsts.h"
#include "ShapeFactory/Shape2DFactory.h"

using namespace std;
using namespace VecConsts;
using namespace ShapeFactory;

class App : public Application {
 public:
  virtual int Init() {
    Application::Init();

    glLineWidth(5);

    auto viewport = AddViewport(true);

    auto cam = viewport->scene_->camera_;
    cam->position_.z = 4.0f;

    viewport->AddEffect("Shaders/Effects/Noop.fs");
    viewport->AddEffect("Shaders/Effects/Inversion.fs");
    // viewport->AddEffect("Shaders/Effects/Remove.fs");

    // material
    auto material1 = new Material2D();
    material1->color_ = RED;
    auto material2 = new Material2D();
    material2->color_ = GREEN;
    material2->alpha_ = 0.5;
    auto material3 = new Material2D();
    material3->color_ = BLUE;
    material3->pctColor_ = 1.0;
    auto material4 = new Material2D();
    material4->color_ = BLUE;
    auto material5 = new Material2D();
    material5->pctColor_ = 1.0;

    // rect mesh
    auto mesh = Shape2DFactory::SolidRect((LEFT + DOWN) / 2.f, vec2(1));
    mesh->Generate(material1->shader_->id_);

    // rect entity 1
    auto entity = new Entity(mesh, material1);
    viewport->scene_->AddEntity(entity);

    // rect entity 2
    entity = new Entity(entity->mesh_, shared_ptr<Material2D>(material2));
    entity->position_ = (LEFT + DOWN) / 4.f;
    entity->position_.z = 0.25;
    entity->rotation_.y = pi<float>() / 4;
    viewport->scene_->AddEntity(entity);

    // line entity 3
    mesh = Shape2DFactory::Line(LEFT, RIGHT);
    mesh->colors_.push_back(GREEN);
    mesh->colors_.push_back(RED);
    mesh->Generate(material2->shader_->id_);
    entity = new Entity(mesh, material3);
    entity->position_.z = 1;
    viewport->scene_->AddEntity(entity);

    // polygons 4, 5
    vector<vec3> points = {LEFT, DOWN, RIGHT, UP};
    mesh = Shape2DFactory::LinePolygon(points);
    mesh->Generate(material1->shader_->id_);
    entity = new Entity(mesh, material4);
    viewport->scene_->AddEntity(entity);

    mesh = Shape2DFactory::SolidPolygon(points);
    mesh->colors_ = {GREEN, BLUE, RED, BLUE};
    mesh->Generate(material5->shader_->id_);
    entity = new Entity(mesh, material5);
    entity->scale_ *= 0.33f;
    entity->position_.z = 0.5;
    viewport->scene_->AddEntity(entity);

    cam->LookAt(ZERO);
    // Application loop

    return 0;
  }

  virtual void ProcessInput() {
    Application::ProcessInput();
    if (input_->GetKey(GLFW_KEY_ESCAPE)) Close();
  }

  virtual void Update(float deltaTime) {
    viewports_[0]->scene_->camera_->ProcessInput(input_, deltaTime_);
    Application::Update(deltaTime);
  }
};

int main() {
  App app;

  if (app.Init() < 0) {
    std::cout << "Failed to create an OpenGL app" << std::endl;
    return -1;
  };

  // ---------------------------------------------------------------------------
  while (!app.ShouldClose()) {
    app.Run();
  }

  // Application termination
  // ---------------------------------------------------------------------------
  app.Terminate();
  return 0;
}
