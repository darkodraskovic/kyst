#include "Cube.h"
#include "VecConsts.h"
#include "CubeFactory.h"

using namespace glm;
using namespace VecConsts;
using namespace CubeVecs;

Cube::Cube(const std::shared_ptr<Material>& material)
{
    material_ = material;

    // vec3 frontBL(-0.5f, -0.5f, 0.5f);
    // vec3 frontTL(-0.5f, 0.5f, 0.5f);
    // vec3 frontTR(0.5f, 0.5f, 0.5f);
    // vec3 frontBR(0.5f, -0.5f, 0.5f);
    // vec3 backBL = frontBL + BACK;
    // vec3 backTL = frontTL + BACK;
    // vec3 backTR = frontTR + BACK;
    // vec3 backBR = frontBR + BACK;

    int elemPerAttr = 3;
    int numVerts = 24;

    float* positions = CubeFactory::GetPositions();
    float* normals = CubeFactory::GetNormals();
    float* texCoords = CubeFactory::GetTexCoords();
    mesh_->GenArrayBuffer(positions, elemPerAttr, numVerts);
    mesh_->GenArrayBuffer(normals, elemPerAttr, numVerts);
    mesh_->GenArrayBuffer(texCoords, elemPerAttr, numVerts);

    int numAttrs = 3;
    vec3 vertices[] = {
        // top
        frontBL, FORWARD, ZERO,
        frontBR, FORWARD, RIGHT,
        frontTR, FORWARD, ONE,
        frontTL, FORWARD, UP,
        // back
        backBR, BACK, ZERO, 
        backBL, BACK, RIGHT,
        backTL, BACK, ONE,  
        backTR, BACK, UP,   
        // left
        backBL, LEFT,   ZERO, 
        frontBL, LEFT,  RIGHT,
        frontTL, LEFT,  ONE,  
        backTL, LEFT,   UP,   
        // right
        frontBR, RIGHT, ZERO, 
        backBR, RIGHT,  RIGHT,
        backTR, RIGHT,  ONE,  
        frontTR, RIGHT, UP, 
        // top
        frontTL, UP, ZERO, 
        frontTR, UP, RIGHT,
        backTR, UP,  ONE,  
        backTL, UP,  UP,           
        // bottom
        backBL, DOWN,   ZERO, 
        backBR, DOWN,   RIGHT,
        frontBR, DOWN,  ONE,  
        frontBL, DOWN,  UP,   
    };
    // mesh_->GenArrayBuffer((float*)vertices, elemPerAttr, numAttrs, numVerts);
    
    int numIdx = 6 * 2 * 3; // num sides x num tris per side x num verts per tri
    unsigned int indices[] = {
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
    mesh_->GenElementBuffer(indices, numIdx);
}

void Cube::Update(float deltaTime) {
    Rotate(deltaTime*50, ONE);
}
