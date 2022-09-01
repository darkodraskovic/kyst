#include <iostream>

#include "Engine/Application.h"
#include "Engine/Graphics/Framebuffer.h"
#include "Engine/Graphics/Material2D.h"
#include "Engine/Graphics/Shader.h"
#include "Engine/Graphics/Texture2D.h"
#include "Engine/VecConsts.h"
#include "ShapeFactory/Shape2DFactory.h"

using namespace std;
using namespace VecConsts;
using namespace ShapeFactory;

const int width = 128;
const int height = 128;
unsigned int data0[width * height];
unsigned int data1[width * height];

class App : public Application {
 public:
  virtual void Init() {
    Application::Init();

    // Viewport* viewport = app.AddViewport();
    Viewport* viewport = AddViewport(false, GetWindowSize().x / 2, GetWindowSize().y / 2);
    viewport->scale_.x = .5;
    viewport->scale_.y = .5;
    viewport->position_.x = .25;

    auto cam = viewport->GetScene()->camera_;
    // cam->zoom_ = 2;
    // cam->position_.z = 5;
    // cam->LookAt(ZERO);

    for (int i = 0; i < width * height; ++i) {
      data0[i] = 0x000000FF;
    }
    Texture2D* texture = new Texture2D(this);
    texture->CreateImage(width, height, data0);
    texture->GetData(data1);
    for (int i = 20; i < 50; ++i) {
      for (int j = 20; j < 50; ++j) {
        if (i == j) data1[i * width + j] = 0x0000FF00;
      }
    }
    texture->SetData(0, 0, width, height, data1);

    Mesh* mesh = Shape2DFactory::SolidRect(ZERO, ONE_2D);
    auto material = new Material2D();
    material->pctTexture_ = 1;
    material->texture_ = texture->GetId();
    mesh->Generate(material->shader_->id_);
    auto entity = new Entity(mesh, material);
    entity->scale_.x = width;
    entity->scale_.y = height;
    // entity->position_.x = GetWindowSize().x / 2;
    // entity->position_.y = GetWindowSize().y / 2;
    // entity->position_.x = GetWindowSize().x / 8;
    // entity->position_.y = GetWindowSize().y / 8;
    viewport->GetScene()->AddEntity(entity);

    // viewport->GetTexture()->SetData(0, 0, width, height, data2);
    // viewport->position_ += (RIGHT + UP) * .5f;
    // viewport->position_ += (RIGHT + UP) / 4.f;
  }

  virtual void Update(float deltaTime) {
    viewports_[0]->GetScene()->camera_->Update(deltaTime_, *GetInput());
    Application::Update(deltaTime);
  }
};

int main() {
  App app;

  app.Init();

  app.Run();

  app.Terminate();

  return 0;
}
