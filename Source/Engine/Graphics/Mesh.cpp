#include <iostream>
#include "Mesh.h"

Mesh::Mesh()
{
    glGenVertexArrays(1, &VAO_);
}

const std::map<MeshAttribute, std::string> ATTRIBUTE_MAP
{
    {POSITIONS, "aPos"},
    {NORMALS, "aNorm"},
    {TANGENTS, "aTang"},
    {TEX_COORDS, "aTexCoord"},
    {COLORS, "aCol"},
};

// VBO interleaved

void Mesh::GenArrayBuffer(const float* data, int elemPerAttr, int numAttrs, int numVerts)
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

void Mesh::GenArrayBuffer(const float* data, int elemPerAttr, int numVerts, unsigned int program, const std::string& name)
{
    GenArrayBuffer(data, elemPerAttr, numVerts, (unsigned int)glGetAttribLocation(program, name.c_str()));
}

void Mesh::GenArrayBuffer(const std::vector<vec2>& attribs)
{
    GenArrayBuffer(&attribs[0].x, 2, attribs.size());
}

void Mesh::GenArrayBuffer(const std::vector<vec3>& attribs)
{
    GenArrayBuffer(&attribs[0].x, 3, attribs.size());
}

void Mesh::GenArrayBuffer(const std::vector<vec2>& attribs, unsigned int program, MeshAttribute attrib)
{
    GenArrayBuffer(&attribs[0].x, 2, attribs.size(), program, ATTRIBUTE_MAP.at(attrib));
}

void Mesh::GenArrayBuffer(const std::vector<vec3>& attribs, unsigned int program, MeshAttribute attrib)
{
    GenArrayBuffer(&attribs[0].x, 3, attribs.size(), program, ATTRIBUTE_MAP.at(attrib));
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

// Attribute order in attributes argument must match (location = n) in shader
void Mesh::Generate(const std::vector<MeshAttribute>& attribOrder)
{
    DeleteBuffers();
    
    for (int i = 0; i < attribOrder.size(); ++i)
    {
        switch (attribOrder[i]) {
        case POSITIONS:
            GenArrayBuffer(positions_);
            break;
        case NORMALS:
            GenArrayBuffer(normals_);
            break;
        case TANGENTS:
            GenArrayBuffer(tangents_);
            break;
        case TEX_COORDS:
            GenArrayBuffer(texCoords_);
            break;
        case COLORS:
            GenArrayBuffer(colors_);
            break;
        default:
            std::cout << "ERROR::MESH:: Unknown mesh attribute!" << std::endl;
            break;
        }
    }
}

void Mesh::Generate(unsigned int program)
{
    DeleteBuffers();
    
    GenArrayBuffer(positions_, program, POSITIONS);
    
    if (!normals_.empty()) GenArrayBuffer(normals_, program, NORMALS);
    if (!normals_.empty()) GenArrayBuffer(tangents_, program, TANGENTS);
    
    if (!texCoords_.empty()) GenArrayBuffer(texCoords_, program, TEX_COORDS);
    if (!colors_.empty()) GenArrayBuffer(colors_, program, COLORS);
    
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

void Mesh::DeleteBuffers()
{
    glDeleteBuffers(1, &EBO_);
    glDeleteBuffers(VBOs_.size(), &VBOs_.front()); 
}

// DESTRUCTOR

Mesh::~Mesh()
{
    DeleteBuffers();
    glDeleteVertexArrays(1, &VAO_);
};
