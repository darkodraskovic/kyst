#ifndef MATERIAL2D_H
#define MATERIAL2D_H

#include "Material.h"

using namespace glm;

class Material2D : public Material
{
public:
    Material2D();
    Material2D(const std::string& fragmentPath);
    Material2D(std::shared_ptr<Shader> shader);
    virtual void Update(const mat4& model, const mat4& view, const mat4& projection) override;

    float pctColor_ = .0f;
    float pctTexture_ = .0f;
    unsigned int texture_ = 0;

private:
    static const std::string vertexPath_;
    static const std::string fragmentPath_;
};

#endif
