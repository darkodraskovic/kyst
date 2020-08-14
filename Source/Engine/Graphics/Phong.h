#ifndef PHONG_H
#define PHONG_H

#include "Material.h"
#include "VecConsts.h"

using namespace glm;
using namespace VecConsts;

class Phong : public Material
{
public:
    Phong(std::shared_ptr<Shader> shader);
    virtual void Update(const glm::mat4& model, const glm::mat4& view, const glm::mat4& projection) override;

    vec3 lightAmbient_ = GRAY;
    vec3 lightDiffuse_ = GRAY;
    vec3 lightSpecular_ = GRAY;
    vec3 lightPosition_ = ZERO;

    float shininess_;
};

#endif
