#ifndef MAZE_FACTORY_H
#define MAZE_FACTORY_H

#include <utility>
#include <vector>
#include <glm/glm.hpp>

using namespace std;
using namespace glm;

typedef pair<vec3, vec3> wall;

class Maze
{
public:
    Maze(int width, int height);
    vector<vec3>* GetVertexArray();
    void RandomWalk();
    
    vector<vector<wall>> wallsHor_;
    vector<vector<wall>> wallsVer_;

private:
    int width_;
    int height_;
    static int seed_;
};


#endif /* MAZE_FACTORY_H */
