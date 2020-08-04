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
#include "Material2D.h"
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
    auto material1 = make_shared<Material2D>();
    material1->color_ = RED;
    auto material2 = make_shared<Material2D>(material1->shader_);
    material2->color_ = GREEN;
    material2->alpha_ = 0.5;
    auto material3 = make_shared<Material2D>(material1->shader_);
    material3->color_ = BLUE;
    material3->pctColor_ = 1.0;

    // mesh
    auto mesh = Shape2DFactory::SolidRect((LEFT + DOWN)/2.f, vec2(1));
    mesh->Generate();

    // entity
    auto entity = make_shared<Entity>(mesh, material1);
    app.AddEntity(entity);
    
    entity = make_shared<Entity>(mesh, material2);
    entity->position_ = (LEFT + DOWN) / 4.f;
    entity->position_.z = 0.25;
    entity->rotation_.y = pi<float>() / 4;
    app.AddEntity(entity);

    mesh = Shape2DFactory::Line(LEFT, RIGHT);
    mesh->colors_.push_back(GREEN);
    mesh->colors_.push_back(RED);
    mesh->Generate(material2->shader_->id_);
    entity = make_shared<Entity>(mesh, material3);
    entity->position_.z = 1;
    app.AddEntity(entity);

    material1.reset();
    material2.reset();
    material3.reset();
    mesh.reset();
    entity.reset();
    
    glLineWidth(5);
    
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
