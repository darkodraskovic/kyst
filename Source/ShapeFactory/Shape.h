#ifndef SHAPE_H
#define SHAPE_H

#include <glm/glm.hpp>

using namespace glm;

namespace Shape {
    struct Line {
        vec2 base_;
        vec2 direction_;
    };
    
    struct Segment {
        vec2 p1_;
        vec2 p2_;
    };

    struct Circle {
        vec2 center_;
        float radius_;
    };

    struct Rectangle {
        vec2 origin_;
        vec2 size_;
    };

    struct OrientedRectangle {
        vec2 center_;
        vec2 halfSize_;
        float rotation_;
    };

    bool overlapping(float minA, float maxA, float minB, float maxB);

    bool collide(const Rectangle& a, const Rectangle& b);
    bool collide(const Circle& a, const Circle& b);
}  // Shape

#endif /* SHAPE_H */
