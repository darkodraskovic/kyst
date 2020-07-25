#ifndef ENTITY_FACTORY_H
#define ENTITY_FACTORY_H

#pragma once

#include "Application.h"
#include "Entity.h"
#include "Shader.h"
#include "VecConsts.h"
#include "ParticleEmitter.h"

using namespace VecConsts;

#include_next <vector>
#include_next <glm/glm.hpp>

using namespace glm;

class EntityFactory
{
public:
    EntityFactory();
    
    std::shared_ptr<Mover> AddMover(bool vCol);
    std::shared_ptr<Mover> CreateLineGasket(int numDivisions, const vec2& varRange, bool threeD, bool vCol);
    std::shared_ptr<Mover> CreateTriGasket(int numDivisions, const vec2& varRange, bool threeD, bool vCol);

    std::shared_ptr<ParticleEmitter> CreateSnowflakeEmitter();

    std::shared_ptr<Shader> colShader_;
    std::shared_ptr<Shader> vColShader_;

    vec3 color1_ = RED;
    vec3 color2_ = GREEN;
    vec3 color3_ = BLUE;
    
private:
    std::shared_ptr<Mesh> snowflakeMesh_;
};

#endif
