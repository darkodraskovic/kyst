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
    mesh->positions_ = points_;
    mesh->Generate();
    return mesh;
}

const std::vector<vec3>& Shape2DFactory::Rect(const vec3& position, const vec2& size)
{
    points_.clear();

    points_.push_back(position);
    points_.push_back(vec3(position.x + size.x, position.y, 0.0));
    points_.push_back(vec3(position.x + size.x, position.y + size.y, 0.0));
    points_.push_back(vec3(position.x, position.y + size.y, 0.0));
        
    return points_;
}

std::shared_ptr<Mesh> Shape2DFactory::RectMesh(const vec3& position, const vec2& size, bool filled)
{
    Rect(position, size);
    auto mesh = std::make_shared<Mesh>();
    if (filled) {
        auto& pos = mesh->positions_;
        pos.push_back(points_[0]); pos.push_back(points_[1]); pos.push_back(points_[3]);
        pos.push_back(points_[1]); pos.push_back(points_[2]); pos.push_back(points_[3]);
        mesh->mode_ = GL_TRIANGLES;
    } else {
        mesh->positions_ = points_;
        mesh->mode_ = GL_LINE_LOOP;
    }
    mesh->Generate();
    return mesh;
}
