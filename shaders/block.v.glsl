#version 410 core


// uniform inputs
uniform mat4 projection;
uniform mat4 view;


// attribute inputs
layout(location = 0) in vec3 vPos;
layout(location = 1) in vec3 vertexNormal;
layout(location = 2) in vec2 textCordinateIn;
layout(location = 3) in mat4 instanceMatrix; // mat4 will take up location 3,4,5,6



// varying outputs
out vec2 textureCordinate;


void main() {
    // transform & output the vertex in clip space
    gl_Position = projection * view * instanceMatrix * vec4(vPos, 1.0);
    textureCordinate = textCordinateIn;
}