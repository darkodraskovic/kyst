#include <iostream>
#include <algorithm>
#include <glm/gtc/random.hpp>
#include "VecConsts.h"
#include "Maze.h"

using namespace VecConsts;

Maze::Maze(int width, int height)
{
    for (int i = 0; i < height; i++) {
        maze.push_back(vector<Cell*>());
        for (int j = 0; j < width; j++) {
            Cell* cell = new Cell;
            float x = float(j);
            float y = float(i);
            vec3* sw = new vec3(x ,y, 0);
            vec3* se = new vec3(x+1 ,y, 0);
            vec3* ne = new vec3(x+1 ,y+1, 0);
            vec3* nw = new vec3(x ,y+1, 0);
            cell->south = new wall(*sw, *se);
            cell->east = new wall(*se, *ne);
            cell->north = new wall(*ne, *nw);
            cell->west = new wall(*nw, *sw);
            maze[i].push_back(cell);
        }
    }
}

vector<vec3>& Maze::GetVertexArray()
{
    vector<vec3>* vertexArray = new vector<vec3>;
    for (int i = 0; i < maze.size(); i++) {
        for (int j = 0; j < maze[i].size() ; j++) {
            auto cell = maze[i][j];
            if (cell->south) {
                vertexArray->push_back(cell->south->first);
                vertexArray->push_back(cell->south->second);
            }
            if (cell->east) {
                vertexArray->push_back(cell->east->first);
                vertexArray->push_back(cell->east->second);
            }
            if (cell->north) {
                vertexArray->push_back(cell->north->first);
                vertexArray->push_back(cell->north->second);
            }
            if (cell->west) {
                vertexArray->push_back(cell->west->first);
                vertexArray->push_back(cell->west->second);
            }
        }
    }

    return *vertexArray;
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
    srand(time(NULL));
    
    int h = maze.size();
    int w = maze[0].size();
    int y = linearRand(0, h-1);
    int x = linearRand(0, w-1);

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
        
        int deltaX = x - prevX;
        int deltaY = y - prevY;
        Cell* prevCell = maze[prevY][prevX];
        Cell* nextCell = maze[y][x];
        if (deltaX != 0) {
            if (deltaX > 0) {
                prevCell->east = 0; 
                nextCell->west = 0;
            } else {
                prevCell->west = 0;
                nextCell->east = 0;
            }
        }
        else {
            if (deltaY > 0) {
                prevCell->north = 0;
                nextCell->south = 0;
            } else {
                prevCell->south = 0;
                nextCell->north = 0;
            }            
        }
    }
}
