#include <vector>

#include "CubeFactory.h"


CubeFactory::CubeFactory()
{
}

std::vector<vec3> CubeFactory::GetPositions() {
    std::vector<vec3> attribs = {// top
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
        
    return attribs;
}

std::vector<vec3> CubeFactory::GetNormals() {
    std::vector<vec3> attribs = {
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
        
    return attribs;
}

std::vector<vec3> CubeFactory::GetTexCoords() {
    std::vector<vec3> attribs = {
        // top
        ZERO, RIGHT, ONE, UP,
        // back
        ZERO, RIGHT, ONE, UP,
        // left
        ZERO, RIGHT, ONE, UP,
        // right
        ZERO, RIGHT, ONE, UP,
        // top
        ZERO, RIGHT, ONE, UP,
        // bottom
        ZERO, RIGHT, ONE, UP,
    };
        
    return attribs;
}

std::vector<unsigned int> CubeFactory::GetIndices() {
    std::vector<unsigned int> indices = {
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
        
    return indices;
}
