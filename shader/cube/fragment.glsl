#version 410 core

out vec3 color;

in vec2 UV;
// uniform sampler2D myTexture;

uniform vec3 inColor;

void main() {
    color = vec3(0, UV);
}