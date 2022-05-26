#version 460 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec3 aNormal;
layout (location = 3) in vec2 aTexCoord;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

out VS_OUT {
    vec3 color;
    vec3 normal;
    vec2 texCoord;
} vs_out;

void main() {
    gl_Position = projection * view * model * vec4(aPos, 1.0);

    vs_out.color = aColor;
    vs_out.normal = aNormal;
    vs_out.texCoord = aTexCoord;
}
