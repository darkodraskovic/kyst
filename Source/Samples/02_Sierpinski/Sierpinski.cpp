#include "VecConsts.h"
#include "Sierpinski.h"

#include "ShapeUitls.h"
#include "SierpinskiFactory.h"

using namespace VecConsts;

Sierpinski::Sierpinski()
{
    material_ = std::shared_ptr<Material>(new Material);
    auto col = std::shared_ptr<Shader>(new Shader( "../Shaders/Col.vs", "../Shaders/Col.fs"));
    col->Use(); col->SetVec4("uColor", vec4(RED, 1.0f));
    auto magenta = std::shared_ptr<Shader>(new Shader( "../Shaders/Magenta.vs", "../Shaders/Magenta.fs"));
    auto vCol = std::shared_ptr<Shader>(new Shader( "../Shaders/VCol.vs", "../Shaders/VCol.fs"));
    material_->shader_ = vCol;
    
    // 2D
    std::vector<vec3> points2D = SierpinskiFactory::Sierpinski2DDet(5);

    // triangles
    // mesh_->GenArrayBuffer(points2D);

    // lines
    std::vector<vec3> lines2D;
    for (int i = 0; i < points2D.size() - 1; i += 3)
    {
        lines2D.push_back(points2D[i]); lines2D.push_back(points2D[i+1]);
        lines2D.push_back(points2D[i+1]); lines2D.push_back(points2D[i+2]);
        lines2D.push_back(points2D[i+2]); lines2D.push_back(points2D[i]);
    }
    // mesh_->mode_ = GL_LINES;
    // mesh_->GenArrayBuffer(lines2D);

    // 3D
    std::vector<vec3> points3D = SierpinskiFactory::Sierpinski3DDet(3);

    // triangles
    // mesh_->GenArrayBuffer(points3D);

    // lines
    std::vector<vec3> lines3D;
    std::vector<vec3> colors3D;
    for (int i = 0; i < points3D.size(); i += 3)
    {
        colors3D.push_back(RED); colors3D.push_back(RED);
        colors3D.push_back(GREEN); colors3D.push_back(GREEN);
        colors3D.push_back(BLUE); colors3D.push_back(BLUE);
        // float limit = 0.03;
        // ShapeUtils::prodPoint(points3D[i], -limit, +limit);
        // ShapeUtils::prodPoint(points3D[i+1], -limit, +limit);
        // ShapeUtils::prodPoint(points3D[i+2], -limit, +limit);
        lines3D.push_back(points3D[i]); lines3D.push_back(points3D[i+1]);
        lines3D.push_back(points3D[i+1]); lines3D.push_back(points3D[i+2]);
        lines3D.push_back(points3D[i+2]); lines3D.push_back(points3D[i]);
    }

    mesh_->mode_ = GL_LINES;
    mesh_->GenArrayBuffer(lines3D);
    mesh_->GenArrayBuffer(colors3D);
}

void Sierpinski::Update(float deltaTime) {
    Rotate(deltaTime*30, UP);
}
