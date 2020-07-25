#ifndef MAZE_GEN_H
#define MAZE_GEN_H

#pragma once

#include_next <glm/glm.hpp>
#include "Mover.h"

using namespace glm;

class MazeGen
{
public:
    MazeGen();
    std::shared_ptr<Mover> CreateMaze(int width, int height, const vec3& color);
};

#endif
