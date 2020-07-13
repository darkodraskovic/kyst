#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/ext/scalar_constants.hpp>
#include <glm/fwd.hpp>
#include <iostream>
#include <memory>

#include "Application.h"
#include "Entity.h"
#include "Framebuffer.h"
#include "Material.h"
#include "Mesh.h"
#include "Shader.h"
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

    // Application CONTENT
    // ---------------------------------------------------------------------------

    app.camera_.position_.z = 3.0f;

    // material
    auto shader = make_shared<Shader>("../Shaders/Col.vs", "../Shaders/Col.fs");
    auto material1 = make_shared<Material>(shader);
    material1->color_ = RED;
    auto material2 = make_shared<Material>(shader);
    material2->color_ = GREEN;
    material2->alpha_ = 0.5;

    // mesh
    auto mesh = Shape2DFactory::RectMesh((LEFT + DOWN)/2.f, vec2(1), false);

    // entity
    auto entity = make_shared<Entity>(mesh, material1);
    app.AddEntity(entity);
    entity = make_shared<Entity>(mesh, material2);
    entity->position_ = (LEFT + DOWN) / 4.f;
    entity->position_.z = 0.25;
    entity->rotation_.y = pi<float>() / 4;
    app.AddEntity(entity);

    mesh = Shape2DFactory::LineMesh(LEFT, RIGHT);
    entity = make_shared<Entity>(mesh, material2);

    material1.reset();
    material2.reset();
    mesh.reset();
    entity.reset();
    
    glLineWidth(10);

    // auto sh = make_shared<Shader>("../Shaders/Tex2D.vs", "../Shaders/Tex2D.fs");
    auto fb = std::make_shared<Framebuffer>();

    // Application loop
    // ---------------------------------------------------------------------------
    while (!app.ShouldClose())
    {
        float time = glfwGetTime();

        app.Update();
    }

    fb.reset();
    // Application termination
    // ---------------------------------------------------------------------------
    app.Terminate();
    return 0;
}
