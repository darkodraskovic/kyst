#ifndef SHAPE_H
#define SHAPE_H

#include <glm/glm.hpp>

using namespace glm;

namespace Shape
{
    class Shape
    {
    public:
        Shape(const vec2& position);
        virtual void Update(const vec2& position, float rotation) = 0;
        vec2 position_;
    };
    
    class Line : public Shape
    {
    public:
        void Update(const vec2& position, float rotation) override;
        const vec2& Direction(); // TODO
        float rotation_;
    };
    
    class Segment : public Shape
    {
    public:
        // TODO: p1_ -> position; p2_ -> end_; Point(const vec2& position, const vec2& end)
        vec2 p1_;
        vec2 p2_;
    };

    class Circle : public Shape
    {
    public:
        Circle(const vec2& position, float radius);
        void Update(const vec2& position, float rotation) override;
        float radius_;
    };

    class Rectangle : public Shape
    {
    public:
        Rectangle(const vec2& position, const vec2& size);
        void Update(const vec2& position, float rotation) override;
        vec2 size_;
    };

    class OrientedRectangle : public Shape
    {
    public:
        OrientedRectangle(const vec2& position, const vec2& halfSize, float rotation);
        void Update(const vec2& position, float rotation) override;
        const vec2& Center(); // TODO
        vec2 halfSize_;
        float rotation_;
    };

    bool overlapping(float minA, float maxA, float minB, float maxB);
    bool collide(const Rectangle& a, const Rectangle& b);
    bool collide(const Circle& a, const Circle& b);

}  // Shape

#endif /* SHAPE_H */
