#include <iostream>
#include "Engine/Application.h"
#include "Engine/Graphics/Material2D.h"
#include "ShapeFactory/Shape2DFactory.h"
#include "Engine/VecConsts.h"

using namespace std;
using namespace VecConsts;
using namespace ShapeFactory;

class App : public Application {
public:
    virtual int Init() {
        Application::Init();

        Viewport* viewport = AddViewport(true);
        auto cam = viewport->scene_->camera_;
        cam->position_.z = 5;
        cam->LookAt(ZERO);

        // Material
        Material2D* material = new Material2D();
        material->pctColor_ = 1;

        // Mesh
        vector<vec3> points = vector<vec3>{LEFT+DOWN, RIGHT+DOWN, UP};
        Mesh* mesh = Shape2DFactory::SolidPolygon(points);
        mesh->colors_ = std::vector<vec3>{RED, GREEN, BLUE};
        mesh->Generate(material->shader_->id_);

        // Entity
        Entity* entity = new Entity(mesh, material);
        viewport->scene_->AddEntity(entity);
        
        return 0;
    }
    virtual void ProcessInput() {
        Application::ProcessInput();
        if(input_->GetKey(GLFW_KEY_ESCAPE)) Close();
    }
    virtual void Update(float deltaTime) {
        viewports_[0]->scene_->camera_->ProcessInput(input_, deltaTime_);
        Application::Update(deltaTime);
    }
};

int main()
{
    App app;
    if (app.Init() < 0)
    {
        std::cout << "Failed to create an OpenGL app" << std::endl;
        return -1;
    };

    while (!app.ShouldClose())
    {
        app.Run();
    }
    
    app.Terminate();

    return 0;
}
