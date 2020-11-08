#include <iostream>
#include "Engine/Application.h"
#include "Engine/Graphics/Framebuffer.h"
#include "Engine/Graphics/Material2D.h"
#include "Engine/Graphics/Texture2D.h"
#include "Engine/Graphics/Shader.h"
#include "Engine/Graphics/Texture2D.h"
#include "ShapeFactory/Shape2DFactory.h"
#include "Engine/VecConsts.h"

using namespace std;
using namespace VecConsts;
using namespace ShapeFactory;

const int width = 128;
const int height = 128;
unsigned int data[width * height];
unsigned int data2[width * height];

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

    // Viewport* viewport = app.AddViewport();
    Viewport* viewport = app.AddViewport(false, app.GetWindowSize().x / 2, app.GetWindowSize().y / 2);
    // viewport->scale_.x = 2;
    // viewport->scale_.y = 2;
    
    auto cam = viewport->scene_->camera_;
    // cam->zoom_ = 2;
    // cam->position_.z = 5;
    // cam->LookAt(ZERO);
    
    for (int i = 0; i < width * height; ++i) {
        data[i] = 0x000000FF;
    }
    Texture2D* texture = new Texture2D(&app);
    texture->CreateImage(width, height, data);
    texture->GetData(data2);
    for (int i = 20; i < 50; ++i) {
        for (int j = 20; j < 50; ++j) {
            if (i == j) data2[i * width + j] = 0x0000FF00;
        }
    }
    texture->SetData(0, 0, width, height, data2);

    Mesh* mesh = Shape2DFactory::SolidRect(ZERO, ONE_2D);
    auto material = new Material2D();
    material->pctTexture_ = 1;
    material->texture_ = texture->GetId();
    mesh->Generate(material->shader_->id_);
    auto entity = new Entity(mesh, material);
    entity->scale_.x = width;
    entity->scale_.y = height;
    // entity->position_.x = app.GetWindowSize().x / 2;
    // entity->position_.y = app.GetWindowSize().y / 2;
    // entity->position_.x = app.GetWindowSize().x / 8;
    // entity->position_.y = app.GetWindowSize().y / 8;
    viewport->scene_->AddEntity(entity);

    // viewport->GetTexture()->SetData(0, 0, width, height, data2);
    // viewport->position_ += (RIGHT + UP) * .5f;
    // viewport->position_ += (RIGHT + UP) / 4.f;
    
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
