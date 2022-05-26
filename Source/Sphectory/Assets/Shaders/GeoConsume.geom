#version 460 core

layout (triangles) in;
layout (triangle_strip, max_vertices = 90) out;

in VS_OUT {
    vec3 color;
    vec3 normal;
    vec2 texCoord;
} gs_in[];

in PLANET {
    vec4 originalPos;
    uint layer;
} gs_planet[];

out GS_OUT {
    vec3 color;
    vec3 normal;
    vec2 texCoord;
} gs_out;

void main() {

    gs_out.color = gs_in[0].color;
    gs_out.normal = gs_in[0].normal;
    gs_out.texCoord = gs_in[0].texCoord;

    // draw base
    for (int i=0; i < gl_in.length(); ++i) {
        gl_Position = gl_in[i].gl_Position;
        EmitVertex();
    }
    EndPrimitive();

    // walls
    uint depth = gs_planet[0].layer;
    for (uint i=0; i < depth; ++i) {
        gl_Position = gl_in[0].gl_Position;
        EmitVertex();
        gl_Position = gs_planet[0].originalPos;
        EmitVertex();
        gl_Position = gl_in[1].gl_Position;
        EmitVertex();
        gl_Position = gs_planet[1].originalPos;
        EmitVertex();
        gl_Position = gl_in[2].gl_Position;
        EmitVertex();
        gl_Position = gs_planet[2].originalPos;
        EmitVertex();
        gl_Position = gl_in[0].gl_Position;
        EmitVertex();
        gl_Position = gs_planet[0].originalPos;
        EmitVertex();
        EndPrimitive();
    }
}
