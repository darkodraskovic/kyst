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

std::shared_ptr<Mesh> Shape2DFactory::Line(const vec3 &point1,
                                             const vec3 &point2) {
    auto mesh = std::make_shared<Mesh>();
    mesh->mode_ = GL_LINES;
    mesh->positions_.push_back(point1);
    mesh->positions_.push_back(point2);
    return mesh;
}

std::shared_ptr<Mesh> Shape2DFactory::Lines(const vec3& offset, const std::vector<vec3>& points)
{
    auto mesh = std::make_shared<Mesh>();
    mesh->positions_ = points;
    mesh->mode_ = GL_LINE_STRIP;
    return mesh;
}

const std::vector<vec3>& Shape2DFactory::RectPoints(const vec3& offset, const vec2& size)
{
    points_.clear();

    points_.push_back(offset);
    points_.push_back(vec3(offset.x + size.x, offset.y, 0.0));
    points_.push_back(vec3(offset.x + size.x, offset.y + size.y, 0.0));
    points_.push_back(vec3(offset.x, offset.y + size.y, 0.0));
        
    return points_;
}

std::shared_ptr<Mesh> Shape2DFactory::RectMesh(const vec3& offset, const vec2& size)
{
    RectPoints(offset, size);
    auto mesh = std::make_shared<Mesh>();
    mesh->positions_ = points_;
    mesh->texCoords_.push_back(vec2(0,0)); mesh->texCoords_.push_back(vec2(1,0));
    mesh->texCoords_.push_back(vec2(1,1)); mesh->texCoords_.push_back(vec2(0,1));
    return mesh;
}

std::shared_ptr<Mesh> Shape2DFactory::LineRect(const vec3& offset, const vec2& size)
{
    auto mesh = RectMesh(offset, size);
    mesh->mode_ = GL_LINE_LOOP;
    return mesh;
}

std::shared_ptr<Mesh> Shape2DFactory::SolidRect(const vec3& offset, const vec2& size)
{
    auto mesh = RectMesh(offset, size);
    mesh->mode_ = GL_TRIANGLE_FAN;
    return mesh;
}

std::shared_ptr<Mesh> Shape2DFactory::LinePolygon(const vec3& offset, const std::vector<vec3>& points)
{
    auto mesh = std::make_shared<Mesh>();
    mesh->positions_ = points;
    mesh->mode_ = GL_LINE_LOOP;
    return mesh;
}

std::shared_ptr<Mesh> Shape2DFactory::SolidPolygon(const vec3& offset, const std::vector<vec3>& points)
{
    auto mesh = std::make_shared<Mesh>();
    mesh->positions_ = points;
    mesh->mode_ = GL_TRIANGLE_FAN;
    return mesh;
}
