#ifndef SHAPE2D_FACTORY_H
#define SHAPE2D_FACTORY_H

#include <glm/fwd.hpp>
#include <glm/glm.hpp>
#include <memory>
#include <vector>

#include "Engine/Graphics/Mesh.h"
#include "Engine/Scene/Entity.h"

using namespace Kyst;
using namespace glm;

namespace ShapeFactory {

class Shape2DFactory {
 public:
  Shape2DFactory();

  // Line
  static Mesh* Line(const vec3& point1, const vec3& point2);
  static Mesh* Lines(const std::vector<vec3>& points);

  // Rect
  static const std::vector<vec3>& RectPoints(const vec3& offset, const vec2& size);
  static Mesh* LineRect(const vec3& offset, const vec2& size);
  static Mesh* SolidRect(const vec3& offset, const vec2& size);

  // Ellipse
  static const std::vector<vec3>& EllipsePoints(const vec3& offset, const vec2& size, unsigned int precision);
  static Mesh* LineEllipse(const vec3& offset, const vec2& size, unsigned int precision = 36);
  static Mesh* SolidEllipse(const vec3& offset, const vec2& size, unsigned int precision = 36);

  // Polygon
  static Mesh* LinePolygon(const std::vector<vec3>& points);
  static Mesh* SolidPolygon(const std::vector<vec3>& points);

 private:
  static Mesh* RectMesh(const vec3& offset, const vec2& size);
  static std::vector<vec3> points_;
};

}  // namespace ShapeFactory
#endif
