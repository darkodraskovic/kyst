#ifndef SIERPINSKI_FACTORY_H
#define SIERPINSKI_FACTORY_H

#include <glm/glm.hpp>
#include <vector>

using namespace glm;

namespace ShapeFactory {

class SierpinskiFactory {
 public:
  SierpinskiFactory();

  static const std::vector<vec3>& Sierpinski2DDet(int numDivisions);
  static const std::vector<vec3>& Sierpinski2DRnd(int numDivisions);

  static const std::vector<vec3>& Sierpinski3DDet(int numDivisions);
  static const std::vector<vec3>& Sierpinski3DRnd(int numDivisions);

  static vec2 varRange_;

 private:
  static void Divide(const vec3& a, const vec3& b, const vec3& c,
                     int numDivisions);
  static void Divide(const vec3& a, const vec3& b, const vec3& c, const vec3& d,
                     int numDivisions);
  static std::vector<vec3> points_;
};

}  // namespace ShapeFactory
#endif
