#include <iostream>
#include "Shape.h"
#include <glm/geometric.hpp>

bool Shape::overlapping(float minA, float maxA, float minB, float maxB)
{
    return minB <= maxA && minA <= maxB;
}

bool Shape::collide(const Rectangle &a, const Rectangle &b)
{
    float aLeft = a.origin_.x;
    float aRight = a.origin_.x + a.size_.x;
    float bLeft = b.origin_.x;
    float bRight = b.origin_.x + b.size_.x;

    float aBottom = a.origin_.y;
    float aTop = a.origin_.y + a.size_.y;
    float bBottom = b.origin_.y;
    float bTop = b.origin_.y + b.size_.y;

    return overlapping(aLeft, aRight, bLeft, bRight) &&
        overlapping(aBottom, aTop, bBottom, bTop);
}

bool Shape::collide(const Circle& a, const Circle& b)
{
    float radiusSum = a.radius_ + b.radius_;
    vec2 distance = a.center_ - b.center_;
    return glm::length(distance) <= radiusSum;
}
