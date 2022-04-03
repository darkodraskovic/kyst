#ifndef MAZE_FACTORY_H
#define MAZE_FACTORY_H

#include <glm/glm.hpp>
#include <utility>
#include <vector>

using namespace std;
using namespace glm;

namespace ShapeFactory {

typedef pair<vec3, vec3> wall;

class MazeFactory {
 public:
  MazeFactory(int width, int height);
  const vector<vec3>& GetVertexArray();
  void RandomWalk();

  vector<vector<wall>> wallsHor_;
  vector<vector<wall>> wallsVer_;

 private:
  static int seed_;
  vector<vec3> points_;
};

}  // namespace ShapeFactory
#endif /* MAZE_FACTORY_H */
