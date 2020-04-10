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
    void GenArrayBuffer(float vertices[], int elemPerAttr, int numAttrs, int numVerts);

    // separate VBOs
    void GenArrayBuffer(float attribArray[], int elemPerAttr, int numVerts);
    void GenArrayBuffer(const std::vector<vec3>&);

    // indices - EBO
    void GenElementBuffer(unsigned int indices[], int numIdx);

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
