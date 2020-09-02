#include "Shape.h"
#include <glm/geometric.hpp>
#include <glm/gtc/constants.hpp>
#include <math.h>

// Shape helpers
// ------------------------------

const vec2& Shape::direction(float rotation)
{
    vec2* dir = new vec2();
    dir->x = cos(rotation);
    dir->y = sin(rotation);
    return *dir;
}

float Shape::rotation(const vec2& direction)
{
    return atan2(direction.y, direction.x);
}

Shape::Range::Range(float min, float max) : min_(min), max_(max) {}

void Shape::Range::Sort()
{
    if(min_ > max_) {
        float tmp = max_;
        max_ = min_;
        min_ = tmp;
    }
}

// Shapes
// ------------------------------

// Shape

Shape::Shape::Shape(const vec2 &position, float rotation)
    : position_(position), rotation_(rotation)
{
    direction_ = direction(rotation);
}

Shape::Shape::Shape(const vec2 &position, const vec2& direction)
    : position_(position), direction_(direction)
{
    rotation_ = rotation(direction);
}

void Shape::Shape::SetPosition(const vec2 &position) { position_ = position; }

const vec2 &Shape::Shape::GetPosition() const
{
    return position_;
}

void Shape::Shape::SetDirection(const vec2 &direction) {
  direction_ = direction;
  rotation_ = rotation(direction);
}

const vec2& Shape::Shape::GetDirection() const
{
    return direction_;
}

void Shape::Shape::SetRotation(float rotation) {
  rotation_ = rotation;
  direction_ = direction(rotation);
}

float Shape::Shape::GetRotation()
{
    return rotation_;
}

void Shape::Shape::Update(const vec2& position, float rotation)
{
    position_ = position;
    rotation_ = rotation;
    direction_ = direction(rotation);
}

// Line

Shape::Line::Line(const vec2& position, float rotation)
    : Shape(position, rotation) {}

Shape::Line::Line(const vec2& position, const vec2& direction)
    : Shape(position, direction) {}

// Segment

Shape::Segment::Segment(const vec2 &startpoint, const vec2 &endpoint)
    : Shape(startpoint, rotation(endpoint - startpoint)), endpoint_(endpoint) {}

void Shape::Segment::SetPosition(const vec2 &position) {
    position_ = position;
    rotation_ = rotation(endpoint_ - position_);
    direction_ = direction(rotation_);
}

void Shape::Segment::SetEndpoint(const vec2& endpoint)
{
    endpoint_ = endpoint;
    rotation_ = rotation(endpoint_ - position_);
    direction_ = direction(rotation_);
}

const vec2& Shape::Segment::GetEndpoint() const
{
    return endpoint_;
}


// Rectangle

Shape::Rectangle::Rectangle(const vec2& position, const vec2& size)
    : Shape(position), size_(size) {}

void Shape::Rectangle::SetSize(const vec2 &size) { size_ = size; }

const vec2& Shape::Rectangle::GetSize() const
{
    return size_;
}

// OrientedRectangle

Shape::OrientedRectangle::OrientedRectangle(const vec2 &position, const vec2 &size, float rotation)
    : Rectangle(position, size)
{
    SetRotation(rotation);
    halfSize_ = size / 2.0f;
}

void Shape::OrientedRectangle::SetSize(const vec2& size)
{
    Rectangle::SetSize(size);
    halfSize_ = size / 2.0f;    
}

// Circle

Shape::Circle::Circle(const vec2& position, float radius)
    : Shape(position), radius_(radius) {}

// Collides helpers
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
    vec2 aNorm = rotate90(a);
    return equal(0, glm::dot(aNorm, b));
}

bool Shape::equivalent(const Line& a, const Line& b)
{
    if (!parallel(a.GetDirection(), b.GetDirection())) return false;
    return parallel(a.GetPosition() - b.GetPosition(), a.GetDirection());
}

bool Shape::overlapping(float minA, float maxA, float minB, float maxB)
{
    return minB <= maxA && minA <= maxB;
}

bool Shape::onSameSide(const Line& axis, const Segment& s)
{
    vec2 d1 = s.GetPosition() - axis.GetPosition();
    vec2 d2 = s.GetEndpoint() - axis.GetPosition();
    vec2 norm = rotate90(axis.GetDirection());
    return glm::dot(norm, d1) * glm::dot(norm, d2) > 0;
}

const Shape::Range& Shape::project(const Segment& s, const vec2& onto)
{
    vec2 ontoN = glm::normalize(onto);
    Range* range = new Range(dot(ontoN, s.GetPosition()), dot(ontoN, s.GetEndpoint()));
    range->Sort();
    return *range;
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
    if (parallel(a.direction_, b.direction_)) return equivalent(a, b);
    return true;
}

bool Shape::collide(const Segment& a, const Segment& b)
{
    if (onSameSide(Line(a.GetPosition(), a.GetDirection()), b)) return false;
    if (onSameSide(Line(b.GetPosition(), b.GetDirection()), a)) return false;

    if (parallel(a.GetDirection(), b.GetDirection())) {
        Range r1 = project(a, a.GetDirection());
        Range r2 = project(b, a.GetDirection());
        return overlapping(r1.min_, r1.max_, r2.min_, r2.max_);
    }

    return true;
}
