#ifndef MESH_H
#define MESH_H

#include <glm/glm.hpp>
#include <string>
#include <vector>
#include <map>

#include "../Core.h"

using namespace glm;

enum MeshAttribute { POSITIONS, NORMALS, TANGENTS, TEX_COORDS, COLORS };

class Mesh
{
public:
    Mesh();
    ~Mesh();

    // interleaved VBO
    void GenArrayBuffer(const float* data, int elemPerAttr, int numAttrs, int numVerts);

    // separate VBOs
    void GenArrayBuffer(const float* data, int elemPerAttr, int numVerts, unsigned int idx);
    void GenArrayBuffer(const float* data, int elemPerAttr, int numVerts);
    void GenArrayBuffer(const float* data, int elemPerAttr, int numVerts, unsigned int program, const std::string& name);
    void GenArrayBuffer(const std::vector<vec2>&);
    void GenArrayBuffer(const std::vector<vec3>&);
    void GenArrayBuffer(const std::vector<vec2>&, unsigned int program, MeshAttribute attrib);
    void GenArrayBuffer(const std::vector<vec3>&, unsigned int program, MeshAttribute attrib);

    // indices - EBO
    void GenElementBuffer(const unsigned int* data, int numIdx);
    void GenElementBuffer(const std::vector<unsigned int>&);

    void Generate(unsigned int program);
    void Render();

    GLuint VAO_;
    std::vector<GLuint> VBOs_;    
    GLuint EBO_;

    GLenum mode_ = GL_TRIANGLES;
    std::vector<glm::vec3> positions_;
    std::vector<glm::vec3> normals_;
    std::vector<glm::vec3> tangents_;
    std::vector<glm::vec3> colors_;
    std::vector<glm::vec2> texCoords_;
    std::vector<unsigned int> indices_;
    
private:
    void DeleteBuffers();
    
    int numVerts_ = 0;
    int numIdx_ = 0;
};

#endif
