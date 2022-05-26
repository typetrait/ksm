#version 460 core

layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

in VS_OUT {
    vec3 color;
    vec3 normal;
    vec2 texCoord;
} gs_in[];

out GS_OUT {
    vec3 color;
    vec3 normal;
    vec2 texCoord;
} gs_out;

void main() {

    gs_out.color = gs_in[0].color;
    gs_out.normal = gs_in[0].normal;
    gs_out.texCoord = gs_in[0].texCoord;

    for (int i=0; i < gl_in.length(); ++i) {
        gl_Position = gl_in[i].gl_Position;
        EmitVertex();
    }

    EndPrimitive();
}
