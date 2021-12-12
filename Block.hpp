//
// Created by cmmeyers on 11/28/21.
//

#ifndef MP_BLOCK_HPP
#define MP_BLOCK_HPP
#include <CSCI441/ShaderProgram.hpp>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <CSCI441/OpenGLEngine.hpp>
#include <string>

class Block {
public:
    Block();
    void drawBlock(GLint numBlocks, glm::mat4 viewMtx, glm::mat4 projMtx);


    // Creates static VAOs and VBOs send vertex data to gpu for future rendering
    GLuint getBlockVAO();
    void setupBlock(GLuint shaderProgramHandle, GLint projection, GLint view, GLint textureMap, GLint vPos, GLint vertexNormal, GLint texCoord);
    void setTexture(std::string name, GLuint handle);
    std::string getTextureName();
    void cleanupBlock();


private:
    // the position of the block in the world
    glm::vec3 _blockLocation;
    std::string textureName;

    struct BlockDescriptors {
        GLuint _blockVAO;
        GLuint _blockVBO;
    } _blockDescriptors;

    /// \desc handle of the shader program to use when drawing the block
    GLuint _shaderProgramHandle;
    /// \desc stores the uniform locations needed for the plan information

    struct shaderUniformLocations {
        GLint projection;
        GLint view;
        GLuint textureMap;
    }_shaderUniformLocations;


    struct BlockShaderAttributeLocations{
        GLint vPos;
        GLint vertexNormal;
        GLint texCoord;
    }_shaderAttributeLocations;


    GLfloat _sideLength = 1.0;
};


#endif //MP_BLOCK_HPP
