#ifndef MESH_H
#define MESH_H

#include <glm/fwd.hpp>
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

    void Generate();
    void Render();

    GLuint VAO_;
    std::vector<GLuint> VBOs_;    
    GLuint EBO_;

    GLenum mode_ = GL_TRIANGLES;
    std::vector<glm::vec3> positions_;
    std::vector<glm::vec3> normals_;
    std::vector<glm::vec3> colors_;
    std::vector<glm::vec2> texCoords_;
    std::vector<unsigned int> indices_;
    
private:
    int numVerts_ = 0;
    int numIdx_ = 0;
};

#endif
