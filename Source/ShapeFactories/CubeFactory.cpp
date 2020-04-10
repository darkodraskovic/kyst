#include <vector>

#include "CubeFactory.h"


CubeFactory::CubeFactory()
{
}

float* CubeFactory::GetPositions() {
    vec3* positions = new vec3[numVerts_] {// top
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
        
    return (float*)positions;
}

float* CubeFactory::GetNormals() {
    vec3* normals = new vec3[numVerts_] {
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
        
    return (float*)normals;
}

float* CubeFactory::GetTexCoords() {
    vec3* texCoords = new vec3[numVerts_] {
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
                                      ZERO, RIGHT, ONE,UP,
                                      };
        
    return (float*)texCoords;
}

