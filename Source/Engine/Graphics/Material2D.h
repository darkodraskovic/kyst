#ifndef MATERIAL2D_H
#define MATERIAL2D_H

#include <glm/fwd.hpp>
#include "Material.h"
#include "VecConsts.h"

using namespace glm;

class Material2D : public Material
{
public:
    Material2D();
    Material2D(std::shared_ptr<Shader> shader);
    virtual void Update(float deltaTime, const glm::mat4& model, const glm::mat4& view, const glm::mat4& projection) override;

    float pctColor_ = .0f;
    float pctTexture_ = .0f;
    unsigned int texture_ = 0;
};

#endif
