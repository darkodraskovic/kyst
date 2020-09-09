#include <iostream>
#include "Engine/Application.h"
#include "Engine/Graphics/Material2D.h"
#include "ShapeFactory/Shape2DFactory.h"
#include "Engine/VecConsts.h"

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

    // Application CONTENT
    // ---------------------------------------------------------------------------

    Viewport* viewport = app.AddViewport();
    auto cam = viewport->GetScene()->camera_;
    cam->position_.z = 5;
    cam->LookAt(ZERO);

    // Material
    Material2D* material = new Material2D;
    material->pctColor_ = 1;

    // Mesh
    vector<vec3> points = vector<vec3>{LEFT+DOWN, RIGHT+DOWN, UP};
    Mesh* mesh = Shape2DFactory::SolidPolygon(points);
    mesh->colors_ = std::vector<vec3>{RED, GREEN, BLUE};
    mesh->Generate(material->shader_->id_);

    // Entity
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
