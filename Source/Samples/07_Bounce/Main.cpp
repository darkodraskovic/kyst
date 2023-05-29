#include <cassert>
#include <glm/ext/scalar_constants.hpp>
#include <glm/fwd.hpp>
#include <iostream>

#include "Assert.h"
#include "Engine/Application.h"
#include "Engine/Scene/Viewport.h"
#include "Engine/Scene/Scene.h"
#include "Engine/Graphics/Material2D.h"
#include "Engine/Scene/Entity.h"
#include "Engine/VecConsts.h"
#include "Engine/Scene/Component/ModelComponent.h"
#include "ShapeFactory/Shape2DFactory.h"
using namespace VecConsts;

using namespace ShapeFactory;

class App : public Application {
 public:
  virtual void Init() {
    Application::Init();

    auto viewport = AddViewport(true);
    auto* camComponent = viewport->GetScene()->cameraComponent_;
    auto* camEntity = camComponent->GetEntity();
    camEntity->position_.z = 5;
    camComponent->GetCamera()->LookAt(ZERO, camEntity->position_, camEntity->rotation_);

    auto material = std::make_shared<Material2D>();
    material->color_ = GREEN;
    
    auto mesh = std::shared_ptr<Mesh>(Shape2DFactory::SolidEllipse(ZERO, ONE * 2.f));
    mesh->Generate(material->GetShader()->GetId());
    
    auto entity = std::make_shared<Entity>();
    ModelComponent* modelComponent = entity->AddComponent<ModelComponent>();
    auto model = std::make_shared<Model>();
    modelComponent->SetModel(model);
    model->SetMaterial(material);
    model->SetMesh(mesh);

    viewport->GetScene()->AddEntity(entity);
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
