#include "Shape.h"
#include <glm/gtc/constants.hpp>

// Shapes
// ------------------------------

// Shape

Shape::Shape::Shape(const vec2& position, float rotation)
    : position_(position), rotation_(rotation) {}

void Shape::Shape::Update(const vec2& position, float rotation)
{
    position_ = position;
    rotation_ = rotation;
}

// Line

Shape::Line::Line(const vec2& position, float rotation)
    : Shape(position, rotation) {}

Shape::Line::Line(const vec2& position, const vec2& direction)
    : Shape(position)
{
    rotation_ = std::atan2(direction.y, direction.x);
}

const vec2& Shape::Line::Direction() const
{
    vec2* dir = new vec2();
    dir->x = cos(rotation_);
    dir->y = sin(rotation_);
    return *dir;
}

// Segment

Shape::Segment::Segment(const vec2& position, const vec2& endpoint)
    : Shape(position), endpoint_(endpoint) {}
    
// Rectangle

Shape::Rectangle::Rectangle(const vec2& position, const vec2& size)
    : Shape(position), size_(size) {}

// Circle

Shape::Circle::Circle(const vec2& position, float radius)
    : Shape(position), radius_(radius) {}

// Helpers
// ------------------------------

bool Shape::equal(float a, float b)
{
    float threshold = 1.0f / 8192.0f;
    return fabsf(a - b) < threshold;
}

bool Shape::equal(const vec2& a, const vec2& b)
{
    return equal(a.x, b.x) && equal(a.y, b.y);
}

const vec2& Shape::rotate90(const vec2& v)
{
    vec2* r = new vec2();
    r->x = -v.y;
    r->y = v.x;
    return *r;
}

bool Shape::parallel(const vec2& a, const vec2& b)
{
    vec2 na = rotate90(a);
    return equal(0, glm::dot(na, b));
}

bool Shape::equivalent(const Line& a, const Line& b)
{
    if (!parallel(a.Direction(), b.Direction())) return false;
    return parallel(a.position_ - b.position_, a.Direction());
}

bool Shape::overlapping(float minA, float maxA, float minB, float maxB)
{
    return minB <= maxA && minA <= maxB;
}

// Collides
// ------------------------------

bool Shape::collide(const Rectangle &a, const Rectangle &b)
{
    float aLeft = a.position_.x;
    float aRight = a.position_.x + a.size_.x;
    float bLeft = b.position_.x;
    float bRight = b.position_.x + b.size_.x;

    float aBottom = a.position_.y;
    float aTop = a.position_.y + a.size_.y;
    float bBottom = b.position_.y;
    float bTop = b.position_.y + b.size_.y;

    return overlapping(aLeft, aRight, bLeft, bRight) &&
        overlapping(aBottom, aTop, bBottom, bTop);
}

bool Shape::collide(const Circle& a, const Circle& b)
{
    float radiusSum = a.radius_ + b.radius_;
    vec2 distance = a.position_ - b.position_;
    return glm::length(distance) <= radiusSum;
}

bool Shape::collide(const Line& a, const Line& b)
{
    if (parallel(a.Direction(), b.Direction())) return equivalent(a, b);
    return true;
}
