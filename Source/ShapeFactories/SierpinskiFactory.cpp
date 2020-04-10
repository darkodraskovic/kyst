#include "SierpinskiFactory.h"

SierpinskiFactory::SierpinskiFactory()
{
}

std::vector<vec3> SierpinskiFactory::positions_;

std::vector<vec3> SierpinskiFactory::Sierpinski2DDet(int numDivisions)
{
    vec3 a(-1, -1, 0);
    vec3 b(1, -1, 0);
    vec3 c(0, 1, 0);

    positions_.clear();
    Divide2D(a, b, c, numDivisions);

    return positions_;
}

void SierpinskiFactory::Divide2D(const vec3& a, const vec3& b, const vec3& c, int numDivisions)
{
    if (numDivisions < 1) {
        positions_.push_back(a);
        positions_.push_back(b);
        positions_.push_back(c);
        return;
    }
    
    vec3 ab((a + b) * 0.5f);
    vec3 ac((a + c) * 0.5f);
    vec3 bc((b + c) * 0.5f);

    numDivisions--;
    Divide2D(a, ab, ac, numDivisions);
    Divide2D(ab, b, bc, numDivisions);
    Divide2D(ac, bc, c, numDivisions);    
}
