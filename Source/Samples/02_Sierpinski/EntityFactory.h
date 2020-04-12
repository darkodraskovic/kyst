#ifndef ENTITY_FACTORY_H
#define ENTITY_FACTORY_H

#pragma once

#include "Entity.h"
#include "Shader.h"
#include "Application.h"
#include "VecConsts.h"

using namespace VecConsts;



#include_next <vector>
#include_next <glm/glm.hpp>

using namespace glm;

class EntityFactory
{
public:
    EntityFactory(Application* app);

    std::shared_ptr<Entity> CreateEntity(bool vCol);
    std::shared_ptr<Entity> CreateLineGasket(int numDivisions, const vec2& varRange, bool threeD, bool vCol);
    std::shared_ptr<Entity> CreateTriGasket(int numDivisions, const vec2& varRange, bool threeD, bool vCol);

    std::shared_ptr<Entity> CreateSnowflake(int numDivisions);
    
    std::shared_ptr<Shader> colShader_;
    std::shared_ptr<Shader> vColShader_;

    void SetColor(const vec3& color);
    
    vec3 color1_ = RED;
    vec3 color2_ = GREEN;
    vec3 color3_ = BLUE;
    
private:
    Application* app_;
};

#endif
