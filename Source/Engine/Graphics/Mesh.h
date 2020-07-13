#ifndef MESH_H
#define MESH_H

#include <vector>
#include "Material.h"

class Mesh
{
public:
    Mesh();
    ~Mesh();

    // interleaved VBO
    void GenArrayBuffer(const float* data, int elemPerAttr, int numAttrs, int numVerts);

    // separate VBOs
    void GenArrayBuffer(const float* data, int elemPerAttr, int numVerts);
    void GenArrayBuffer(const std::vector<vec2>&);
    void GenArrayBuffer(const std::vector<vec3>&);

    // indices - EBO
    void GenElementBuffer(const unsigned int* data, int numIdx);
    void GenElementBuffer(const std::vector<unsigned int>&);

    void Render();

    GLuint VAO_;
    std::vector<GLuint> VBOs_;    
    GLuint EBO_;

    GLenum mode_ = GL_TRIANGLES;
    
private:
    int numVerts_ = 0;
    int numIdx_ = 0;
};

#endif
