#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec3 aNormal;
layout (location = 3) in vec2 aTexCoord;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

#define SELECTION_MAX 60
uniform int selectedVertices[SELECTION_MAX];

out vec3 outColor;
out vec2 TexCoord;

void main()
{
    bool selected = false;
    for (int i=0; i<SELECTION_MAX; ++i)
        if (gl_VertexID == selectedVertices[i])
            selected = true;

    if (selected) {
        gl_Position = projection * view * model * vec4(aPos * 0.8, 1.0);
        outColor = vec3(1.0, 0.0, 0.0);
    } else {
        gl_Position = projection * view * model * vec4(aPos, 1.0);
        outColor = aColor;
    }

    TexCoord = aTexCoord;
}
