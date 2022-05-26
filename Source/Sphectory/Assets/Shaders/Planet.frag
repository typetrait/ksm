#version 460 core

out vec4 FragColor;

in vec3 outColor;
in vec2 TexCoord;

uniform sampler2D sampler;

#define SELECTION_MAX 20
uniform int selectedIndices[SELECTION_MAX];

void main()
{
    vec3 outColor2;
    bool selected = false;

    for (int i=0; i<SELECTION_MAX; ++i)
        if (gl_PrimitiveID == selectedIndices[i])
            selected = true;

    if (selected)
        outColor2 = vec3(1.0, 0.0, 0.0);
    else
        outColor2 = outColor;

    //FragColor = texture(sampler, TexCoord);
    FragColor = vec4(outColor2, 1.0f);
}
