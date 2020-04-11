#ifndef SHAPE_UTILS_H
#define SHAPE_UTILS_H

#include <glm/glm.hpp>

using namespace glm;

class ShapeUtils
{
public:
    ShapeUtils();

    static void prodPoint(vec3& point, float min, float max);
};

#endif
