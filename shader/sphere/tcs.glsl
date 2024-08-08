#version 410 core

layout(vertices = 4) out;

uniform float quality;

void main() {
    // per vertex code
    gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;

    // Same for all verts in a patch
    gl_TessLevelOuter[0] = quality;
    gl_TessLevelOuter[1] = quality;
    gl_TessLevelOuter[2] = quality;
    gl_TessLevelOuter[3] = quality;

    gl_TessLevelInner[0] = quality;
    gl_TessLevelInner[1] = quality;
}