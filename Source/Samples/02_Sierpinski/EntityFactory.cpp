#include <glm/gtc/constants.hpp>
#include <glm/gtc/random.hpp>

#include "Engine/Graphics/Material.h"
#include "Engine/Scene/Scene.h"
#include "Engine/Scene/Mover.h"
#include "Engine/Scene/Particle.h"
#include "ShapeFactory/MazeFactory.h"
#include "ShapeFactory/KochFactory.h"
#include "ShapeFactory/SierpinskiFactory.h"
#include "EntityFactory.h"

using namespace ShapeFactory;

EntityFactory::EntityFactory(Scene* scene)
    : scene_(scene)
{
    colShader_ = std::make_shared<Shader>("Shaders/Col.vs", "Shaders/Col.fs");
    vColShader_ = std::make_shared<Shader>("Shaders/VCol.vs", "Shaders/VCol.fs");

    snowflakeMesh_ = std::shared_ptr<Mesh>(new Mesh());
    snowflakeMesh_->mode_ = GL_LINE_LOOP;
    snowflakeMesh_->positions_ = KochFactory::Snowflake(3);
    snowflakeMesh_->Generate(colShader_->id_);
}

std::shared_ptr<Mover> EntityFactory::AddMover(bool vCol)
{
    std::shared_ptr<Mover> mover = std::make_shared<Mover>();
    mover->material_ = std::make_shared<Material>();
    mover->material_->shader_ = colShader_;
    mover->material_->color_ = color1_;
    if (vCol) {
        mover->material_->shader_ = vColShader_;
    }

    mover->name_ = "mover";

    scene_->AddEntity(mover);
    return mover;
}

std::shared_ptr<Mover> EntityFactory::CreateLineGasket(int numDivisions, const vec2& varRange, bool threeD, bool vCol)
{
    auto gasket = AddMover(vCol);
    gasket->aVelocity_.y = quarter_pi<float>();
    
    gasket->mesh_ = std::make_shared<Mesh>();
    SierpinskiFactory::varRange_ = varRange;
    auto points = threeD ? SierpinskiFactory::Sierpinski3DDet(numDivisions) :
        SierpinskiFactory::Sierpinski2DDet(numDivisions);
    gasket->mesh_->mode_ = GL_LINES;
    std::vector<vec3>& lines = gasket->mesh_->positions_;
    for (int i = 0; i < points.size(); i += 3)
    {
        lines.push_back(points.at(i));
        lines.push_back(points.at(i + 1));
        lines.push_back(points.at(i + 1));
        lines.push_back(points.at(i + 2));
        lines.push_back(points.at(i + 2));
        lines.push_back(points.at(i));
    }

    if (!vCol)
    {
        gasket->mesh_->Generate(colShader_->id_);
        return gasket;
    };

    std::vector<vec3>& colors = gasket->mesh_->colors_;
    for (int i = 0; i < lines.size(); i += 6) {
        colors.push_back(color1_);
        colors.push_back(color1_);
        colors.push_back(color2_);
        colors.push_back(color2_);
        colors.push_back(color3_);
        colors.push_back(color3_);
    }

    gasket->mesh_->Generate(vColShader_->id_);
    return gasket;
}

std::shared_ptr<Mover> EntityFactory::CreateTriGasket(int numDivisions, const vec2& varRange, bool threeD, bool vCol)
{
    auto gasket = AddMover(vCol);
    gasket->aVelocity_.y = quarter_pi<float>();
    
    gasket->mesh_ = std::make_shared<Mesh>();
    SierpinskiFactory::varRange_ = varRange;
    gasket->mesh_->positions_ = threeD ? SierpinskiFactory::Sierpinski3DDet(numDivisions) :
        SierpinskiFactory::Sierpinski2DDet(numDivisions);
    gasket->mesh_->mode_ = GL_TRIANGLES;

    if (!vCol)
    {
        gasket->mesh_->Generate(colShader_->id_);
        return gasket;
    };

    std::vector<vec3>& colors = gasket->mesh_->colors_;
    for (int i = 0; i < gasket->mesh_->positions_.size(); i += 3)
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

    gasket->mesh_->Generate(vColShader_->id_);
    return gasket;
}

std::shared_ptr<ParticleEmitter> EntityFactory::CreateSnowflakeEmitter()
{
    auto emitter = std::shared_ptr<ParticleEmitter>(new ParticleEmitter());
    emitter->name_ = "emitter";
    emitter->mesh_ = snowflakeMesh_;
    emitter->material_ = std::make_shared<Material>(colShader_);
    emitter->material_->color_ = color3_;

    emitter->emissionFreq_ = .03f;

    emitter->position_ = UP;
    emitter->minScale_ = ONE * 0.01f; emitter->maxScale_ = ONE * 0.1f;

    emitter->minVelocity_.y = 1.f; emitter->maxVelocity_.y = 1.5f;
    emitter->minGravity_ = DOWN * .7f; emitter->maxGravity_ = DOWN * .8f;

    emitter->minLifespan_ = 2.f; emitter->minLifespan_ = 3.f;

    scene_->AddEntity(emitter);

    return emitter;
}
