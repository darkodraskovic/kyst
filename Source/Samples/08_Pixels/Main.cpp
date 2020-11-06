#include <iostream>
#include "Engine/Application.h"
#include "Engine/Graphics/Framebuffer.h"
#include "Engine/Graphics/Material2D.h"
#include "Engine/Graphics/Texture2D.h"
#include "ShapeFactory/Shape2DFactory.h"
#include "Engine/VecConsts.h"

using namespace std;
using namespace VecConsts;
using namespace ShapeFactory;

const int width = 320;
const int height = 320;
unsigned int data[width * height];

void SetPixel(int x, int y, unsigned int color) { data[y * width + x] = color; }

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

    // unsigned int colorbuffer;
    // glGenTextures(1, &colorbuffer);
    // glBindTexture(GL_TEXTURE_2D, colorbuffer);
    // glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, nullptr);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    for (int i = 0; i < width * height; ++i) {
        data[i] = 0x000000FF;
    }    
    for (int i = 20; i < 50; ++i) {
        for (int j = 20; j < 50; ++j) {
            SetPixel(i, j, 0x00FFFF00);
        }
        
    }
    Texture2D* texture = new Texture2D(&app);
    texture->CreateImage(width, height, data);
    
    Mesh* mesh = Shape2DFactory::SolidRect(ZERO, ONE_2D);
    auto material = new Material2D();
    material->pctTexture_ = 1;
    // unsigned int diffuseBricks = app.resourceManager_.LoadTexture("Assets/bricks_diffuse.jpg");
    material->texture_ = texture->GetTexture();
    mesh->Generate(material->shader_->id_);
    auto entity = new Entity(mesh, material);
    entity->position_ = (LEFT + DOWN) * 0.5f;
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
