#version 450

layout(location = 0) in vec2 in_Position;
layout(location = 1) in vec3 in_Color;

layout(location = 0) out vec3 out_FragColor;

void main() {
    gl_Position = vec4(in_Position, 0.0, 1.0);
    out_FragColor = in_Color;
}