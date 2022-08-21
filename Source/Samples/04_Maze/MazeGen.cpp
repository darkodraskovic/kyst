#include "MazeGen.h"

#include <glm/gtc/constants.hpp>
#include <glm/gtc/random.hpp>

#include "Engine/Application.h"
#include "Engine/Graphics/Material.h"
#include "Engine/Graphics/Shader.h"
#include "Engine/Scene/Mover.h"
#include "Engine/VecConsts.h"
#include "ShapeFactory/MazeFactory.h"

using namespace VecConsts;
using namespace ShapeFactory;

MazeGen::MazeGen(Scene* scene) : scene_(scene) {}

std::shared_ptr<Mover> MazeGen::CreateMaze(int width, int height, const vec3& color) {
  std::shared_ptr<Mover> maze = std::make_shared<Mover>();
  maze->GetModel()->material_ = std::make_shared<Material>("Shaders/Col.vs", "Shaders/Col.fs");
  maze->GetModel()->material_->color_ = color;

  scene_->AddEntity(maze);
  auto mazeFactory = new MazeFactory(width, height);
  mazeFactory->RandomWalk();
  auto vertexArray = mazeFactory->GetVertexArray();

  auto mesh = std::make_shared<Mesh>();
  maze->GetModel()->mesh_ = mesh;
  mesh->GenArrayBuffer(vertexArray);
  mesh->mode_ = GL_LINES;

  maze->scale_ = ONE / 4.f;

  return maze;
}
