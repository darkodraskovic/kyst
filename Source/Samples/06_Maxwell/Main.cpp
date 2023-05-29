#include <iostream>

#include "Engine/Application.h"
#include "Engine/Scene/Viewport.h"
#include "Engine/Scene/Scene.h"
#include "Engine/Scene/Component/CameraComponent.h"
#include "Engine/Scene/Component/ModelComponent.h"
#include "Engine/Scene/Entity.h"
#include "Engine/Graphics/Material2D.h"
#include "Engine/VecConsts.h"
#include "ShapeFactory/Shape2DFactory.h"

using namespace std;
using namespace VecConsts;
using namespace ShapeFactory;

using namespace Kyst;

class App : public Application {
 public:
  virtual void Init() {
    Application::Init();

    Viewport* viewport = AddViewport(true);
    auto* camComponent = viewport->GetScene()->cameraComponent_;
    auto* camEntity = camComponent->GetEntity();
    camEntity->position_.z = 5;
    viewport->GetScene()->cameraComponent_->GetCamera()->LookAt(ZERO, camEntity->position_, camEntity->rotation_);

    // Material
    auto material = std::make_shared<Material2D>();
    material->pctColor_ = 1;

    // Mesh
    vector<vec3> points = vector<vec3>{LEFT + DOWN, RIGHT + DOWN, UP};
    auto mesh = std::shared_ptr<Mesh>(Shape2DFactory::SolidPolygon(points));
    mesh->colors_ = std::vector<vec3>{RED, GREEN, BLUE};
    mesh->Generate(material->GetShader()->GetId());

    // Entity
    auto entity = std::make_shared<Entity>();
    ModelComponent* modelComponent = entity->AddComponent<ModelComponent>();
    auto model = std::make_shared<Model>();
    modelComponent->SetModel(model);
    model->SetMaterial(material);
    model->SetMesh(mesh);

    model->GetMesh()->Generate(material->GetShader()->GetId());
    viewport->GetScene()->AddEntity(entity);
  }

  // virtual void Update(float deltaTime) {
  //   viewports_[0]->GetScene()->GetViewport->->Update(deltaTime_, *GetInput());
  //   Application::Update(deltaTime);
  // }
};

int main() {
  App app;

  app.Init();

  app.Run();

  app.Terminate();

  return 0;
}
