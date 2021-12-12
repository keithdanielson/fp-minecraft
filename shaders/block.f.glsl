#version 410 core

// uniform inputs
uniform sampler2D textureMap;

// varying inputs
in vec2 textureCordinate; // coordinate for the texture

// outputs
out vec4 fragColorOut;  // color to apply to this fragment



void main() {
    // pass the interpolated color through as output
//    vec4 fColor = texture(blockTexture, textCoordinateIn);
//
//    fragColorOut = fColor;
   //fragColorOut = vec4(1.0,1.0,1.0,1.0);
    fragColorOut = texture(textureMap, textureCordinate);
}