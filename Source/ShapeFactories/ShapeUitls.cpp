#include "ShapeUitls.h"
#include <glm/gtc/random.hpp>

ShapeUtils::ShapeUtils()
{
}

void ShapeUtils::prodPoint(vec3& point, float min, float max)
{
    vec3 delta(linearRand(min, max), linearRand(min, max), linearRand(min, max));
    point += delta;
}

