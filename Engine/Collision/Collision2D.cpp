#include <cmath>
#include <glm/common.hpp>
#include <iostream>
#include <glm/ext/matrix_transform.hpp>
#include <glm/fwd.hpp>

#include "Engine/VecConsts.h"
#include "Collision2D.h"

using namespace Collision2D;

// Shapes
// ------------------------------

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

bool Range::Overlapping(const Range &other) const
{
    return overlapping(min_, max_, other.min_, other.max_);
}

const Range& Range::Hull(const Range& other) const
{
    Range* hull = new Range();
    hull->min_ = min_ < other.min_ ? min_ : other.min_;
    hull->max_ = max_ > other.max_ ? max_ : other.max_;
    return *hull;    
}

// Rotor

Rotor::Rotor(float rotation) { SetRotation(rotation); }

Rotor::Rotor(const vec2& direction) : direction_(direction) {}

void Rotor::SetRotation(float rotation)
{
    direction_.x = cos(rotation);
    direction_.y = sin(rotation);
}

float Rotor::GetRotation() const
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

bool Line::Equivalent(const Line& other) const
{
    if (!parallel(direction_, other.direction_)) return false;
    return parallel(position_ - other.position_, direction_);
}

// Segment

Segment::Segment(const vec2 &startpoint, const vec2 &endpoint)
    : Shape(startpoint), endpoint_(endpoint) {}

const Range& Segment::Project(const vec2& onto) const
{
    vec2 ontoN = glm::normalize(onto);
    Range* range = new Range(dot(ontoN, position_), dot(ontoN, endpoint_));
    range->Sort();
    return *range;
}

bool Segment::OnOneSide(const Line& line) const
{
    vec2 d1 = position_ - line.position_;
    vec2 d2 = endpoint_ - line.position_;
    vec2 norm = rotate90(line.direction_);
    return glm::dot(norm, d1) * glm::dot(norm, d2) > 0; // colinear is not on the same side
}

// Rectangle

Rectangle::Rectangle(const vec2& position, const vec2& size)
    : Shape(position), size_(size) {}

// OrientedRectangle

OrientedRectangle::OrientedRectangle(const vec2 &center, const vec2 &halfSize, float rotation)
    : Shape(center), halfSize_(halfSize), Rotor(rotation) {}

const Segment& OrientedRectangle::Edge(int n) const
{
    vec2 a = halfSize_;
    vec2 b = halfSize_;
    switch (n % 4)
    {
    case 0:
        a.x = -a.x;
        break;
    case 1:
        b.y = -b.y;
        break;
    case 2:
        a.y = -a.y;
        b = -b;
        break;
    default:
        a = -a;
        b.x = -b.x;
        break;
    }

    float rot = GetRotation();
    return *new Segment(rotate(a, rot) + position_, rotate(b, rot) + position_);
}

bool OrientedRectangle::SAT(const Segment &axis) const
{
    vec2 dir = axis.endpoint_ - axis.position_;
    Range axisRange = axis.Project(dir);
    return !axisRange.Overlapping(Project(dir));
}

const Range& OrientedRectangle::Project(const vec2& dir) const
{
    return Edge(0).Project(dir).Hull(Edge(2).Project(dir));
}

// Circle

Circle::Circle(const vec2 &position, float radius)
    : Shape(position), radius_(radius) {}

bool Circle::Contains(const vec2 &point) const
{
    return  glm::length(point - position_) <= radius_;
}

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

const vec2& Collision2D::rotate(const vec2& vec, float rotation)
{
  float s = sinf(rotation);
  float c = cosf(rotation);
  return *new vec2(vec.x * c - vec.y * s, vec.x * s + vec.y * c);
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

const vec2& Collision2D::project(const vec2& project, const vec2& onto)
{
    float d = glm::dot(onto, onto);
    if(0 < d)
    {
        float dp = glm::dot(project, onto);
        vec2* res = new vec2((onto * dp) / d);
        return *res;
    }
    return onto;    
}

bool Collision2D::overlapping(float minA, float maxA, float minB, float maxB)
{
    return minB <= maxA && minA <= maxB;
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
    if (parallel(a.direction_, b.direction_)) return a.Equivalent(b);
    return true;
}

bool Collision2D::collide(const Segment& a, const Segment& b)
{
    vec2 aDir = (a.endpoint_ - a.position_);
    vec2 bDir = (b.endpoint_ - b.position_);
    
    if (b.OnOneSide(Line(a.position_, aDir))) return false;
    if (a.OnOneSide(Line(b.position_, bDir))) return false;

    if (parallel(aDir, bDir)) return a.Project(aDir).Overlapping(b.Project(aDir));

    return true;
}

bool Collision2D::collide(const OrientedRectangle& a, const OrientedRectangle& b)
{
    if (a.SAT(b.Edge(0))) return false;
    if (a.SAT(b.Edge(1))) return false;
    if (b.SAT(a.Edge(0))) return false;
    if (b.SAT(a.Edge(1))) return false;
    return true;
}

bool Collision2D::collide(const Circle& circle, const Line& line)
{
    vec2 nearestPt = project(circle.position_ - line.position_, line.direction_) + line.position_;
    return circle.Contains(nearestPt);
}

bool Collision2D::collide(const Circle& circle, const Segment& segment)
{
    if(circle.Contains(segment.position_)) return true;
    if(circle.Contains(segment.endpoint_)) return true;
    
    vec2 dir = segment.endpoint_ - segment.position_;
    vec2 proj = project(circle.position_ - segment.position_, dir);
    vec2 nearestPt = proj + segment.position_;
    return circle.Contains(nearestPt) &&
        glm::length(proj) <= length(dir) &&
        glm::dot(proj, dir) >= 0;
}

bool Collision2D::collide(const Circle& circle, const Rectangle& rect)
{
    vec2 clamped = glm::clamp(circle.position_, rect.position_, rect.position_ + rect.size_);
    return circle.Contains(clamped);
}
