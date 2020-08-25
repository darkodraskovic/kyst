#ifndef SHAPE_H
#define SHAPE_H

#include <glm/glm.hpp>

using namespace glm;

namespace Shape
{
    class Shape
    {
    public:
        Shape(const vec2& position, float rotation = 0);
        virtual void Update(const vec2& position, float rotation);
        vec2 position_;
        float rotation_;        
    };
    
    class Line : public Shape
    {
    public:
        Line(const vec2& position, float rotation);
        Line(const vec2& position, const vec2& direction);
        const vec2& Direction() const;
    };

    // Segment::position_ is startpoint
    class Segment : public Shape
    {
    public:
        Segment(const vec2& position, const vec2& endpoint);
        vec2 endpoint_;
    };

    class Circle : public Shape
    {
    public:
        Circle(const vec2& position, float radius);
        float radius_;
    };

    class Rectangle : public Shape
    {
    public:
        Rectangle(const vec2& position, const vec2& size);
        vec2 size_;
    };

    // OrientedRectangle::position_ is center
    class OrientedRectangle : public Shape
    {
    public:
        OrientedRectangle(const vec2& position, const vec2& halfSize, float rotation);
        vec2 halfSize_;
    };

    bool equal(float a, float b);
    bool equal(const vec2& a, const vec2& b);
    const vec2& rotate90(const vec2& v);
    bool parallel(const vec2& a, const vec2& b);
    bool equivalent(const Line& a, const Line& b);
    bool overlapping(float minA, float maxA, float minB, float maxB);    

    bool collide(const Rectangle& a, const Rectangle& b);
    bool collide(const Circle& a, const Circle& b);
    bool collide(const Line& a, const Line& b);
    
}  // Shape

#endif /* SHAPE_H */
