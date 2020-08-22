#include <iostream>
#include "Shape.h"
#include <glm/geometric.hpp>

bool Shape::overlapping(float minA, float maxA, float minB, float maxB)
{
    return minB <= maxA && minA <= maxB;
}

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

Shape::Shape::Shape(const vec2 &position) : position_(position)
{
    
}

Shape::Rectangle::Rectangle(const vec2 &position, const vec2 &size)
    : Shape(position), size_(size) {}

void Shape::Rectangle::Update(const vec2 &position, float rotation)
{
    position_ = position;
}    
    
Shape::Circle::Circle(const vec2& position, float radius)
    : Shape(position), radius_(radius) {}

void Shape::Circle::Update(const vec2 &position, float rotation)
{
    position_ = position;
}    

