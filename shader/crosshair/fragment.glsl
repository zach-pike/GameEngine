#version 410 core

out vec3 color;

in vec2 UV;

uniform sampler2D myTexture;

void main() {
    vec4 texColor = texture(myTexture, UV);
    if (texColor.a < .1) discard;
    color = texColor.rgb;
}