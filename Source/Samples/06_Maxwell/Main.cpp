#include <iostream>

#include "Engine/Application.h"
#include "Engine/Graphics/Material2D.h"
#include "Engine/VecConsts.h"
#include "ShapeFactory/Shape2DFactory.h"

using namespace std;
using namespace VecConsts;
using namespace ShapeFactory;

class App : public Application {
 public:
  virtual void Init() {
    Application::Init();

    Viewport* viewport = AddViewport(true);
    auto cam = viewport->GetScene()->camera_;
    cam->position_.z = 5;
    cam->LookAt(ZERO);

    // Material
    Material2D* material = new Material2D();
    material->pctColor_ = 1;

    // Mesh
    vector<vec3> points = vector<vec3>{LEFT + DOWN, RIGHT + DOWN, UP};
    Mesh* mesh = Shape2DFactory::SolidPolygon(points);
    mesh->colors_ = std::vector<vec3>{RED, GREEN, BLUE};
    mesh->Generate(material->shader_->id_);

    // Entity
    Entity* entity = new Entity(mesh, material);
    viewport->GetScene()->AddEntity(entity);
  }

  virtual void Update(float deltaTime) {
    viewports_[0]->GetScene()->camera_->Update(deltaTime_, *GetInput());
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
