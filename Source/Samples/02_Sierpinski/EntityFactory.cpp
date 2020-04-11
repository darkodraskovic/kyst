#include <glm/gtc/constants.hpp>

#include "SierpinskiFactory.h"
#include "EntityFactory.h"

EntityFactory::EntityFactory(Application* app) : app_(app)
{
    colShader_ = std::make_shared<Shader>("../Shaders/Col.vs", "../Shaders/Col.fs");
    vColShader_ = std::make_shared<Shader>("../Shaders/VCol.vs", "../Shaders/VCol.fs");
    colShader_->Use();
    colShader_->SetVec4("uColor", vec4(MAGENTA, 1.0));    
}

std::shared_ptr<Entity> EntityFactory::CreateEntity(bool vCol)
{
    auto entity = std::make_shared<Entity>();
    entity->material_ = std::make_shared<Material>();
    app_->entities_.push_back(entity);
    entity->material_->shader_ = colShader_;
    if (vCol) {
        entity->material_->shader_ = vColShader_;
    }
    return entity;
}

std::shared_ptr<Entity> EntityFactory::CreateLineGasket(int numDivisions, const vec2& varRange, bool threeD, bool vCol)
{
    auto entity = CreateEntity(vCol);
    
    SierpinskiFactory::varRange_ = varRange;
    auto points = threeD ? SierpinskiFactory::Sierpinski3DDet(numDivisions) :
        SierpinskiFactory::Sierpinski2DDet(numDivisions);
    std::vector<vec3> line;
    entity->mesh_->mode_ = GL_LINES;
    for (int i = 0; i < points.size(); i += 3)
    {
        line.push_back(points.at(i));
        line.push_back(points.at(i+1));
        line.push_back(points.at(i+1));
        line.push_back(points.at(i+2));
        line.push_back(points.at(i+2));
        line.push_back(points.at(i));
    }
    entity->mesh_->GenArrayBuffer(line);
    
    if (!vCol) return entity;
    
    std::vector<vec3> colors;
    for (int i = 0; i < line.size(); i += 6)
    {
        colors.push_back(color1_); colors.push_back(color1_);
        colors.push_back(color2_); colors.push_back(color2_);
        colors.push_back(color3_); colors.push_back(color3_);
    }
    entity->mesh_->GenArrayBuffer(colors);

    return entity;
}

std::shared_ptr<Entity> EntityFactory::CreateTriGasket(int numDivisions, const vec2& varRange, bool threeD, bool vCol)
{
    auto entity = CreateEntity(vCol);
    
    SierpinskiFactory::varRange_ = varRange;
    auto points = threeD ? SierpinskiFactory::Sierpinski3DDet(numDivisions) :
        SierpinskiFactory::Sierpinski2DDet(numDivisions);
    entity->mesh_->GenArrayBuffer(points);

    entity->mesh_->mode_ = GL_TRIANGLES;
    
    if (!vCol) return entity;
    
    std::vector<vec3> colors;
    for (int i = 0; i < points.size(); i += 3)
    {
        int idx = (i / 3) % 3;
        vec3 color = color1_;
        if (idx == 1) {
            color = color2_;
        } else if (idx == 2) {
            color = color3_;
        }
        for (int j = 0; j < 3; ++j) colors.push_back(color);
    }
    
    entity->mesh_->GenArrayBuffer(colors);

    return entity;
}
