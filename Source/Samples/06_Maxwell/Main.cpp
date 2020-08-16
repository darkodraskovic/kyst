#include <cmath>
#include <iostream>
#include <memory>
#include "Application.h"
#include "Material.h"
#include "Material2D.h"
#include "Scene.h"
#include "Shape2DFactory.h"
#include "VecConsts.h"

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

    // Application CONTENT
    // ---------------------------------------------------------------------------

    Viewport* viewport = app.AddViewport();
    auto cam = viewport->GetScene()->camera_;
    cam->position_.z = 5;
    cam->LookAt(ZERO);

    Material2D* material = new Material2D;
    material->pctColor_ = 1;
    std::vector<vec3> points = std::vector<vec3>{LEFT+DOWN, RIGHT+DOWN, vec3(0,-1+sqrt(3),0)};
    Mesh* mesh = Shape2DFactory::SolidPolygon(points);
    mesh->colors_ = std::vector<vec3>{RED, GREEN, BLUE};
    mesh->Generate(material->shader_->id_);
    Entity* entity = new Entity(mesh, material);
    viewport->GetScene()->AddEntity(entity);

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
