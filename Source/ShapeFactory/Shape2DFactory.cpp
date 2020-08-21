#include <glm/fwd.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/trigonometric.hpp>
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

Mesh* Shape2DFactory::Line(const vec3 &point1,
                                             const vec3 &point2) {
    auto mesh = new Mesh();;
    mesh->mode_ = GL_LINES;
    mesh->positions_.push_back(point1);
    mesh->positions_.push_back(point2);
    return mesh;
}

Mesh* Shape2DFactory::Lines(const std::vector<vec3>& points)
{
    auto mesh = new Mesh();;
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

Mesh* Shape2DFactory::RectMesh(const vec3& offset, const vec2& size)
{
    auto mesh = new Mesh();
    mesh->positions_ = RectPoints(offset, size);
    mesh->texCoords_.push_back(vec2(0,0)); mesh->texCoords_.push_back(vec2(1,0));
    mesh->texCoords_.push_back(vec2(1,1)); mesh->texCoords_.push_back(vec2(0,1));
    return mesh;
}

Mesh* Shape2DFactory::LineRect(const vec3& offset, const vec2& size)
{
    auto mesh = RectMesh(offset, size);
    mesh->mode_ = GL_LINE_LOOP;
    return mesh;
}

Mesh* Shape2DFactory::SolidRect(const vec3& offset, const vec2& size)
{
    auto mesh = RectMesh(offset, size);
    mesh->mode_ = GL_TRIANGLE_FAN;
    return mesh;
}

const std::vector<vec3>& Shape2DFactory::EllipsePoints(const vec3& offset, const vec2& size, unsigned int precision)
{
    points_.clear();
    
    float step = glm::pi<float>() * 2 / precision;
    for (int i = 0; i < precision; ++i) {
        float x = cos(i * step) * size.x + offset.x;
        float y = sin(i * step) * size.y + offset.y;
        points_.push_back(vec3(x, y, 0.0));
    }
    
    return points_;
}

Mesh* Shape2DFactory::LineEllipse(const vec3& offset, const vec2& size, unsigned int precision)
{
    auto mesh = new Mesh();
    mesh->positions_ = EllipsePoints(offset, size, precision);
    mesh->mode_ = GL_LINE_LOOP;
    return mesh;
}

Mesh* Shape2DFactory::SolidEllipse(const vec3& offset, const vec2& size, unsigned int precision)
{
    auto mesh = new Mesh();
    mesh->positions_ = EllipsePoints(offset, size, precision);
    mesh->positions_.insert(mesh->positions_.end(), *mesh->positions_.begin());
    mesh->positions_.insert(mesh->positions_.begin(), offset);
    mesh->mode_ = GL_TRIANGLE_FAN;
    return mesh;
}

Mesh* Shape2DFactory::LinePolygon(const std::vector<vec3>& points)
{
    auto mesh = new Mesh();
    mesh->positions_ = points;
    mesh->mode_ = GL_LINE_LOOP;
    return mesh;
}

Mesh* Shape2DFactory::SolidPolygon(const std::vector<vec3>& points)
{
    auto mesh = new Mesh();
    mesh->positions_ = points;
    mesh->mode_ = GL_TRIANGLE_FAN;
    return mesh;
}
