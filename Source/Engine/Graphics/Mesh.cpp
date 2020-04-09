#include "Mesh.h"

Mesh::Mesh()
{
    glGenVertexArrays(1, &VAO_);
}

// VBO interleaved

void Mesh::GenArrayBuffer(float vertices[], int elemPerAttr, int numAttrs, int numVerts)
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
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);

    // Define data
    GLsizei stride = attrSize * numAttrs; 
    for (int i = 0; i < numAttrs; ++i) {
        void* offset = (void*)(i*attrSize);
        glVertexAttribPointer(i, elemPerAttr, GL_FLOAT, GL_FALSE, stride, offset);
        glEnableVertexAttribArray(i);
    }

    glBindVertexArray(0);
}

// VBOs separate

void Mesh::GenArrayBuffer(float attribArray[], int elemPerAttr, int numVerts)
{
    numVerts_ = numVerts;
    
    glBindVertexArray(VAO_);
    
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    VBOs_.push_back(VBO);
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    size_t size = sizeof(float) * elemPerAttr * numVerts;
    glBufferData(GL_ARRAY_BUFFER, size, attribArray, GL_STATIC_DRAW);
    int idx = VBOs_.size()-1;
    glVertexAttribPointer(idx, elemPerAttr, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(idx);

    glBindVertexArray(0);
}

// EBO

void Mesh::GenElementBuffer(unsigned int indices[], int numIdx)
{
    numIdx_ = numIdx;
    
    glBindVertexArray(VAO_);
    
    glGenBuffers(1, &EBO_);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_);
    int size = sizeof(unsigned int) * numIdx_;
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);

    glBindVertexArray(0);
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
