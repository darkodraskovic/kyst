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
    auto material = make_shared<Material>("../Shaders/Col.vs", "../Shaders/Col.fs");

    // mesh
    auto mesh = make_shared<Mesh>();
    // mesh->mode_ = GL_LINES;
    // auto points = Shape2DFactory::Line(LEFT/2.f);
    mesh->mode_ = GL_TRIANGLES;
    auto points = Shape2DFactory::Rect(ivec2(1,1), (LEFT+DOWN)/2.f, true);
    mesh->GenArrayBuffer(points);

    // entity
    auto entity = make_shared<Entity>(mesh, material);
    app.AddEntity(entity);

    material.reset();
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
