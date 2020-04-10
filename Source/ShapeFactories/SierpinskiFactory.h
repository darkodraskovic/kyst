#ifndef SIERPINSKI_FACTORY_H
#define SIERPINSKI_FACTORY_H

#include_next <vector>
#include_next <glm/glm.hpp>

using namespace glm;

class SierpinskiFactory
{
public:
    SierpinskiFactory();

    static std::vector<vec3> Sierpinski2DDet(int numDivisions);
    
private:
    static void Divide2D(const vec3& a, const vec3& b, const vec3& c, int numDivisions);
    static std::vector<vec3> positions_;
};

#endif
