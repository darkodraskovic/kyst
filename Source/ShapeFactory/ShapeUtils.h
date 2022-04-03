#ifndef SHAPE_UTILS_H
#define SHAPE_UTILS_H

#include <glm/fwd.hpp>
#include <glm/glm.hpp>
#include <string>
#include <vector>

using namespace glm;

namespace ShapeFactory {

class ShapeUtils {
 public:
  ShapeUtils();

  static void ProdPoint(vec3& point, float min, float max);
  static vec3 Hex2rgb(std::string hex);
};

}  // namespace ShapeFactory
#endif
