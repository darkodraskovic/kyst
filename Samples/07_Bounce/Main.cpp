#include <cassert>
#include <glm/ext/scalar_constants.hpp>
#include <iostream>
#include "Engine/VecConsts.h"
#include "Engine/Application.h"
#include "Engine/Scene/Entity.h"
#include "Engine/Graphics/Material2D.h"
#include "Engine/Collision/Collision2D.h"
#include "ShapeFactory/Shape2DFactory.h"

using namespace VecConsts;
using namespace ShapeFactory;

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
    mesh->Generate(material->shader_->id_);
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
    using namespace Collision2D;
    
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

    vec2 dPoint{3, 4};
    vec2 ePoint{11, 1};
    vec2 fPoint{8, 4};
    vec2 gPoint{11, 7};
    Segment de{dPoint, ePoint};
    Segment fg{fPoint, gPoint};
    Segment df{dPoint, fPoint};
    Segment eg{ePoint, gPoint};
    Segment ae{aPoint, ePoint};
    assert(collide(de, de)); // congruent
    assert(collide(de, df)); // copunctual
    assert(!collide(de, fg));
    assert(!collide(df, eg));
    assert(collide(ae, df));
    assert(collide(df, ae)); // reverse order

    OrientedRectangle aORect = {{3, 5}, {1, 3}, pi<float>() / 12};
    OrientedRectangle bORect = {{10, 5}, {2, 2}, -pi<float>() / 12};
    assert(!collide(aORect, bORect));
    OrientedRectangle cORect = {{-6, 5}, {2, 1}, 0};
    OrientedRectangle dORect = {{-4, 2}, {3, 1}, 0}; // colinear
    assert(!collide(cORect, dORect));
    assert(!collide(aORect, cORect));
    dORect.SetRotation(-pi<float>()/4);
    assert(collide(cORect, dORect));
    assert(collide(dORect, cORect));
    OrientedRectangle eORect = {{5, 2}, {3, 1}, -pi<float>()/4};
    OrientedRectangle fORect = {{9, -1}, {3, 1}, -pi<float>()/4};
    assert(collide(eORect, fORect));
    assert(!collide(eORect, cORect));
}
