#version 410 core

layout (location = 0) in vec3 vpos;

out vec3 TexCoords;

uniform mat4 viewMtx;
uniform mat4 projMtx;

void main()
{
    vec4 position = projection * view * vec4(vpos, 1.0);
    gl_Position = position.xyww;
    TexCoords = vpos;

}