#version 410 core


// uniform inputs
uniform vec3 eyePos;                    // eye position in world space
uniform vec3 lightPos;                  // light position in world space
uniform vec3 lightDir;                  // light direction in world space
uniform float lightCutoff;              // angle of our spotlight
uniform vec3 lightColor;                // light color
uniform vec3 materialDiffColor;         // the material diffuse color
uniform vec3 materialSpecColor;         // the material specular color
uniform float materialShininess;        // the material shininess value
uniform vec3 materialAmbColor;          // the material ambient color
uniform uint lightType;                 // 0 - point light, 1 - directional light, 2 - spotlight


// uniform inputs
uniform mat4 projection;
uniform mat4 view;


// attribute inputs
layout(location = 0) in vec3 vPos;
layout(location = 1) in vec3 vertexNormal;
layout(location = 2) in vec2 textCordinateIn;
layout(location = 3) in mat4 instanceMatrix; // mat4 will take up location 3,4,5,6
layout(location = 7) in mat3 normalMtx; // normal matrix locations 7,8,9


// varying outputs
out vec2 textureCordinate;
out vec4 color;


vec3 diffuseColor(vec3 vertexPosition, vec3 vertexNormal) {
    vec3 lightVector;

    // directional light
    if(lightType == 1) {
        lightVector = normalize( -lightDir );
    }
    // spotlight or point light
    else {
        lightVector = normalize(lightPos - vertexPosition);
    }

    vec3 diffColor = lightColor * materialDiffColor * max( dot(vertexNormal, lightVector), 0.0 );

    // spotlight - check if within cone
    if(lightType == 2) {
        float theta = dot(normalize(lightDir), -lightVector);
        if( theta <= lightCutoff ) {
            diffColor = vec3(0.0, 0.0, 0.0);
        }
    }

    return diffColor;
}

// compute the specular color using Blinn-Phong specular reflectance
vec3 specularColor(vec3 vertexPosition, vec3 vertexNormal) {
    vec3 lightVector;

    // directional light
    if(lightType == 1) {
        lightVector = normalize( -lightDir );
    }
    // spotlight or point light
    else {
        lightVector = normalize(lightPos - vertexPosition);
    }

    vec3 viewVector = normalize(eyePos - vertexPosition);
    vec3 halfwayVector = normalize(viewVector + lightVector);

    vec3 specColor = lightColor * materialSpecColor * pow(max( dot(vertexNormal, halfwayVector), 0.0 ), 4.0*materialShininess);

    // spotlight - check if within cone
    if(lightType == 2) {
        float theta = dot(normalize(lightDir), -lightVector);
        if( theta <= lightCutoff ) {
            specColor = vec3(0.0, 0.0, 0.0);
        }
    }

    return specColor;
}


void main() {
    // transform & output the vertex in clip space
    gl_Position = projection * view * instanceMatrix * vec4(vPos, 1.0);
    textureCordinate = textCordinateIn;

    // transform vertex information into world space
    vec3 vPosWorld = (instanceMatrix * vec4(vPos, 1.0)).xyz;
    vec3 nVecWorld = normalize( normalMtx * vertexNormal );

    // compute each component of the Phong Illumination Model
    vec3 diffColor = diffuseColor(vPosWorld, nVecWorld);
    vec3 specColor = specularColor(vPosWorld, nVecWorld);
    vec3 ambColor = lightColor * materialAmbColor;

    // assign the final color for this vertex
    color = vec4(diffColor + specColor + ambColor, 1.0f);
}