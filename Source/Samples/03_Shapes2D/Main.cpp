#include <iostream>

#include "Application.h"
#include "Material2D.h"
#include "Shape2DFactory.h"
#include "VecConsts.h"
#include "Viewport.h"

using namespace std;
using namespace VecConsts;

int main()
{
    // Application init
    // ---------------------------------------------------------------------------
    Application app;

    if (app.Init() < 0)
    {
        std::cout << "Failed to create an OpenGL app" << std::endl;
        return -1;
    };

    glLineWidth(5);
    
    // Viewport
    // ---------------------------------------------------------------------------

    auto viewport = std::make_shared<Viewport>(app.GetWindowSize());
    app.AddViewport(viewport);
    
    auto cam = viewport->GetScene()->camera_;
    cam->position_.z = 4.0f;

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
    viewport->GetScene()->AddEntity(entity);

    // rect entity 2
    entity = make_shared<Entity>(mesh, material2);
    entity->position_ = (LEFT + DOWN) / 4.f;
    entity->position_.z = 0.25;
    entity->rotation_.y = pi<float>() / 4;
    viewport->GetScene()->AddEntity(entity);

    // line entity 2
    mesh = Shape2DFactory::Line(LEFT, RIGHT);
    mesh->colors_.push_back(GREEN);
    mesh->colors_.push_back(RED);
    mesh->Generate(material2->shader_->id_);
    entity = make_shared<Entity>(mesh, material3);
    entity->position_.z = 1;
    viewport->GetScene()->AddEntity(entity);

    // polygons
    vector<vec3> points = {LEFT, DOWN, RIGHT, UP};
    mesh = Shape2DFactory::LinePolygon(points);
    mesh->Generate();
    entity = make_shared<Entity>(mesh, material4);
    viewport->GetScene()->AddEntity(entity);
    
    mesh = Shape2DFactory::SolidPolygon(points);
    mesh->colors_ = {GREEN, BLUE, RED, BLUE};
    mesh->Generate(material5->shader_->id_);
    entity = make_shared<Entity>(mesh, material5);
    entity->scale_ *= 0.33f;
    entity->position_.z = 0.5;
    viewport->GetScene()->AddEntity(entity);
    
    // Reset POINTERS
    // ---------------------------------------------------------------------------
    
    material1.reset();
    material2.reset();
    material3.reset();
    mesh.reset();
    entity.reset();
    viewport.reset();

    cam->LookAt(ZERO);
    // Application loop
    // ---------------------------------------------------------------------------
    while (!app.ShouldClose())
    {
        cam->ProcessInput(app.GetInput(), app.GetDeltaTime());
        app.Update();
    }

    // Application termination
    // ---------------------------------------------------------------------------
    app.Terminate();
    return 0;
}
