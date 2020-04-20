#include <iostream>
#include <algorithm>
#include <glm/gtc/random.hpp>
#include "VecConsts.h"
#include "Maze.h"

using namespace VecConsts;

int Maze::seed_ = 0;

Maze::Maze(int width, int height) : width_(width), height_(height)
{
    for (int i = 0; i < height; i++) {
        wallsHor_.push_back(vector<wall>());
        wallsVer_.push_back(vector<wall>());
        for (int j = 0; j < width; j++) {
            float x = float(j);
            float y = float(i);
            wall hor(vec3(x, y, 0), vec3(x+1, y, 0));
            wall ver(vec3(x, y+1, 0), vec3(x, y, 0));
            wallsHor_[i].push_back(hor);
            wallsVer_[i].push_back(ver);
        }
    }

    wallsHor_.push_back(vector<wall>());
    for (int j = 0; j < width; j++) {
        wallsHor_[height].push_back(wall(vec3(j, height, 0), vec3(j+1, height, 0)));
    }

    for (int i = 0; i < height; i++) {
        wallsVer_[i].push_back(wall(vec3(width, i, 0), vec3(width, i + 1, 0)));
    }
}

vector<vec3>* Maze::GetVertexArray()
{
    vector<vec3>* vertexArray = new vector<vec3>;
    for (vector<wall> column : wallsHor_) {
        for (wall w : column) {
            if (w.first.x > -1) {
                vertexArray->push_back(w.first);
                vertexArray->push_back(w.second);
                
            }
        }
    }
    for (vector<wall> col : wallsVer_) {
        for (wall w : col) {
            if (w.first.x > -1) {
                vertexArray->push_back(w.first);
                vertexArray->push_back(w.second);
            }
        }
    }
    
    return vertexArray;
}

struct compareIVec2
{
    const ivec2& key;
    compareIVec2(const ivec2& iv): key(iv) { }

    bool operator() (const ivec2& iv) {
        return iv.x == key.x && iv.y == key.y;
    }
};

void Maze::RandomWalk()
{
    srand(time(NULL) + Maze::seed_++);
    
    int x = linearRand(0, width_-1);
    int y = linearRand(0, height_-1);

    vector<ivec2> visited; // visited cells
    visited.push_back(ivec2(x,y));

    while (visited.size() < width_ * height_) {
        int prevX = x;
        int prevY = y;

        // random walk
        if (linearRand(0,1) == 0) {
            if(linearRand(0,1) == 0) x++; else x--;
            if (x < 0 || x > width_-1) x = prevX; // either clamp or wrap x
        } else {
            if(linearRand(0,1) == 0) y++; else y--;
            if (y < 0 || y > height_-1) y = prevY;
        }

        // if cell is visited, continue
        if (find_if(visited.begin(), visited.end(), compareIVec2(ivec2(x,y))) != visited.end()) continue;
        
        visited.push_back(ivec2(x,y));
        
        if (x - prevX != 0) {
            wallsVer_[y][x > prevX ? x : prevX].first.x = -1;
        } else {
            wallsHor_[y > prevY ? y : prevY][x].first.x = -1;
        }
    }
}
