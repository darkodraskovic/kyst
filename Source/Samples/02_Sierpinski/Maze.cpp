#include <iostream>
#include <algorithm>
#include <glm/gtc/random.hpp>
#include "VecConsts.h"
#include "Maze.h"

using namespace VecConsts;

int Maze::seed_ = 0;

Maze::Maze(int width, int height)
{
    wallsHor_ = vector<vector<wall>> (height+1);
    wallsVer_ = vector<vector<wall>> (height);
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            float x = float(j);
            float y = float(i);
            wall hor(vec3(x, y, 0), vec3(x+1, y, 0));
            wall ver(vec3(x, y+1, 0), vec3(x, y, 0));
            wallsHor_[i].push_back(hor);
            wallsVer_[i].push_back(ver);
        }
    }

    for (int j = 0; j < width; j++) {
        wallsHor_[height].push_back(wall(vec3(j, height, 0), vec3(j+1, height, 0)));
    }

    for (int i = 0; i < height; i++) {
        wallsVer_[i].push_back(wall(vec3(width, i, 0), vec3(width, i + 1, 0)));
    }
}

const vector<vec3>& Maze::GetVertexArray()
{
    for (vector<wall> column : wallsHor_) {
        for (wall w : column) {
            if (w.first.x > -1) {
                points_.push_back(w.first);
                points_.push_back(w.second);
            }
        }
    }
    for (vector<wall> col : wallsVer_) {
        for (wall w : col) {
            if (w.first.x > -1) {
                points_.push_back(w.first);
                points_.push_back(w.second);
            }
        }
    }
    
    return points_;
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

    int w = wallsHor_[0].size(), h = wallsVer_.size();
    int x = linearRand(0, w-1), y = linearRand(0, h-1);

    vector<ivec2> visited; // visited cells
    visited.push_back(ivec2(x,y));

    while (visited.size() < w * h) {
        int prevX = x;
        int prevY = y;

        // random walk
        if (linearRand(0,1) == 0) {
            if(linearRand(0,1) == 0) x++; else x--;
            if (x < 0 || x > w-1) x = prevX; // either clamp or wrap x
        } else {
            if(linearRand(0,1) == 0) y++; else y--;
            if (y < 0 || y > h-1) y = prevY;
        }

        // if cell is visited, continue
        if (find_if(visited.begin(), visited.end(), compareIVec2(ivec2(x,y))) != visited.end()) continue;
        visited.push_back(ivec2(x,y));
        
        if (x - prevX != 0) { // remove walls
            wallsVer_[y][x > prevX ? x : prevX].first.x = -1;
        } else {
            wallsHor_[y > prevY ? y : prevY][x].first.x = -1;
        }
    }
}
