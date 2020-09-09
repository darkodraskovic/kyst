#ifndef SHAPE_UTILS_H
#define SHAPE_UTILS_H

#include <string>
#include <vector>
#include <glm/fwd.hpp>
#include <glm/glm.hpp>

using namespace glm;

class ShapeUtils
{
public:
    ShapeUtils();

    static void ProdPoint(vec3& point, float min, float max);
    static vec3 Hex2rgb(std::string hex);
};

#endif
