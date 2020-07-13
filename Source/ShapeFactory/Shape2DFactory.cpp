#include <glm/fwd.hpp>
#include <glm/gtc/constants.hpp>
#include <memory>

#include "Mesh.h"
#include "ShapeUtils.h"
#include "VecConsts.h"
#include "Shape2DFactory.h"

using namespace VecConsts;

std::vector<vec3> Shape2DFactory::points_;

Shape2DFactory::Shape2DFactory()
{
}

const std::vector<vec3>& Shape2DFactory::Line(const vec3 &point1,
                                             const vec3 &point2) {
  points_.clear();
  points_.push_back(point1);
  points_.push_back(point2);
  return points_;
}

std::shared_ptr<Mesh> Shape2DFactory::LineMesh(const vec3 &point1,
                                             const vec3 &point2) {
    Line(point1, point2);
    auto mesh = std::make_shared<Mesh>();
    mesh->mode_ = GL_LINES;
    mesh->GenArrayBuffer(points_);
    return mesh;
}

const std::vector<vec3>& Shape2DFactory::Rect(const vec3& position, const vec2& size, bool filled)
{
    points_.clear();
    vec3 a = position;
    vec3 b = vec3(position.x + size.x, position.y, 0.0);
    vec3 c = vec3(position.x + size.x, position.y + size.y, 0.0);
    vec3 d = vec3(position.x, position.y + size.y, 0);

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

    return points_;
}

std::shared_ptr<Mesh> Shape2DFactory::RectMesh(const vec3& position, const vec2& size, bool filled)
{
    Rect(position, size, filled);
    auto mesh = std::make_shared<Mesh>();
    mesh->mode_ = GL_LINES;
    if (filled) {
        mesh->mode_ = GL_TRIANGLES;
    }
    mesh->GenArrayBuffer(points_);
    return mesh;
}
