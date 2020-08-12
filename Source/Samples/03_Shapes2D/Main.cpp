#include <iostream>

#include "Application.h"
#include "Material2D.h"
#include "Shape2DFactory.h"
#include "VecConsts.h"

using namespace std;
using namespace VecConsts;

int main()
{
    // Application init
    // ---------------------------------------------------------------------------
    Application& app = Application::Instance();

    if (app.Init() < 0)
    {
        std::cout << "Failed to create an OpenGL app" << std::endl;
        return -1;
    };

    glLineWidth(5);
    
    // Viewport
    // ---------------------------------------------------------------------------

    auto viewport = std::make_shared<Viewport>();
    app.viewports_.push_back(viewport);
    
    app.camera_ = viewport->scene_->camera_;
    app.camera_->position_.z = 4.0f;

    viewport->AddEffect("../Shaders/Effects/Noop.fs");
    viewport->AddEffect("../Shaders/Effects/Inversion.fs");
    // viewport->AddEffect("../Shaders/Effects/Remove.fs");

    // Application CONTENT
    // ---------------------------------------------------------------------------

    // material
    auto material1 = make_shared<Material2D>();
    material1->color_ = RED;
    auto material2 = make_shared<Material2D>(material1->shader_);
    material2->color_ = GREEN;
    material2->alpha_ = 0.5;
    auto material3 = make_shared<Material2D>(material1->shader_);
    material3->color_ = BLUE;
    material3->pctColor_ = 1.0;
    auto material4 = make_shared<Material2D>(material1->shader_);
    material4->color_ = BLUE;
    auto material5 = make_shared<Material2D>(material1->shader_);
    material5->pctColor_ = 1.0;

    // rect mesh
    auto mesh = Shape2DFactory::SolidRect((LEFT + DOWN)/2.f, vec2(1));
    mesh->Generate();

    // rect entity 1
    auto entity = make_shared<Entity>(mesh, material1);
    viewport->scene_->AddEntity(entity);

    // rect entity 2
    entity = make_shared<Entity>(mesh, material2);
    entity->position_ = (LEFT + DOWN) / 4.f;
    entity->position_.z = 0.25;
    entity->rotation_.y = pi<float>() / 4;
    viewport->scene_->AddEntity(entity);

    // line entity 2
    mesh = Shape2DFactory::Line(LEFT, RIGHT);
    mesh->colors_.push_back(GREEN);
    mesh->colors_.push_back(RED);
    mesh->Generate(material2->shader_->id_);
    entity = make_shared<Entity>(mesh, material3);
    entity->position_.z = 1;
    viewport->scene_->AddEntity(entity);

    // polygons
    vector<vec3> points = {LEFT, DOWN, RIGHT, UP};
    mesh = Shape2DFactory::LinePolygon(ZERO, points);
    mesh->Generate();
    entity = make_shared<Entity>(mesh, material4);
    viewport->scene_->AddEntity(entity);
    
    mesh = Shape2DFactory::SolidPolygon(ZERO, points);
    mesh->colors_ = {GREEN, BLUE, RED, BLUE};
    mesh->Generate(material5->shader_->id_);
    entity = make_shared<Entity>(mesh, material5);
    entity->scale_ *= 0.33f;
    entity->position_.z = 0.5;
    viewport->scene_->AddEntity(entity);
    
    // Reset POINTERS
    // ---------------------------------------------------------------------------
    
    material1.reset();
    material2.reset();
    material3.reset();
    mesh.reset();
    entity.reset();
    viewport.reset();
    
    // Application loop
    // ---------------------------------------------------------------------------
    while (!app.ShouldClose())
    {
        float time = glfwGetTime();

        app.Update();
    }

    // Application termination
    // ---------------------------------------------------------------------------
    app.Terminate();
    return 0;
}
