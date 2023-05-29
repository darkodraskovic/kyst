#ifndef MAZE_GEN_H
#define MAZE_GEN_H

#pragma once

#include <glm/glm.hpp>

#include "Engine/Scene/Scene.h"
#include "Engine/Scene/Component/Mover.h"

using namespace glm;
using namespace Kyst;

class MazeGen {
 public:
  MazeGen(Scene* scene);
  std::shared_ptr<Entity> CreateMaze(int width, int height, const vec3& color);

 private:
  Scene* scene_;
};

#endif
