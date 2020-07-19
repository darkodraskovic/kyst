mat3 translate(vec2 tnl) {
    return mat3(1.0, 0.0, 0.0,
                0.0, 1.0, 0.0,
                -tnl.x, -tnl.y, 1.0);
}

mat3 rotate(float angle) {
    return mat3(cos(angle), -sin(angle), 0.0,
                sin(angle), cos(angle), 0.0,
                0.0, 0.0, 1.0);
}

mat3 scale(vec2 scl){
    return mat3(1.0/scl.x, 0.0, 0.0,
                0.0, 1.0/scl.y, 0.0,
                0.0, 0.0, 1.0);
}
