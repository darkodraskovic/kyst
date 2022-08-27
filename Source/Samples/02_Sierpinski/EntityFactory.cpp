#include "EntityFactory.h"

#include <glm/gtc/constants.hpp>
#include <glm/gtc/random.hpp>

#include "Engine/Graphics/Material.h"
#include "Engine/Scene/Mover.h"
#include "Engine/Scene/Particle.h"
#include "Engine/Scene/Scene.h"
#include "ShapeFactory/KochFactory.h"
#include "ShapeFactory/MazeFactory.h"
#include "ShapeFactory/SierpinskiFactory.h"

using namespace ShapeFactory;

EntityFactory::EntityFactory(Scene* scene) : scene_(scene) {
  colMaterial_ = std::make_shared<Material>("Shaders/Col.vs", "Shaders/Col.fs");
  vColMaterial = std::make_shared<Material>("Shaders/VCol.vs", "Shaders/VCol.fs");

  snowflakeMesh_ = std::make_shared<Mesh>();
  snowflakeMesh_->mode_ = GL_LINE_LOOP;
  snowflakeMesh_->positions_ = KochFactory::Snowflake(3);
  snowflakeMesh_->Generate(colMaterial_->GetShader()->GetId());
}

Mover* EntityFactory::AddMover(bool vCol) {
  auto mover = std::make_shared<Mover>();
  mover->SetModel(std::make_shared<Model>());
  mover->GetModel()->SetMaterial(colMaterial_);
  mover->GetModel()->GetMaterial()->color_ = color1_;
  if (vCol) {
    mover->GetModel()->SetMaterial(vColMaterial);
  }

  scene_->AddEntity(mover);
  return mover.get();
}

void EntityFactory::CreateLineGasket(int numDivisions, const vec2& varRange, bool threeD, bool vCol) {
  auto gasket = AddMover(vCol);
  gasket->name_ = "gasket";

  gasket->aVelocity_.y = quarter_pi<float>();

  gasket->GetModel()->SetMesh(std::make_shared<Mesh>());
  SierpinskiFactory::varRange_ = varRange;
  auto points = threeD ? SierpinskiFactory::Sierpinski3DDet(numDivisions) : SierpinskiFactory::Sierpinski2DDet(numDivisions);
  gasket->GetModel()->GetMesh()->mode_ = GL_LINES;
  std::vector<vec3>& lines = gasket->GetModel()->GetMesh()->positions_;
  for (int i = 0; i < points.size(); i += 3) {
    lines.push_back(points.at(i));
    lines.push_back(points.at(i + 1));
    lines.push_back(points.at(i + 1));
    lines.push_back(points.at(i + 2));
    lines.push_back(points.at(i + 2));
    lines.push_back(points.at(i));
  }

  if (!vCol) {
    gasket->GetModel()->GetMesh()->Generate(gasket->GetModel()->GetMaterial()->GetShader()->GetId());
  };

  std::vector<vec3>& colors = gasket->GetModel()->GetMesh()->colors_;
  for (int i = 0; i < lines.size(); i += 6) {
    colors.push_back(color1_);
    colors.push_back(color1_);
    colors.push_back(color2_);
    colors.push_back(color2_);
    colors.push_back(color3_);
    colors.push_back(color3_);
  }

  gasket->GetModel()->GetMesh()->Generate(gasket->GetModel()->GetMaterial()->GetShader()->GetId());
}

void EntityFactory::CreateTriGasket(int numDivisions, const vec2& varRange, bool threeD, bool vCol) {
  auto gasket = AddMover(vCol);
  gasket->aVelocity_.y = quarter_pi<float>();

  gasket->GetModel()->SetMesh(std::make_shared<Mesh>());
  SierpinskiFactory::varRange_ = varRange;
  gasket->GetModel()->GetMesh()->positions_ =
      threeD ? SierpinskiFactory::Sierpinski3DDet(numDivisions) : SierpinskiFactory::Sierpinski2DDet(numDivisions);
  gasket->GetModel()->GetMesh()->mode_ = GL_TRIANGLES;

  if (!vCol) {
    gasket->GetModel()->GetMesh()->Generate(gasket->GetModel()->GetMaterial()->GetShader()->GetId());
  };

  std::vector<vec3>& colors = gasket->GetModel()->GetMesh()->colors_;
  for (int i = 0; i < gasket->GetModel()->GetMesh()->positions_.size(); i += 3) {
    int idx = (i / 3) % 3;
    vec3 color = color1_;
    if (idx == 1) {
      color = color2_;
    } else if (idx == 2) {
      color = color3_;
    }
    for (int j = 0; j < 3; ++j) colors.push_back(color);
  }

  gasket->GetModel()->GetMesh()->Generate(gasket->GetModel()->GetMaterial()->GetShader()->GetId());
}

ParticleEmitter* EntityFactory::CreateSnowflakeEmitter() {
  auto emitter = std::make_shared<ParticleEmitter>();
  emitter->name_ = "emitter";
  emitter->SetModel(std::make_shared<Model>());
  emitter->GetModel()->SetMesh(snowflakeMesh_);
  emitter->GetModel()->SetMaterial(colMaterial_);
  emitter->GetModel()->GetMaterial()->color_ = color3_;

  emitter->emissionFreq_ = .03f;

  emitter->position_ = UP;
  emitter->minScale_ = ONE * 0.01f;
  emitter->maxScale_ = ONE * 0.1f;

  emitter->minVelocity_.y = 1.f;
  emitter->maxVelocity_.y = 1.5f;
  emitter->minGravity_ = DOWN * .7f;
  emitter->maxGravity_ = DOWN * .8f;

  emitter->minLifespan_ = 2.f;
  emitter->maxLifespan_ = 3.f;

  scene_->AddEntity(emitter);

  return emitter.get();
}
