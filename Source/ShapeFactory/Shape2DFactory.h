#ifndef SHAPE2D_FACTORY_H
#define SHAPE2D_FACTORY_H

#include <glm/fwd.hpp>
#pragma once

#include "Entity.h"

#include_next <vector>
#include_next <glm/glm.hpp>

using namespace glm;

class Shape2DFactory
{
public:
    Shape2DFactory();

    static const std::vector<vec3> Line(const vec3& offset);
    static const std::vector<vec3> Rect(const ivec2& size, const vec3& offset, bool filled);

private:
    static void OffsetPoints(const vec3& offset);
    static std::vector<vec3> points_;
};

#endif
