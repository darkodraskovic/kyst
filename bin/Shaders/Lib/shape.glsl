float rectFill(vec2 frag_pos, vec2 size, vec2 anchor) {
    frag_pos = step(0 - anchor * size, frag_pos)
        - step(size - anchor * size, frag_pos);
    return frag_pos.x * frag_pos.y;
}

float rectStroke(vec2 frag_pos, vec2 size, vec2 anchor, float line_width) {
    return rectFill(frag_pos, size, anchor)
        - rectFill(frag_pos, size - line_width, anchor);
}

float circleFill(vec2 frag_pos, float radius, vec2 anchor) {
    return 1.0 - step(radius, length(frag_pos - radius * anchor));
}

float circleStroke(vec2 frag_pos, float radius, vec2 anchor, float line_width) {
    return circleFill(frag_pos, radius, anchor)
        - circleFill(frag_pos, radius - line_width, anchor);
}
