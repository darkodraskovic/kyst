#ifndef CUBE_FACTORY_H
#define CUBE_FACTORY_H

#include <memory>
#include <vector>
#include <glm/glm.hpp>

#include "Engine/VecConsts.h"
#include "Engine/Graphics/Mesh.h"

using namespace glm;
using namespace VecConsts;

namespace CubeVecs {
    const vec3 frontBL(-0.5f, -0.5f, 0.5f);
    const vec3 frontTL(-0.5f, 0.5f, 0.5f);
    const vec3 frontTR(0.5f, 0.5f, 0.5f);
    const vec3 frontBR(0.5f, -0.5f, 0.5f);
    const vec3 backBL(frontBL + BACK);
    const vec3 backTL(frontTL + BACK);
    const vec3 backTR(frontTR + BACK);
    const vec3 backBR(frontBR + BACK);
}  // CubeVecs

using namespace CubeVecs;

class CubeFactory
{
public:
    CubeFactory();

    static std::vector<vec3>  GetPositions();
    static std::vector<vec3> GetNormals();
    static std::vector<vec3> GetTexCoords();
    static std::vector<unsigned int> GetIndices();

    static std::shared_ptr<Mesh> GetMesh();
};

#endif
