#include "Viewport.h"
#include "Scene.h"

const std::string Viewport::vertexPath_ = "../Shaders/Viewport/Viewport.vs";
const std::string Viewport::fragmentPath_ = "../Shaders/Viewport/Viewport.fs";

Viewport::Viewport(const uvec2& size)
{
    scene_ = std::make_shared<Scene>(std::make_shared<Camera>());
    Init(size.x, size.y);
}

Viewport::Viewport(const uvec2& size, std::shared_ptr<Scene> scene)
    : scene_(scene)
{
    Init(size.x, size.y);
}

void Viewport::Init(unsigned int width, unsigned int height)
{
    width_ = width;
    height_ = height;
    scene_->viewport_ = this;
    GenQuad(width, height);
    GenBuffers(width, height);
}

Application* Viewport::GetApplication() { return application_;}

Scene* Viewport::GetScene() { return scene_.get(); }

void Viewport::GenBuffers(float width, float height)
{
    shader_ = std::make_shared<Shader>(vertexPath_, fragmentPath_);
    frontbuffer_ = std::make_shared<Framebuffer>(width, height);
    backbuffer_ = std::make_shared<Framebuffer>(width, height);
}

void Viewport::GenQuad(float width, float height)
{
    quad_ = std::make_shared<Mesh>();
    quad_->mode_ = GL_TRIANGLE_FAN;

    float right = -1 + 2 * (width / Application::GetWindowSize().x);
    float up = -1 + 2 * (height / Application::GetWindowSize().y);

    quad_->positions_.push_back(vec3(-1, -1, 0));
    quad_->positions_.push_back(vec3(right, -1, 0));
    quad_->positions_.push_back(vec3(right, up, 0));
    quad_->positions_.push_back(vec3(-1, up, 0));

    quad_->texCoords_.push_back(vec2(0, 0));
    quad_->texCoords_.push_back(vec2(1, 0));
    quad_->texCoords_.push_back(vec2(1, 1));
    quad_->texCoords_.push_back(vec2(0, 1));

    quad_->Generate();
}

void Viewport::AddEffect(const char *fragmentPath)
{
    auto effect = std::make_shared<Shader>(Viewport::vertexPath_, fragmentPath);
    effects_.push_back(effect);
}


void Viewport::Render()
{
    frontbuffer_->Bind();
    scene_->Draw(width_, height_);
    auto bound = frontbuffer_;
    
    if (!effects_.empty()) {
        glDisable(GL_DEPTH_TEST);
        glActiveTexture(GL_TEXTURE0);
        auto unbound = backbuffer_;
        for (int i = 0; i < effects_.size(); i++) {
            bound->Unbind();
            unbound->Bind();
            auto tmp = bound;
            bound = unbound;
            unbound = tmp;
            glBindTexture(GL_TEXTURE_2D, unbound->colorbuffer_);
            effects_[i]->Use();
            effects_[i]->SetInt("uTexture", 0);
            quad_->Render();            
        }
    }
    
    bound->Unbind();
    texture_ = bound->colorbuffer_;
}

void Viewport::Draw()
{
    glDisable(GL_DEPTH_TEST);
    glActiveTexture(GL_TEXTURE0);
    shader_->Use();
    glBindTexture(GL_TEXTURE_2D, texture_);
    shader_->SetInt("uTexture", 0);
    shader_->SetMat4("uModel", glm::translate(glm::mat4(1.f), position_));    
    quad_->Render();
}

void Viewport::Update(float deltaTime)
{
    scene_->Update(deltaTime);
    Render();
    Draw();
}

unsigned int Viewport::GetTexture()
{
    Render();
    return texture_;
}