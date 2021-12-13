//
// Created by cmmeyers on 12/12/21.
//

#include <CSCI441/ShaderProgram.hpp>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <CSCI441/OpenGLEngine.hpp>
#include <string>
#include <vector>
#include <stb_image.h>


#ifndef MP_SKYBOX_HPP
#define MP_SKYBOX_HPP

class Skybox {
public:

    GLuint _cubeMap;
    GLuint _shaderProgramHandle;
    GLfloat _skyboxVertices[108];
    GLfloat _skyboxIndices;

    Skybox();

    void drawSkybox(glm::mat4 viewMtx, glm::mat4 projMtx);
    void setupSkybox(GLuint shaderProgramHandle, GLint viewMtx, GLint projMtx, GLint skybox, GLint VPos);

    GLuint loadCubeMap(std::vector<std::string> faces);

private:


    /// \desc total number of VAOs in our scene
    static constexpr GLuint NUM_VAOS = 1;
    /// \desc used to index through our VAO/VBO/IBO array to give named access
    enum VAO_ID {
        /// \desc the patch surface
        SKYBOX = 0,
    };
    /// \desc VAO for our objects
    GLuint _vaos[NUM_VAOS];
    /// \desc VBO for our objects
    GLuint _vbos[NUM_VAOS];
    /// \desc IBO for our objects
    GLuint _ibos[NUM_VAOS];
    /// \desc the number of points that make up our VAO
    GLsizei _numVAOPoints[NUM_VAOS];

    /// \desc stores the locations of all of our shader uniforms
    struct ShaderProgramUniformLocations {
        /// \desc precomputed MVP matrix location
        GLint textureMap;
        GLint viewMatrix;
        GLint projectionMatrix;
    } _shaderProgramUniformLocations;
    /// \desc stores the locations of all of our shader attributes
    struct ShaderProgramAttributeLocations {
        /// \desc vertex position location
        GLint vPos;
    } _shaderProgramAttributeLocations;

};



#endif //MP_SKYBOX_HPP
