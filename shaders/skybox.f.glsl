#version 410 core
in vec3 TexCoord;

out vec4 fragColorOut;

uniform samplerCube skybox;

void main(){
    fragColorOut = texture(skybox, TexCoord);
}