#include "Mesh.h"
#include "Shader.h"

Mesh::Mesh()
{
    glGenVertexArrays(1, &VAO_);
}

// VBO interleaved

void Mesh::GenArrayBuffer(const float* data, int elemPerAttr, int numAttrs,
                          int numVerts)
{
    numVerts_ = numVerts;

    glBindVertexArray(VAO_);

    unsigned int VBO;
    glGenBuffers(1, &VBO);
    VBOs_.push_back(VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // Buffer data
    size_t attrSize = elemPerAttr * sizeof(float);
    int size = attrSize * numAttrs * numVerts;
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);

    // Define data
    GLsizei stride = attrSize * numAttrs;
    for (int i = 0; i < numAttrs; ++i) {
        glEnableVertexAttribArray(i);
        void *offset = (void *)(i * attrSize);
        glVertexAttribPointer(i, elemPerAttr, GL_FLOAT, GL_FALSE, stride, offset);
    }

    glBindVertexArray(0);
}

// VBOs separate

void Mesh::GenArrayBuffer(const float *data, int elemPerAttr, int numVerts, unsigned int idx)
{
    numVerts_ = numVerts;

    glBindVertexArray(VAO_);

    unsigned int VBO;
    glGenBuffers(1, &VBO);
    VBOs_.push_back(VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    size_t size = sizeof(float) * elemPerAttr * numVerts;
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
    glEnableVertexAttribArray(idx);
    glVertexAttribPointer(idx, elemPerAttr, GL_FLOAT, GL_FALSE, 0, 0);

    glBindVertexArray(0);
}

void Mesh::GenArrayBuffer(const float *data, int elemPerAttr, int numVerts)
{
    GenArrayBuffer(data, elemPerAttr, numVerts, (unsigned int)VBOs_.size());
}

void Mesh::GenArrayBuffer(const float* data, int elemPerAttr, int numVerts, unsigned int program, const char* name)
{
    GenArrayBuffer(data, elemPerAttr, numVerts, (unsigned int)glGetAttribLocation(program, name));
}

void Mesh::GenArrayBuffer(const std::vector<vec2>& attribs)
{
    GenArrayBuffer(&attribs[0].x, 2, attribs.size());
}

void Mesh::GenArrayBuffer(const std::vector<vec3>& attribs)
{
    GenArrayBuffer(&attribs[0].x, 3, attribs.size());
}

void Mesh::GenArrayBuffer(const std::vector<vec2>& attribs, unsigned int program, const char* name)
{
    GenArrayBuffer(&attribs[0].x, 2, attribs.size(), program, name);
}

void Mesh::GenArrayBuffer(const std::vector<vec3>& attribs, unsigned int program, const char* name)
{
    GenArrayBuffer(&attribs[0].x, 3, attribs.size(), program, name);
}

// EBO

void Mesh::GenElementBuffer(const unsigned int *data, int numIdx) {
    numIdx_ = numIdx;

    glBindVertexArray(VAO_);

    glGenBuffers(1, &EBO_);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_);
    int size = sizeof(unsigned int) * numIdx_;
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);

    glBindVertexArray(0);
}

void Mesh::GenElementBuffer(const std::vector<unsigned int>& indices)
{
    GenElementBuffer(&indices[0], indices.size());
}

// GENERATE

/*
  layout (location = 0) in vec3 aPos;
  layout (location = 1) in vec3 aNorm;
  layout (location = 2) in vec3 aTang;
  layout (location = 3) in vec2 aTexCoord;
  layout (location = 4) in vec3 aCol;
*/

void Mesh::Generate()
{
    glDeleteBuffers(1, &EBO_);
    glDeleteBuffers(VBOs_.size(), &VBOs_.front());
    
    if (positions_.empty()) {
        std::cout << "ERROR: Mesh position array empty" << std::endl;
        return;
    }
    GenArrayBuffer(positions_);
    
    if (!normals_.empty()) GenArrayBuffer(normals_);
    if (!normals_.empty()) GenArrayBuffer(tangents_);
    
    if (!texCoords_.empty()) GenArrayBuffer(texCoords_);
    if (!colors_.empty()) GenArrayBuffer(colors_);
    
    if (!indices_.empty()) GenElementBuffer(indices_);
}

void Mesh::Generate(unsigned int program)
{
    glDeleteBuffers(1, &EBO_);
    glDeleteBuffers(VBOs_.size(), &VBOs_.front());
    
    if (positions_.empty()) {
        std::cout << "ERROR: Mesh position array empty" << std::endl;
        return;
    }
    GenArrayBuffer(positions_, program, "aPos");
    
    if (!normals_.empty()) GenArrayBuffer(normals_, program, "aNorm");
    if (!normals_.empty()) GenArrayBuffer(tangents_, program, "aTang");
    
    if (!texCoords_.empty()) GenArrayBuffer(texCoords_, program, "aTexCoord");
    if (!colors_.empty()) GenArrayBuffer(colors_, program, "aCol");
    
    if (!indices_.empty()) GenElementBuffer(indices_);
}

// RENDER

void Mesh::Render()
{
    glBindVertexArray(VAO_);
    
    if (numIdx_) {
        glDrawElements(mode_, numIdx_, GL_UNSIGNED_INT, 0);
    } else {
        glDrawArrays(mode_, 0, numVerts_);
    }
    
    glBindVertexArray(0);
}

// DESTRUCTOR

Mesh::~Mesh()
{
    glDeleteBuffers(1, &EBO_);
    glDeleteBuffers(VBOs_.size(), &VBOs_.front());
    glDeleteVertexArrays(1, &VAO_);
};
