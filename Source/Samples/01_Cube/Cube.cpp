#include <glm/gtc/constants.hpp>
#include "Cube.h"
#include "VecConsts.h"
#include "CubeFactory.h"

using namespace glm;
using namespace VecConsts;
using namespace CubeVecs;

Cube::Cube(const std::shared_ptr<Material>& material)
{
    material_ = material;

    mesh_->GenArrayBuffer(CubeFactory::GetPositions());
    mesh_->GenArrayBuffer(CubeFactory::GetNormals());
    mesh_->GenArrayBuffer(CubeFactory::GetTexCoords());

    int elemPerAttr = 3;
    int numAttrs = 3;
    int numVerts = 24;    
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
    
    mesh_->GenElementBuffer(CubeFactory::GetIndices());
}

void Cube::Update(float deltaTime) {
    Rotate(deltaTime * glm::quarter_pi<float>(), ONE);
}
