#version 450


layout(binding = 0) uniform UniformBufferObject {
    mat4 model;
    mat4 view;
    mat4 proj;
} ubo;

layout(location = 0) in vec2 in_Position;
layout(location = 1) in vec3 in_Color;

layout(location = 0) out vec3 out_FragColor;

void main() {
    gl_Position = ubo.proj * ubo.view * ubo.model * vec4(in_Position, 0.0, 1.0);
    out_FragColor = in_Color;
}