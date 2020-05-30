#include "ShapeUitls.h"
#include "SierpinskiFactory.h"

SierpinskiFactory::SierpinskiFactory()
{
}

std::vector<vec3> SierpinskiFactory::points_;
vec2 SierpinskiFactory::varRange_(0,0);

const std::vector<vec3>& SierpinskiFactory::Sierpinski2DDet(int numDivisions)
{
    vec3 a(-1, -1, 0);
    vec3 b(1, -1, 0);
    vec3 c(0, 1, 0);

    points_.clear();
    Divide(a, b, c, numDivisions);

    return points_;
}

const std::vector<vec3>& SierpinskiFactory::Sierpinski3DDet(int numDivisions)
{
    vec3 a(-1, -1, -1);
    vec3 b(0, -1, 1);
    vec3 c(1, -1, -1);
    vec3 d(0, 1, 0);

    points_.clear();
    Divide(a, b, c, d, numDivisions);

    return points_;
}

void SierpinskiFactory::Divide(const vec3& a, const vec3& b, const vec3& c, int numDivisions)
{
    if (numDivisions < 1) {
        points_.push_back(a);
        points_.push_back(b);
        points_.push_back(c);
        return;
    }

    vec3 ab((a + b) * 0.5f);
    vec3 ac((a + c) * 0.5f);
    vec3 bc((b + c) * 0.5f);

    ShapeUtils::prodPoint(ab, varRange_.x, varRange_.y);
    ShapeUtils::prodPoint(ac, varRange_.x, varRange_.y);
    ShapeUtils::prodPoint(bc, varRange_.x, varRange_.y);

    numDivisions--;
    Divide(a, ab, ac, numDivisions);
    Divide(ab, b, bc, numDivisions);
    Divide(ac, bc, c, numDivisions);
}

void SierpinskiFactory::Divide(const vec3& a, const vec3& b, const vec3& c, const vec3& d, int numDivisions)
{
    if (numDivisions < 1) {
        points_.push_back(a);
        points_.push_back(b);
        points_.push_back(c);

        points_.push_back(a);
        points_.push_back(b);
        points_.push_back(d);

        points_.push_back(a);
        points_.push_back(c);
        points_.push_back(d);

        points_.push_back(b);
        points_.push_back(c);
        points_.push_back(d);
        return;
    }

    vec3 ab = (a + b) * 0.5f;
    vec3 ac = (a + c) * 0.5f;
    vec3 ad = (a + d) * 0.5f;
    vec3 bc = (b + c) * 0.5f;
    vec3 bd = (b + d) * 0.5f;
    vec3 cd = (c + d) * 0.5f;

    ShapeUtils::prodPoint(ab, varRange_.x, varRange_.y);
    ShapeUtils::prodPoint(ac, varRange_.x, varRange_.y);
    ShapeUtils::prodPoint(ad, varRange_.x, varRange_.y);
    ShapeUtils::prodPoint(bc, varRange_.x, varRange_.y);
    ShapeUtils::prodPoint(bd, varRange_.x, varRange_.y);
    ShapeUtils::prodPoint(cd, varRange_.x, varRange_.y);

    numDivisions--;
    Divide(a, ab, ac, ad, numDivisions);
    Divide(ab, b, bc, bd, numDivisions);
    Divide(ac, bc, c, cd, numDivisions);
    Divide(ad, bd, cd, d, numDivisions);
}
