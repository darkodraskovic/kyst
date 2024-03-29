#ifndef KOCH_FACTORY_H
#define KOCH_FACTORY_H

#include <glm/glm.hpp>
#include <vector>

using namespace glm;

namespace ShapeFactory {

class KochFactory {
 public:
  KochFactory();

  static const std::vector<glm::vec3>& Snowflake(int numDivisions);
  static const std::vector<glm::vec3>& SnowflakeCurve(vec3& a, vec3& b,
                                                      int numDivisions);

 private:
  static void Divide(const vec3& a, const vec3& b, int numDivisions);
  static std::vector<vec3> points_;

  static glm::mat4 id_;
};

}  // namespace ShapeFactory
#endif /* KOCH_FACTORY_H */
