#include <memory>
#include <vector>

#include "CubeFactory.h"

using namespace ShapeFactory;

CubeFactory::CubeFactory() {}

std::vector<vec3> CubeFactory::GetPositions()
{
    return std::vector<vec3>{// top
        frontBL, frontBR, frontTR, frontTL,
        // back
        backBR, backBL, backTL, backTR,
        // left
        backBL, frontBL, frontTL, backTL,
        // right
        frontBR, backBR, backTR, frontTR,
        // top
        frontTL, frontTR, backTR, backTL,
        // bottom
        backBL, backBR, frontBR, frontBL,
    };
}

std::vector<vec3> CubeFactory::GetNormals()
{
    return std::vector<vec3>{
        // top
        FORWARD, FORWARD, FORWARD, FORWARD,
        // back
        BACK, BACK, BACK, BACK,
        // left
        LEFT, LEFT, LEFT, LEFT,
        // right
        RIGHT, RIGHT, RIGHT, RIGHT,
        // top
        UP, UP, UP, UP,
        // bottom
        DOWN, DOWN, DOWN, DOWN,
    };
}

std::vector<vec2> CubeFactory::GetTexCoords() {
    return std::vector<vec2>{
        // top
        ZERO_2D, RIGHT_2D, ONE_2D, UP_2D,
        // back
        ZERO_2D, RIGHT_2D, ONE_2D, UP_2D,
        // left
        ZERO_2D, RIGHT_2D, ONE_2D, UP_2D,
        // right
        ZERO_2D, RIGHT_2D, ONE_2D, UP_2D,
        // top
        ZERO_2D, RIGHT_2D, ONE_2D, UP_2D,
        // bottom
        ZERO_2D, RIGHT_2D, ONE_2D, UP_2D,
    };
}

std::vector<unsigned int> CubeFactory::GetIndices() {
    return std::vector<unsigned int>{
        // top
        0, 1, 2, 0, 2, 3,
        // back
        4, 5, 6, 4, 6, 7,
        // left
        8, 9, 10, 8, 10, 11,
        // right
        12, 13, 14, 12, 14, 15,
        // top
        16, 17, 18, 16, 18, 19,
        // bottom
        20, 21, 22, 20, 22, 23,
    };
}

std::shared_ptr<Mesh> CubeFactory::GetMesh()
{
    auto mesh = std::make_shared<Mesh>();
    mesh->positions_ = CubeFactory::GetPositions();
    mesh->normals_ = CubeFactory::GetNormals();
    mesh->texCoords_ = CubeFactory::GetTexCoords();
    mesh->indices_ = CubeFactory::GetIndices();
    
    return mesh;
}
