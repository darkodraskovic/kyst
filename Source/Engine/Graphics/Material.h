#ifndef MATERIAL_H
#define MATERIAL_H

#include <glm/glm.hpp>
#include <memory>
#include <map>

#include "../Core.h"
#include "Shader.h"

using namespace glm;

enum Uniform { TIME, COLOR, ALPHA, MODEL, VIEW, PROJECTION };
extern const std::map<Uniform, std::string> UNIFORM_MAP;

class Material
{
public:
    Material();
    Material(std::shared_ptr<Shader> shader);
    Material(const char* vertexPath, const char* fragmentPath);
    
    virtual void Update(const mat4& model, const mat4& view, const mat4& projection);

    std::shared_ptr<Shader> shader_;
    vec3 color_ = vec3(1.0);
    float alpha_ = 1.0;
};

#endif
