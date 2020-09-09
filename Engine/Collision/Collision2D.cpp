#include <cmath>
#include <glm/fwd.hpp>
#include <glm/geometric.hpp>
#include <glm/gtc/constants.hpp>

#include "Collision2D.h"

using namespace Collision2D;

// Shapes
// ------------------------------

// Rotor

Rotor::Rotor(float rotation) { SetRotation(rotation); }

Rotor::Rotor(const vec2& direction) : direction_(direction) {}

void Rotor::SetRotation(float rotation)
{
    direction_.x = cos(rotation);
    direction_.y = sin(rotation);
}

float Rotor::GetRotation()
{
  return atan2(direction_.y, direction_.x);
}

void Rotor::Update(float rotation)
{
    SetRotation(rotation);
}

// Shape

Shape::Shape(const vec2 &position) : position_(position) {}

void Shape::Update(const vec2& position) { position_ = position; }

// Line

Line::Line(const vec2& position, float rotation)
    : Shape(position), Rotor(rotation) {}

Line::Line(const vec2& position, const vec2& direction)
    : Shape(position), Rotor(direction) {}

// Segment

Segment::Segment(const vec2 &startpoint, const vec2 &endpoint)
    : Shape(startpoint), endpoint_(endpoint) {}

// Rectangle

Rectangle::Rectangle(const vec2& position, const vec2& size)
    : Shape(position), size_(size) {}

// OrientedRectangle

OrientedRectangle::OrientedRectangle(const vec2 &position, const vec2 &size, float rotation)
    : Rectangle(position, size), Rotor(rotation) {}

// Circle

Circle::Circle(const vec2& position, float radius)
    : Shape(position), radius_(radius) {}

// Collides helpers
// ------------------------------

bool Collision2D::equal(float a, float b)
{
    float threshold = 1.0f / 8192.0f;
    return fabsf(a - b) < threshold;
}

bool Collision2D::equal(const vec2& a, const vec2& b)
{
    return equal(a.x, b.x) && equal(a.y, b.y);
}

const vec2& Collision2D::rotate90(const vec2& v)
{
    vec2* r = new vec2();
    r->x = -v.y;
    r->y = v.x;
    return *r;
}

bool Collision2D::parallel(const vec2& a, const vec2& b)
{
    vec2 aNorm = rotate90(a);
    return equal(0, glm::dot(aNorm, b));
}

bool Collision2D::equivalent(const Line& a, const Line& b)
{
    if (!parallel(a.direction_, b.direction_)) return false;
    return parallel(a.position_ - b.position_, a.direction_);
}

bool Collision2D::overlapping(float minA, float maxA, float minB, float maxB)
{
    return minB <= maxA && minA <= maxB;
}

bool Collision2D::onSameSide(const Line& axis, const Segment& s)
{
    vec2 d1 = s.position_ - axis.position_;
    vec2 d2 = s.endpoint_ - axis.position_;
    vec2 norm = rotate90(axis.direction_);
    return glm::dot(norm, d1) * glm::dot(norm, d2) > 0; // colinear is not on the same side
}

Range::Range(float min, float max) : min_(min), max_(max) {}

void Range::Sort()
{
    if(min_ > max_)
    {
        float tmp = max_;
        max_ = min_;
        min_ = tmp;
    }
}

const Range& Collision2D::project(const Segment& s, const vec2& onto)
{
    vec2 ontoN = glm::normalize(onto);
    Range* range = new Range(dot(ontoN, s.position_), dot(ontoN, s.endpoint_));
    range->Sort();
    return *range;
}

// Collides
// ------------------------------

bool Collision2D::collide(const Rectangle &a, const Rectangle &b)
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

bool Collision2D::collide(const Circle& a, const Circle& b)
{
    float radiusSum = a.radius_ + b.radius_;
    vec2 distance = a.position_ - b.position_;
    return glm::length(distance) <= radiusSum;
}

bool Collision2D::collide(const Line& a, const Line& b)
{
    if (parallel(a.direction_, b.direction_)) return equivalent(a, b);
    return true;
}

bool Collision2D::collide(const Segment& a, const Segment& b)
{
    vec2 aDir = (a.endpoint_ - a.position_);
    vec2 bDir = (b.endpoint_ - b.position_);
    if (onSameSide(Line(a.position_, aDir), b)) return false;
    if (onSameSide(Line(b.position_, bDir), a)) return false;

    if (parallel(aDir, bDir)) {
        Range r1 = project(a, aDir);
        Range r2 = project(b, aDir);
        return overlapping(r1.min_, r1.max_, r2.min_, r2.max_);
    }

    return true;
}
