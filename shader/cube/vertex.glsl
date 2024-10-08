#version 410 core

layout(location=0) in vec3 vertexLocation;
layout(location=1) in vec2 uv;

uniform mat4 MVP;

out vec2 UV;

void main() {
    gl_Position = MVP * vec4(vertexLocation * vec3(.5), 1);
    UV = uv;
}