#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/ext/scalar_constants.hpp>
#include <glm/fwd.hpp>
#include <memory>

#include "Application.h"
#include "Entity.h"
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
    auto material1 =
        make_shared<Material>("../Shaders/Col.vs", "../Shaders/Col.fs");
    material1->color_ = RED;
    auto material2 = make_shared<Material>("../Shaders/Col.vs", "../Shaders/Col.fs");
    material2->color_ = GREEN;
    material2->alpha_ = 0.5;

    // mesh
    auto mesh = make_shared<Mesh>();
    // mesh->mode_ = GL_LINES;
    // auto points = Shape2DFactory::Line(LEFT/2.f);
    mesh->mode_ = GL_TRIANGLES;
    auto points = Shape2DFactory::Rect(ivec2(1,1), (LEFT+DOWN)/2.f, true);
    mesh->GenArrayBuffer(points);

    // entity
    auto entity = make_shared<Entity>(mesh, material1);
    entity->position_ = (RIGHT + UP)/4.f;
    app.AddEntity(entity);
    entity = make_shared<Entity>(mesh, material2);
    entity->position_ = (LEFT + DOWN)/4.f;
    entity->position_.z = 0.25;
    entity->rotation_.y = pi<float>() / 4;
    app.AddEntity(entity);

    material1.reset();
    mesh.reset();
    entity.reset();
    
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
