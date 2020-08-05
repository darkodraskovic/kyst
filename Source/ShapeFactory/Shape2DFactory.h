#ifndef SHAPE2D_FACTORY_H
#define SHAPE2D_FACTORY_H

#include "Mesh.h"
#include <glm/fwd.hpp>
#include <memory>
#pragma once

#include "Entity.h"

#include_next <vector>
#include_next <glm/glm.hpp>

using namespace glm;

class Shape2DFactory
{
public:
    Shape2DFactory();

    static std::shared_ptr<Mesh> Line(const vec3& point1, const vec3& point2);
    
    static const std::vector<vec3>& RectPoints(const vec3& offset, const vec2& size);
    static std::shared_ptr<Mesh> LineRect(const vec3& offset, const vec2& size);
    static std::shared_ptr<Mesh> SolidRect(const vec3& offset, const vec2& size);
    static std::shared_ptr<Mesh> LinePolygon(const vec3& offset, const std::vector<vec3>& points);
    static std::shared_ptr<Mesh> SolidPolygon(const vec3& offset, const std::vector<vec3>& points);

private:
    static std::shared_ptr<Mesh> RectMesh(const vec3& offset, const vec2& size);
    static std::vector<vec3> points_;
};

#endif
