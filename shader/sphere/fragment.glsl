#version 410 core

out vec3 color;

in vec2 tesscoord;

uniform sampler2D myTexture;

float light(float v, float k) {
    return pow(2.718, -pow(v*k - k, 2));
}

void main() {
    vec4 texColor = texture(myTexture, vec2(tesscoord.x, 1-tesscoord.y));

    if (texColor.a < .1) discard;

    // float k = .2;

    color = texColor.rgb;

    // color = vec3(1, tesscoord);
}