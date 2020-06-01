#include <glm/fwd.hpp>
#include <glm/gtc/constants.hpp>

#include "ShapeUtils.h"
#include "VecConsts.h"
#include "Shape2DFactory.h"

using namespace VecConsts;

std::vector<vec3> Shape2DFactory::points_;

Shape2DFactory::Shape2DFactory()
{
}

const std::vector<vec3> Shape2DFactory::Line(const vec3& offset)
{
    points_.clear();
    points_.push_back(ZERO);
    points_.push_back(RIGHT);
    ShapeUtils::MovePoints(points_, offset);
    return points_;
};

const std::vector<vec3> Shape2DFactory::Rect(const ivec2& size, const vec3& offset, bool filled)
{
    points_.clear();
    vec3 a = vec3(0, 0, 0);
    vec3 b = vec3(size.x, 0, 0);
    vec3 c = vec3(size.x, size.y, 0);
    vec3 d = vec3(0, size.y, 0);

    if (filled) {
        points_.push_back(a); points_.push_back(b); points_.push_back(d);
        points_.push_back(b); points_.push_back(c); points_.push_back(d);
    }
    else {
        points_.push_back(a); points_.push_back(b);
        points_.push_back(b); points_.push_back(c);
        points_.push_back(c); points_.push_back(d);
        points_.push_back(d); points_.push_back(a);
    }
    ShapeUtils::MovePoints(points_, offset);
    
    return points_;
}
