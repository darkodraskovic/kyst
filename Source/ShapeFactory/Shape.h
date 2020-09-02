#ifndef SHAPE_H
#define SHAPE_H

#include <glm/glm.hpp>

using namespace glm;

namespace Shape
{
    const vec2& direction(float rotation);
    float rotation(const vec2& direction);

    class Range
    {
        public:
        Range(float min, float max);
        void Sort();
        float min_;
        float max_;
    };
    
    class Shape
    {
    public:
        Shape(const vec2& position, float rotation = 0);
        Shape(const vec2& position,  const vec2& direction);
        virtual void Update(const vec2& position, float rotation);
        
        virtual void SetPosition(const vec2& position);        
        const vec2& GetPosition() const;
        virtual void SetDirection(const vec2& direction);        
        const vec2& GetDirection() const;
        virtual void SetRotation(float rotation);
        float GetRotation();
        
    protected:
        vec2 position_;
        vec2 direction_;
        float rotation_;
    };
    
    class Line : public Shape
    {
    public:
        Line(const vec2& position, float rotation);
        Line(const vec2& position, const vec2& direction);
        
    private:
        friend bool collide(const Line& a, const Line& b);
    };

    class Segment : public Shape
    {
    public:
        Segment(const vec2& startpoint, const vec2& endpoint);
        virtual void SetPosition(const vec2& position);
        void SetEndpoint(const vec2& endpoint);
        const vec2& GetEndpoint() const;
        
    private:
        vec2 endpoint_;
    };

    class Circle : public Shape
    {
    public:
        Circle(const vec2& position, float radius);
        
    private:
        float radius_;
        friend bool collide(const Circle& a, const Circle& b);
    };

    class Rectangle : public Shape
    {
    public:
        Rectangle(const vec2& position, const vec2& size);
        virtual void SetSize(const vec2& dir);
        const vec2& GetSize() const;
        
    private:
        vec2 size_;
        friend bool collide(const Rectangle& a, const Rectangle& b);
    };

    class OrientedRectangle : public Rectangle
    {
    public:
        OrientedRectangle(const vec2& position, const vec2& size, float rotation = 0);
        virtual void SetSize(const vec2& size) override;
        
    private:
        vec2 halfSize_;
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

#endif /* SHAPE_H */
