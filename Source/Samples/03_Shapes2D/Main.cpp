#include <iostream>
#include <memory>

#include "Engine/Application.h"
#include "Engine/Graphics/Material2D.h"
#include "Engine/Graphics/Model.h"
#include "Engine/Scene/Component/ModelComponent.h"
#include "Engine/Scene/Scene.h"
#include "Engine/Scene/Viewport.h"
#include "Engine/VecConsts.h"
#include "ShapeFactory/Shape2DFactory.h"

using namespace std;
using namespace VecConsts;
using namespace ShapeFactory;

class App : public Application {
 public:
  virtual void Init() {
    Application::Init();

    glLineWidth(5);

    auto viewport = AddViewport(true);

    auto cam = viewport->GetScene()->camera_;
    cam->position_.z = 4.0f;

    viewport->AddEffect("Shaders/Effects/Noop.fs");
    // viewport->AddEffect("Shaders/Effects/Remove.fs");
    viewport->AddEffect("Shaders/Effects/Inversion.fs");

    // materials
    auto material1 = std::make_shared<Material2D>();
    material1->color_ = RED;

    auto material2 = std::make_shared<Material2D>();
    material2->color_ = GREEN;
    material2->alpha_ = 0.5;

    auto material3 = std::make_shared<Material2D>();
    material3->pctColor_ = 1.0;

    auto material4 = std::make_shared<Material2D>();
    material4->color_ = BLUE;

    auto material5 = std::make_shared<Material2D>();
    material5->pctColor_ = 1.0;

    // models
    auto solidRectMesh = std::shared_ptr<Mesh>(Shape2DFactory::SolidRect((LEFT + DOWN) / 2.f, vec2(1)));
    solidRectMesh->Generate(material1->GetShader()->GetId());
    auto solidRectModel = std::make_shared<Model>();
    solidRectModel->SetMaterial(material1);
    solidRectModel->SetMesh(solidRectMesh);

    auto transparentSolidRectMesh = std::shared_ptr<Mesh>(Shape2DFactory::SolidRect((LEFT + DOWN) / 2.f, vec2(1)));
    transparentSolidRectMesh->Generate(material2->GetShader()->GetId());
    auto transparentSolidRectModel = std::make_shared<Model>();
    transparentSolidRectModel->SetMaterial(material2);
    transparentSolidRectModel->SetMesh(transparentSolidRectMesh);

    auto lineMesh = std::shared_ptr<Mesh>(Shape2DFactory::Line(LEFT, RIGHT));
    lineMesh->colors_.push_back(GREEN);
    lineMesh->colors_.push_back(RED);
    lineMesh->Generate(material3->GetShader()->GetId());
    auto lineModel = std::make_shared<Model>();
    lineModel->SetMaterial(material3);
    lineModel->SetMesh(lineMesh);

    vector<vec3> points = {LEFT, DOWN, RIGHT, UP};
    auto linePolygonMesh = std::shared_ptr<Mesh>(Shape2DFactory::LinePolygon(points));
    linePolygonMesh->Generate(material4->GetShader()->GetId());
    auto linePolygonModel = std::make_shared<Model>();
    linePolygonModel->SetMaterial(material4);
    linePolygonModel->SetMesh(linePolygonMesh);

    auto solidPolygonMesh = std::shared_ptr<Mesh>(Shape2DFactory::SolidPolygon(points));
    solidPolygonMesh->colors_ = {GREEN, BLUE, RED, BLUE};
    solidPolygonMesh->Generate(material5->GetShader()->GetId());
    auto solidPolygonModel = std::make_shared<Model>();
    solidPolygonModel->SetMaterial(material5);
    solidPolygonModel->SetMesh(solidPolygonMesh);

    // entities
    auto entity = std::make_shared<Entity>();
    auto modelComponent = entity->AddComponent<ModelComponent>();
    modelComponent->SetModel(solidRectModel);
    viewport->GetScene()->AddEntity(entity);

    entity = std::make_shared<Entity>();
    modelComponent = entity->AddComponent<ModelComponent>();
    modelComponent->SetModel(transparentSolidRectModel);
    entity->position_ = (LEFT + DOWN) / 4.f;
    entity->position_.z = 0.25;
    entity->rotation_.y = pi<float>() / 4;
    viewport->GetScene()->AddEntity(entity);

    entity = std::make_shared<Entity>();
    modelComponent = entity->AddComponent<ModelComponent>();
    modelComponent->SetModel(lineModel);
    entity->position_.z = 1;
    viewport->GetScene()->AddEntity(entity);

    entity = std::make_shared<Entity>();
    modelComponent = entity->AddComponent<ModelComponent>();
    modelComponent->SetModel(linePolygonModel);
    viewport->GetScene()->AddEntity(entity);

    entity = std::make_shared<Entity>();
    modelComponent = entity->AddComponent<ModelComponent>();
    modelComponent->SetModel(solidPolygonModel);
    entity->scale_ *= 0.33f;
    entity->position_.z = 0.5;
    viewport->GetScene()->AddEntity(entity);

    cam->LookAt(ZERO);
  }
};

int main() {
  App app;

  app.Init();

  app.Run();

  app.Terminate();

  return 0;
}
