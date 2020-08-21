#ifndef SHAPE_H
#define SHAPE_H

#include <glm/glm.hpp>

using namespace glm;

namespace Shape {
    struct Line {
        vec3 base_;
        vec3 direction_;
    };
    
    struct Segment {
        vec3 p1_;
        vec3 p2_;
    };

    struct Circle {
        vec3 center_;
        float radius_;
    };

    struct Rectangle {
        vec3 origin_;
        vec2 size_;
    };

    struct OrientedRectangle {
        vec3 center_;
        vec2 halfSize_;
        float rotation_;
    };
}  // Shape

#endif /* SHAPE_H */
