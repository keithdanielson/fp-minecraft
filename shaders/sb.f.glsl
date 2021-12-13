#version 410 core

// uniform inputs
// TODO #E
uniform sampler2D ourTexture;

// varying inputs
// TODO #D
in vec2 TexCoord;

// fragment outputs
out vec4 fragColorOut;

void main() {
    // TODO #F
    vec4 fColor = texture(ourTexture, TexCoord);

    // TODO #G
    fragColorOut = fColor;
}