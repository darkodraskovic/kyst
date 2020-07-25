#include <glm/gtc/constants.hpp>
#include <glm/gtc/random.hpp>
#include <memory>

#include "VecConsts.h"
#include "Shader.h"
#include "Material.h"
#include "Mover.h"

#include "Application.h"

#include "MazeFactory.h"

#include "MazeGen.h"

using namespace VecConsts;

MazeGen::MazeGen() {}

std::shared_ptr<Mover> MazeGen::CreateMaze(int width, int height, const vec3& color)
{
    std::shared_ptr<Mover> maze = std::make_shared<Mover>();
    maze->material_ = std::make_shared<Material>("../Shaders/Col.vs", "../Shaders/Col.fs");
    maze->material_->color_ = color;
    
    Application::Instance().AddEntity(maze);    
    auto mazeFactory = new MazeFactory(width, height);
    mazeFactory->RandomWalk();
    auto vertexArray = mazeFactory->GetVertexArray();

    auto mesh = std::make_shared<Mesh>();
    maze->mesh_ = mesh;
    mesh->GenArrayBuffer(vertexArray);
    mesh->mode_ = GL_LINES;

    maze->scale_ = ONE / 4.f;

    return maze;
}
