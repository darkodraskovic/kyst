#ifndef VEC_CONSTS_H
#define VEC_CONSTS_H

#include <glm/glm.hpp>

using namespace glm;

namespace VecConsts
{
    // Directions
    const vec3 UP(0.0f, 1.0f, 0.0f);
    const vec3 DOWN(0.0f, -1.0f, 0.0f);
    const vec3 RIGHT(1.0f, 0.0f, 0.0f);
    const vec3 LEFT(-1.0f, 0.0f, 0.0f);
    const vec3 FORWARD(0.0f, 0.0f, 1.0f);
    const vec3 BACK(0.0f, 0.0f, -1.0f);
    const vec3 ZERO(0.0f, 0.0f, 0.0f);
    const vec3 ONE(1.0f, 1.0f, 1.0f);
    const vec2 UP_2D(0.0f, 1.0f);
    const vec2 DOWN_2D(0.0f, -1.0f);
    const vec2 RIGHT_2D(1.0f, 0.0f);
    const vec2 LEFT_2D(-1.0f, 0.0f);
    const vec2 FORWARD_2D(0.0f, 0.0f);
    const vec2 ZERO_2D(0.0f, 0.0f);
    const vec2 ONE_2D(1.0f, 1.0f);

    // Colors
    const vec3 RED(1.0f, 0.0f, 0.0f);
    const vec3 GREEN(0.0f, 1.0f, 0.0f);
    const vec3 BLUE(0.0f, 0.0f, 1.0f);
    const vec3 YELLOW(1.0f, 1.0f, 0.0f);
    const vec3 MAGENTA(1.0f, 0.0f, 1.0f);
    const vec3 CYAN(0.0f, 1.0f, 1.0f);
    
    const vec3 BLACK(0.0f, 0.0f, 0.0f);
    const vec3 WHITE(1.0f, 1.0f, 1.0f);
    const vec3 DARK_GRAY(0.2f, 0.2f, 0.2f);    
    const vec3 GRAY(0.5f, 0.5f, 0.5f);
    const vec3 LIGHT_GRAY(0.8f, 0.8f, 0.8f);
}

#endif
