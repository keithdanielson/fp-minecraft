#version 410 core

// uniform inputs
uniform sampler2D textureMap;
uniform vec3 lightColor;                // light color
uniform vec3 materialAmbColor;          // the material ambient color

// varying inputs
in vec2 textureCordinate; // coordinate for the texture
in vec4 color;

// outputs
out vec4 fragColorOut;  // color to apply to this fragment



void main() {
    // pass the interpolated color through as output
    vec3 texColor = texture(textureMap, textureCordinate).rgb;

    if(gl_FrontFacing) {
        // then pass the interpolated color through as output
            fragColorOut = color;
        }
        // otherwise we are lookiing at the back face of the fragment
        else {
            // apply only ambient lighting
            fragColorOut = vec4( texColor * lightColor * materialAmbColor, 1.0f );
        }
    //fragColorOut = texture(textureMap, textureCordinate);
}