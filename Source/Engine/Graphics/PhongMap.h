#ifndef PHONG_MAP_H
#define PHONG_MAP_H

#include "Phong.h"

class PhongMap : public Phong
{
public:
    PhongMap(std::shared_ptr<Shader> shader);
    
    virtual void Update(float deltaTime, const glm::mat4& model, const glm::mat4& view, const glm::mat4& projection) override;

    unsigned int diffuse_;
    unsigned int specular_;
    unsigned int emissive_;
};

#endif
