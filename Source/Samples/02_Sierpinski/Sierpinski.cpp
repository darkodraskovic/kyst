#include <glm/gtc/constants.hpp>
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
    SierpinskiFactory::varRange_ += vec2(-0.03, 0.1);
    std::vector<vec3> points2D = SierpinskiFactory::Sierpinski2DDet(4);

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
    std::vector<vec3> colors3D;
    std::vector<vec3> lines3D;
    
    // triangles
    // mesh_->GenArrayBuffer(points3D);
    for (int i = 0; i < points3D.size(); i += 3)
    {
        switch ((i/3)%3) {
        case 0: {
            colors3D.push_back(RED); colors3D.push_back(RED); colors3D.push_back(RED);
            break;
        }
        case 1: {
            colors3D.push_back(GREEN); colors3D.push_back(GREEN); colors3D.push_back(GREEN);
            break;
        }
        case 2: {
            colors3D.push_back(BLUE); colors3D.push_back(BLUE); colors3D.push_back(BLUE);
            break;
        }
        default:
            break;
        }
    }    
    // mesh_->GenArrayBuffer(colors3D);
    
    // lines
    for (int i = 0; i < points3D.size(); i += 3)
    {
        colors3D.push_back(RED); colors3D.push_back(RED);
        colors3D.push_back(GREEN); colors3D.push_back(GREEN);
        colors3D.push_back(BLUE); colors3D.push_back(BLUE);
        lines3D.push_back(points3D[i]); lines3D.push_back(points3D[i+1]);
        lines3D.push_back(points3D[i+1]); lines3D.push_back(points3D[i+2]);
        lines3D.push_back(points3D[i+2]); lines3D.push_back(points3D[i]);
    }

    mesh_->mode_ = GL_LINES;
    mesh_->GenArrayBuffer(lines3D);
    mesh_->GenArrayBuffer(colors3D);
}

void Sierpinski::Update(float deltaTime) {
    Rotate(deltaTime * glm::quarter_pi<float>(), UP);
}
