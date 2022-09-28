#include <memory>

#include "Engine/Application.h"
#include "Engine/Graphics/Material2D.h"
#include "Engine/Scene/Component/ModelComponent.h"
#include "Engine/Scene/Entity.h"
#include "Engine/Scene/Scene.h"
#include "Engine/Scene/Viewport.h"
#include "Engine/VecConsts.h"
#include "ShapeFactory/Shape2DFactory.h"

using namespace VecConsts;
using namespace ShapeFactory;

std::shared_ptr<Entity> GenEntity(const string& fragmentPath, const vec3& position) {
  Material2D* material = new Material2D(fragmentPath);
  Mesh* mesh = Shape2DFactory::SolidRect(LEFT + DOWN, glm::vec2(2, 2));
  mesh->Generate(material->GetShader()->GetId());

  auto model = make_shared<Model>();
  model->SetMaterial(std::shared_ptr<Material2D>(material));
  model->SetMesh(std::shared_ptr<Mesh>(mesh));

  auto entity = make_shared<Entity>();
  auto modelComponent = entity->AddComponent<ModelComponent>();
  modelComponent->SetModel(model);
  entity->position_ = position;
  return entity;
}

class App : public Application {
 public:
  virtual void Init() {
    Application::Init();

    auto viewport = AddViewport(true);
    auto cam = viewport->GetScene()->cameraComponent_->GetCamera();
    auto camEntity = viewport->GetScene()->cameraComponent_->GetEntity();

    camEntity->position_.z = 7.0f;
    cam->LookAt(ZERO, camEntity->position_, camEntity->rotation_);

    // viewport->AddEffect("Shaders/Effects/Noop.fs");
    // viewport->AddEffect("Shaders/Effects/Inversion.fs");
    // viewport->AddEffect("Shaders/Effects/Remove.fs");

    viewport->GetScene()->AddEntity(GenEntity("Shaders/GenArt/01.fs", LEFT + DOWN));
    viewport->GetScene()->AddEntity(GenEntity("Shaders/GenArt/02.fs", RIGHT + DOWN));
    viewport->GetScene()->AddEntity(GenEntity("Shaders/GenArt/03.fs", RIGHT + UP));
    viewport->GetScene()->AddEntity(GenEntity("Shaders/GenArt/04_tiling.fs", LEFT + UP));
  }
};

int main() {
  App app;

  app.Init();

  app.Run();

  app.Terminate();

  return 0;
}
