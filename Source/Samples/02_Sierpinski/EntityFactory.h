#ifndef ENTITY_FACTORY_H
#define ENTITY_FACTORY_H

#pragma once

#include "Engine/Application.h"
#include "Engine/Graphics/Shader.h"
#include "Engine/Scene/Component/ParticleEmitter.h"
#include "Engine/Scene/Entity.h"
#include "Engine/VecConsts.h"

using namespace Kyst;
using namespace VecConsts;

#include <glm/glm.hpp>
#include <vector>

using namespace glm;

class EntityFactory {
 public:
  EntityFactory(Scene* scene, const vec3& col1 = RED, const vec3& col2 = GREEN, const vec3& col3 = BLUE);

  Entity* AddEntity(bool vCol);
  void CreateLineGasket(int numDivisions, const vec2& varRange, bool threeD, bool vCol);
  void CreateTriGasket(int numDivisions, const vec2& varRange, bool threeD, bool vCol);

  Entity* CreateSnowflakeEmitter();

  vec3 color1_ = RED;
  vec3 color2_ = GREEN;
  vec3 color3_ = BLUE;

 private:
  std::shared_ptr<Material> colMaterial_;
  std::shared_ptr<Material> vColMaterial_;
  std::shared_ptr<Mesh> snowflakeMesh_;

  Scene* scene_;
};

#endif
