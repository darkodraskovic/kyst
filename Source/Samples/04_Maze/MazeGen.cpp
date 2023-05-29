#include "MazeGen.h"

#include <glm/gtc/constants.hpp>
#include <glm/gtc/random.hpp>

#include "Engine/Application.h"
#include "Engine/Graphics/Material.h"
#include "Engine/Graphics/Shader.h"
#include "Engine/Scene/Component/ModelComponent.h"
#include "Engine/Scene/Component/Mover.h"
#include "Engine/Scene/Entity.h"
#include "Engine/VecConsts.h"
#include "ShapeFactory/MazeFactory.h"

using namespace Kyst::VecConsts;
using namespace ShapeFactory;

MazeGen::MazeGen(Scene* scene) : scene_(scene) {}

std::shared_ptr<Entity> MazeGen::CreateMaze(int width, int height, const vec3& color) {
  auto maze = std::make_shared<Entity>();
  maze->scale_ = ONE / 4.f;

  // mover
  Mover* mover = maze->AddComponent<Mover>();

  // model
  auto model = std::make_shared<Model>();

  auto shader = std::make_shared<Shader>("Shaders/Col.vs", "Shaders/Col.fs");

  auto material = std::make_shared<Material>();
  material->SetShader(shader);
  material->color_ = color;

  auto mazeFactory = new MazeFactory(width, height);
  mazeFactory->RandomWalk();
  auto vertexArray = mazeFactory->GetVertexArray();

  auto mesh = std::make_shared<Mesh>();
  mesh->GenArrayBuffer(vertexArray);
  mesh->mode_ = GL_LINES;

  model->SetMesh(mesh);
  model->SetMaterial(material);

  ModelComponent* modelComponent = maze->AddComponent<ModelComponent>();
  modelComponent->SetModel(model);

  // scene
  scene_->AddEntity(maze);

  return maze;
}
