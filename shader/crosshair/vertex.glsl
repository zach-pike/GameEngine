#version 410 core

layout(location=0) in vec2 vertexPosition;
layout(location=1) in vec2 uv;

uniform float aspect;
uniform float scale;

out vec2 UV;

void main() {
    UV = uv;
    gl_Position = vec4(vertexPosition*vec2(1, aspect)*vec2(scale), -1, 1);
}