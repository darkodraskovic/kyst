// transforms

vec4 project3D(vec3 pos) {
    return uProjection * uView * uModel * vec4(pos, 1.0);
}

vec3 fragPos3D(vec3 pos) {
    return mat3(uModel) * pos;
}

vec3 fragNorm(vec3 norm) {
    return mat3(transpose(inverse(uModel))) * norm;
}

// utils

int alter_sign(int i, int n) {
    return (i / n) % 2 == 0 ? 1 : -1;
}
