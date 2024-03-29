#include "KochFactory.h"

#include <glm/gtc/constants.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Engine/VecConsts.h"

using namespace Kyst;
using namespace VecConsts;
using namespace ShapeFactory;

std::vector<vec3> KochFactory::points_;
glm::mat4 KochFactory::id_ = glm::mat4(1.0f);

KochFactory::KochFactory() {}

const std::vector<vec3>& KochFactory::Snowflake(int numDivisions) {
  points_.clear();

  float side = sqrt(3);
  vec3 a(-1, side / 3, 0);
  vec3 b(1, side / 3, 0);
  vec3 c(0, -2 * (side / 3), 0);

  Divide(a, b, numDivisions);
  Divide(b, c, numDivisions);
  Divide(c, a, numDivisions);

  return points_;
}

const std::vector<vec3>& KochFactory::SnowflakeCurve(vec3& a, vec3& b, int numDivisions) {
  points_.clear();

  Divide(a, b, numDivisions);
  return points_;
}

void KochFactory::Divide(const vec3& a, const vec3& b, int numDivisions) {
  vec3 delta = b - a;
  vec3 c = delta * (1.0f / 3) + a;
  vec3 d = delta * (2.0f / 3) + a;
  vec4 e4 = glm::rotate(id_, glm::pi<float>() / 3, FORWARD) * vec4(d - c, 1.0);
  vec3 e = vec3(e4.x, e4.y, e4.z) + c;

  numDivisions--;
  if (numDivisions < 1) {
    points_.push_back(a);
    points_.push_back(c);
    points_.push_back(e);
    points_.push_back(d);
    points_.push_back(b);
    return;
  }

  Divide(a, c, numDivisions);
  Divide(c, e, numDivisions);
  Divide(e, d, numDivisions);
  Divide(d, b, numDivisions);
}
