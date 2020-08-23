#include <cassert>
#include <iostream>
#include "Application.h"
#include "Entity.h"
#include "Material2D.h"
#include "Shape2DFactory.h"
#include "VecConsts.h"
#include "Shape.h"

using namespace VecConsts;

void assertColllide();

int main()
{
    assertColllide();
    
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

    auto viewport = app.AddViewport();
    auto cam = viewport->GetScene()->camera_;
    cam->position_.z = 5;
    cam->LookAt(ZERO);

    auto material = new Material2D();
    material->color_ = GREEN;
    auto mesh = Shape2DFactory::SolidEllipse(ZERO, ONE*2.f);
    mesh->Generate();
    auto entity = new Entity(mesh, material);
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

void assertColllide()
{
    using namespace Shape;
    
    Rectangle aRect{{1, 1}, {4, 4}};
    Rectangle bRect{{2, 2}, {5, 5}};
    Rectangle cRect{{6, 4}, {4, 2}};
    assert(collide(aRect, bRect));
    assert(collide(bRect, cRect));
    assert(!collide(aRect, cRect));

    Circle aCircle{{4, 4}, 2};
    Circle bCircle{{7, 4}, 2};
    Circle cCircle{{10, 4}, 2};
    assert(collide(aCircle, bCircle));
    assert(collide(bCircle, cCircle));
    assert(!collide(aCircle, cCircle));

    vec2 aPoint{3, 5};
    vec2 bPoint{3, 2};
    vec2 cPoint{8, 4};
    vec2 down{5, -1};
    vec2 up{5, 2};
    Line l1{aPoint, down};
    Line l2{aPoint, up};
    Line l3{bPoint, up};
    Line l4{cPoint, down};
    assert(collide(l1, l2));
    assert(collide(l1, l3));
    assert(!collide(l2, l3));
    assert(collide(l1, l4));    
}
