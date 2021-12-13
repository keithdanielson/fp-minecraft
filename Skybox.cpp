//
// Created by cmmeyers on 12/12/21.
//

#include "Skybox.hpp"

Skybox::Skybox() = default;

void Skybox::drawSkybox(glm::mat4 viewMtx, glm::mat4 projMtx) {
    glUseProgram(_shaderProgramHandle);
glProgramUniform4v(_shaderProgramHandle, _shaderProgramUniformLocations.projectionMatrix, 1, GL_FALSE)
}

void Skybox::setupSkybox(GLuint shaderProgramHandle, GLint viewMtx, GLint projMtx, GLint skybox, GLint VPos) {
    this->_shaderProgramHandle = shaderProgramHandle;
    _shaderProgramAttributeLocations.vPos = VPos;

    _shaderProgramUniformLocations.viewMatrix = viewMtx;
    _shaderProgramUniformLocations.projectionMatrix = projMtx;
    _shaderProgramUniformLocations.textureMap = skybox;


    // setup the vertices for the cube
    GLfloat skyboxVertices[108] = {
            // positions
            -1.0f,  1.0f, -1.0f,
            -1.0f, -1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,
            1.0f,  1.0f, -1.0f,
            -1.0f,  1.0f, -1.0f,

            -1.0f, -1.0f,  1.0f,
            -1.0f, -1.0f, -1.0f,
            -1.0f,  1.0f, -1.0f,
            -1.0f,  1.0f, -1.0f,
            -1.0f,  1.0f,  1.0f,
            -1.0f, -1.0f,  1.0f,

            1.0f, -1.0f, -1.0f,
            1.0f, -1.0f,  1.0f,
            1.0f,  1.0f,  1.0f,
            1.0f,  1.0f,  1.0f,
            1.0f,  1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,

            -1.0f, -1.0f,  1.0f,
            -1.0f,  1.0f,  1.0f,
            1.0f,  1.0f,  1.0f,
            1.0f,  1.0f,  1.0f,
            1.0f, -1.0f,  1.0f,
            -1.0f, -1.0f,  1.0f,

            -1.0f,  1.0f, -1.0f,
            1.0f,  1.0f, -1.0f,
            1.0f,  1.0f,  1.0f,
            1.0f,  1.0f,  1.0f,
            -1.0f,  1.0f,  1.0f,
            -1.0f,  1.0f, -1.0f,

            -1.0f, -1.0f, -1.0f,
            -1.0f, -1.0f,  1.0f,
            1.0f, -1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,
            -1.0f, -1.0f,  1.0f,
            1.0f, -1.0f,  1.0f
    };

    for(int i = 0; i < 108; ++i){
        _skyboxVertices[i] = skyboxVertices[i];
    }

    glGenVertexArrays(NUM_VAOS, _vaos);
    glGenVertexArrays(NUM_VAOS, _vbos);
    glGenVertexArrays(NUM_VAOS, _ibos);


    glBindVertexArray(_vaos[VAO_ID::SKYBOX]);

    glBindBuffer(GL_ARRAY_BUFFER, _vbos[VAO_ID::SKYBOX]);

    glBufferData( GL_ARRAY_BUFFER, 108, _skyboxVertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(_shaderProgramAttributeLocations.vPos);
    glVertexAttribPointer(_shaderProgramAttributeLocations.vPos, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);

    std::vector<std::string> textures
            {
                    "textures/dirt.jpg",
                    "textures/dirt.jpg",
                    "textures/dirt.jpg",
                    "textures/dirt.jpg",
                    "textures/dirt.jpg",
                    "textures/dirt.jpg",

            };

    _cubeMap = loadCubeMap(textures);
}

GLuint Skybox::loadCubeMap(std::vector<std::string> faces) {
    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    int width, height, nrChannels;
    for (GLuint i = 0; i < faces.size(); i++){
        unsigned char *data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);

        if (data){
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            stbi_image_free(data);
        }
        else{
            fprintf(stderr,"Couldn't load tex: \n");
    }


    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);


    return textureID;
}