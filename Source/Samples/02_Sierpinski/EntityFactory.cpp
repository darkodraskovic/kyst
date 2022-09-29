#include "EntityFactory.h"

#include <glm/gtc/constants.hpp>
#include <glm/gtc/random.hpp>

#include "Engine/Graphics/Material.h"
#include "Engine/Scene/Component/ModelComponent.h"
#include "Engine/Scene/Component/Mover.h"
#include "Engine/Scene/Scene.h"
#include "ShapeFactory/KochFactory.h"
#include "ShapeFactory/MazeFactory.h"
#include "ShapeFactory/SierpinskiFactory.h"

using namespace ShapeFactory;

EntityFactory::EntityFactory(Scene* scene, const vec3& col1, const vec3& col2, const vec3& col3) : scene_(scene) {
  color1_ = col1;
  color2_ = col2;
  color3_ = col3;

  // make materials
  auto colShader = std::make_shared<Shader>("Shaders/Col.vs", "Shaders/Col.fs");
  colMaterial_ = std::make_shared<Material>();
  colMaterial_->SetShader(colShader);
  colMaterial_->color_ = color3_;

  auto vColShader = std::make_shared<Shader>("Shaders/VCol.vs", "Shaders/VCol.fs");
  vColMaterial_ = std::make_shared<Material>();
  vColMaterial_->SetShader(vColShader);
  vColMaterial_->color_ = color3_;

  // make mesh
  snowflakeMesh_ = std::make_shared<Mesh>();
  snowflakeMesh_->mode_ = GL_LINE_LOOP;
  snowflakeMesh_->positions_ = KochFactory::Snowflake(3);
  snowflakeMesh_->Generate(colMaterial_->GetShader()->GetId());
}

Entity* EntityFactory::AddEntity(bool vCol) {
  auto model = std::make_shared<Model>();
  model->SetMaterial(colMaterial_);
  if (vCol) {
    model->SetMaterial(vColMaterial_);
  }

  auto entity = std::make_shared<Entity>();
  auto modelComponent = entity->AddComponent<ModelComponent>();
  modelComponent->SetModel(model);
  entity->AddComponent<Mover>();

  scene_->AddEntity(entity);
  return entity.get();
}

void EntityFactory::CreateLineGasket(int numDivisions, const vec2& varRange, bool threeD, bool vCol) {
  auto gasket = AddEntity(vCol);
  gasket->name_ = "gasket";
  auto* mover = gasket->GetComponent<Mover>();
  auto* model = gasket->GetComponent<ModelComponent>()->GetModel();

  mover->aVelocity_.y = quarter_pi<float>();

  model->SetMesh(std::make_shared<Mesh>());
  SierpinskiFactory::varRange_ = varRange;
  auto points = threeD ? SierpinskiFactory::Sierpinski3DDet(numDivisions) : SierpinskiFactory::Sierpinski2DDet(numDivisions);
  model->GetMesh()->mode_ = GL_LINES;
  std::vector<vec3>& lines = model->GetMesh()->positions_;
  for (int i = 0; i < points.size(); i += 3) {
    lines.push_back(points.at(i));
    lines.push_back(points.at(i + 1));
    lines.push_back(points.at(i + 1));
    lines.push_back(points.at(i + 2));
    lines.push_back(points.at(i + 2));
    lines.push_back(points.at(i));
  }

  if (!vCol) {
    model->GetMesh()->Generate(model->GetMaterial()->GetShader()->GetId());
  };

  std::vector<vec3>& colors = model->GetMesh()->colors_;
  for (int i = 0; i < lines.size(); i += 6) {
    colors.push_back(color1_);
    colors.push_back(color1_);
    colors.push_back(color2_);
    colors.push_back(color2_);
    colors.push_back(color3_);
    colors.push_back(color3_);
  }

  model->GetMesh()->Generate(model->GetMaterial()->GetShader()->GetId());
}

void EntityFactory::CreateTriGasket(int numDivisions, const vec2& varRange, bool threeD, bool vCol) {
  auto gasket = AddEntity(vCol);
  auto* mover = gasket->GetComponent<Mover>();
  auto* model = gasket->GetComponent<ModelComponent>()->GetModel();

  mover->aVelocity_.y = quarter_pi<float>();

  model->SetMesh(std::make_shared<Mesh>());
  SierpinskiFactory::varRange_ = varRange;
  model->GetMesh()->positions_ =
      threeD ? SierpinskiFactory::Sierpinski3DDet(numDivisions) : SierpinskiFactory::Sierpinski2DDet(numDivisions);
  model->GetMesh()->mode_ = GL_TRIANGLES;

  if (!vCol) {
    model->GetMesh()->Generate(model->GetMaterial()->GetShader()->GetId());
  };

  std::vector<vec3>& colors = model->GetMesh()->colors_;
  for (int i = 0; i < model->GetMesh()->positions_.size(); i += 3) {
    int idx = (i / 3) % 3;
    vec3 color = color1_;
    if (idx == 1) {
      color = color2_;
    } else if (idx == 2) {
      color = color3_;
    }
    for (int j = 0; j < 3; ++j) colors.push_back(color);
  }

  model->GetMesh()->Generate(model->GetMaterial()->GetShader()->GetId());
}

Entity* EntityFactory::CreateSnowflakeEmitter() {
  auto entity = std::make_shared<Entity>();
  entity->name_ = "emitter";
  entity->position_ = UP;
  scene_->AddEntity(entity);

  auto model = std::make_shared<Model>();
  model->SetMesh(snowflakeMesh_);
  model->SetMaterial(colMaterial_);

  auto* emitter = entity->AddComponent<ParticleEmitter>();
  emitter->SetModel(model);

  emitter->emissionFreq_ = .05f;

  emitter->minScale_ = ONE * 0.01f;
  emitter->maxScale_ = ONE * 0.1f;

  emitter->minVelocity_.y = 1.f;
  emitter->maxVelocity_.y = 1.5f;
  emitter->minGravity_ = DOWN * .7f;
  emitter->maxGravity_ = DOWN * .8f;

  emitter->minLifespan_ = 2.f;
  emitter->maxLifespan_ = 3.f;

  return entity.get();
}
