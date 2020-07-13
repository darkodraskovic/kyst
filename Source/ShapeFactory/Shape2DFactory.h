#ifndef SHAPE2D_FACTORY_H
#define SHAPE2D_FACTORY_H

#include "Mesh.h"
#include <glm/fwd.hpp>
#include <memory>
#pragma once

#include "Entity.h"

#include_next <vector>
#include_next <glm/glm.hpp>

using namespace glm;

class Shape2DFactory
{
public:
    Shape2DFactory();

    static const std::vector<vec3>& Line(const vec3& point1, const vec3& point2);
    static std::shared_ptr<Mesh> LineMesh(const vec3& point1, const vec3& point2);
    static const std::vector<vec3>& Rect(const vec3& position, const vec2& size, bool filled);
    static std::shared_ptr<Mesh> RectMesh(const vec3& position, const vec2& size, bool filled);

private:
    static std::vector<vec3> points_;
};

#endif
