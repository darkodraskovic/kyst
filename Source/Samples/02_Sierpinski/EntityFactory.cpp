#include <glm/gtc/constants.hpp>
#include <glm/gtc/random.hpp>

#include "Mover.h"
#include "Particle.h"
#include "KochFactory.h"
#include "SierpinskiFactory.h"
#include "EntityFactory.h"

EntityFactory::EntityFactory()
{
    colShader_ = std::make_shared<Shader>("../Shaders/Col.vs", "../Shaders/Col.fs");
    vColShader_ = std::make_shared<Shader>("../Shaders/VCol.vs", "../Shaders/VCol.fs");
    SetColor(MAGENTA);

    snowflakeMesh_ = std::shared_ptr<Mesh>(new Mesh());
    snowflakeMesh_->mode_ = GL_LINE_LOOP;
    snowflakeMesh_->GenArrayBuffer(KochFactory::Snowflake(3));
}

void EntityFactory::SetColor(const vec3 &color)
{
    colShader_->Use();
    colShader_->SetVec4("uColor", vec4(color, 1.0));    
}

std::shared_ptr<Entity> EntityFactory::AddEntity(EntityType type, bool vCol)
{
    std::shared_ptr<Entity> entity;
    switch (type) {
    case MOVER_ENTITY: entity = std::make_shared<Mover>();
        break;
    case PARTICLE_ENTITY: entity = std::make_shared<Particle>();
        break;
    default: entity = std::make_shared<Entity>();
        break;
    }
    
    entity->material_ = std::make_shared<Material>();
    Application::Instance().AddEntity(entity);
    entity->material_->shader_ = colShader_;
    if (vCol) {
        entity->material_->shader_ = vColShader_;
    }
    return entity;
}

std::shared_ptr<Entity> EntityFactory::CreateLineGasket(int numDivisions, const vec2& varRange, bool threeD, bool vCol)
{
    auto entity = AddEntity(MOVER_ENTITY, vCol);
    entity->mesh_ = std::make_shared<Mesh>();
    
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

    auto mover = dynamic_cast<Mover*>(entity.get());
    mover->aVelocity_.y = quarter_pi<float>();
    
    return entity;
}

std::shared_ptr<Entity> EntityFactory::CreateTriGasket(int numDivisions, const vec2& varRange, bool threeD, bool vCol)
{
    auto entity = AddEntity(BASE_ENTITY, vCol);
    entity->mesh_ = std::make_shared<Mesh>();
    
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

std::shared_ptr<ParticleEmitter> EntityFactory::CreateSnowflakeEmitter()
{
    auto emitter = std::shared_ptr<ParticleEmitter>(new ParticleEmitter());
    emitter->mesh_ = snowflakeMesh_;
    emitter->material_ = std::make_shared<Material>(colShader_);
    SetColor(color3_);
    
    emitter->emissionFreq_ = .03f;
    
    emitter->position_ = UP;
    emitter->minScale_ = ONE * 0.01f; emitter->maxScale_ = ONE * 0.1f;
    
    emitter->minVelocity_.y = 1.f; emitter->maxVelocity_.y = 1.5f;
    emitter->minGravity_ = DOWN * .7f; emitter->maxGravity_ = DOWN * .8f;

    emitter->minLifespan_ = 2.f; emitter->minLifespan_ = 3.f;

    Application::Instance().AddEntity(emitter);
    
    return emitter;
}

std::shared_ptr<Entity> EntityFactory::CreateMaze(int width, int height)
{
    auto entity = AddEntity(BASE_ENTITY, false);

    auto maze = new Maze(width, height);
    maze->RandomWalk();
    auto vertexArray = maze->GetVertexArray();

    auto mesh = std::make_shared<Mesh>();
    entity->mesh_ = mesh;
    mesh->GenArrayBuffer(vertexArray);
    mesh->mode_ = GL_LINES;

    entity->scale_ = ONE / 3.f;

    
    return entity;
}
