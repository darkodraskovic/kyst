#ifndef COLLISION2D_H
#define COLLISION2D_H

#include <glm/fwd.hpp>
#include <glm/glm.hpp>

using namespace glm;

namespace Collision2D
{
    // Shapes    
    class Range
    {
        public:
        Range() {};
        Range(float min, float max);
        void Sort();
        bool Overlapping(const Range& other) const;
        const Range& Hull(const Range& other) const;
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
        float GetRotation() const;

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
        bool Equivalent(const Line& other) const;
    };

    class Segment : public Shape
    {
    public:
        Segment(const vec2& startpoint, const vec2& endpoint);
        const Range& Project(const vec2& dir) const;
        bool OnOneSide(const Line& line) const;
        
        vec2 endpoint_;
    };

    class Circle : public Shape
    {
    public:
        Circle(const vec2& position, float radius);
        bool Contains(const vec2& point) const;
        
        float radius_;
    };

    class Rectangle : public Shape
    {
    public:
        Rectangle(const vec2& position, const vec2& size);
        
        vec2 size_;
    };

    class OrientedRectangle : public Shape, public Rotor
    {
    public:
        OrientedRectangle(const vec2& center, const vec2& halfSize, float rotation = 0);
        const Segment& Edge(int n) const; // cw side count: 0 = up, 1, = right, etc.
        bool SAT(const Segment& axis) const;
        const Range& Project(const vec2& dir) const;
        
        vec2 halfSize_;
    };

    // Collides helpers    
    bool equal(float a, float b);
    bool equal(const vec2& a, const vec2& b);
    const vec2& rotate(const vec2& v, float rotation);
    const vec2& rotate90(const vec2& v);
    bool parallel(const vec2& a, const vec2& b);
    const vec2& project(const vec2& a, const vec2& b);
    bool overlapping(float minA, float maxA, float minB, float maxB);

    // Collides
    bool collide(const Rectangle& a, const Rectangle& b);
    bool collide(const Circle& a, const Circle& b);
    bool collide(const Line& a, const Line& b);
    bool collide(const Segment& a, const Segment& b);
    bool collide(const OrientedRectangle& a, const OrientedRectangle& b);
    bool collide(const Circle& circle, const Line& line);
    bool collide(const Circle& circle, const Segment& segment);
    bool collide(const Circle& circle, const Rectangle& rect);
    bool collide(const Rectangle& rect, const Line& line); // TODO
    bool collide(const Rectangle& rect, const Segment& segment); // TODO
}  // Shape

#endif /* COLLISION2D_H */
