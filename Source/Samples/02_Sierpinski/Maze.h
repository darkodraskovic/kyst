#ifndef MAZE_FACTORY_H
#define MAZE_FACTORY_H

#include <utility>
#include <vector>
#include <glm/glm.hpp>

using namespace std;
using namespace glm;

typedef pair<const vec3&, const vec3&> wall;

typedef struct Cell {
    wall* south = 0;
    wall* east = 0;
    wall* north = 0;
    wall* west = 0;
} Cell;

class Maze
{
public:
    Maze(int width, int height);
    vector<vec3>& GetVertexArray();
    void RandomWalk();
    
    vector<vector<Cell*>> maze;
};


#endif /* MAZE_FACTORY_H */
