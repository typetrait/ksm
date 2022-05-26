#version 460 core

in GS_OUT {
    vec3 color;
    vec3 normal;
    vec2 texCoord;
} fs_in;

out vec4 FragColor;

uniform sampler2D sampler;

void main() {
    FragColor = texture(sampler, fs_in.texCoord);
    FragColor *= vec4(fs_in.color, 1.0f);
}
