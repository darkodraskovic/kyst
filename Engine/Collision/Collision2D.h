#ifndef COLLISION2D_H
#define COLLISION2D_H

#include <glm/glm.hpp>

using namespace glm;

namespace Collision2D
{
    class Range
    {
        public:
        Range(float min, float max);
        void Sort();
        float min_;
        float max_;
    };

    class Rotor
    {
    public:
        Rotor(float rotation = 0);
        Rotor(const vec2& direction);
        virtual void Update(float rotation);
        virtual void SetRotation(float rotation);
        float GetRotation();

        vec2 direction_;
    };
        
    class Shape
    {
    public:
        Shape(const vec2& position);
        virtual void Update(const vec2& position);
        
        vec2 position_;
    };
    
    class Line : public Shape, public Rotor
    {
    public:
        Line(const vec2& position, float rotation);
        Line(const vec2& position, const vec2& direction);
    };

    class Segment : public Shape
    {
    public:
        Segment(const vec2& startpoint, const vec2& endpoint);
        
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

    class OrientedRectangle : public Rectangle, Rotor
    {
    public:
        OrientedRectangle(const vec2& position, const vec2& size, float rotation = 0);
    };

    bool equal(float a, float b);
    bool equal(const vec2& a, const vec2& b);
    const vec2& rotate90(const vec2& v);
    bool parallel(const vec2& a, const vec2& b);
    bool equivalent(const Line& a, const Line& b);
    bool overlapping(float minA, float maxA, float minB, float maxB);    
    bool onSameSide(const Line& axis, const Segment& s);
    const Range& project(const Segment& s, const vec2& onto);
    
    bool collide(const Rectangle& a, const Rectangle& b);
    bool collide(const Circle& a, const Circle& b);
    bool collide(const Line& a, const Line& b);
    bool collide(const Segment& a, const Segment& b);
    
}  // Shape

#endif /* COLLISION2D_H */
