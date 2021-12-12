//
// Created by cmmeyers on 11/28/21.
//

#include "Block.hpp"
#include <iostream>
#include <CSCI441/objects.hpp>



Block::Block(){}



void Block::setupBlock(GLuint shaderProgramHandle, GLint projection, GLint view, GLint textureMap, GLint vPos, GLint vertexNormal, GLint texCoord){

    this->_shaderProgramHandle = shaderProgramHandle;

    _shaderAttributeLocations.vPos = vPos;
    _shaderAttributeLocations.vertexNormal = vertexNormal;
    _shaderAttributeLocations.texCoord = texCoord;
    _shaderUniformLocations.projection = projection;
    _shaderUniformLocations.view = view;
    _shaderUniformLocations.textureMap = textureMap;

    glGenVertexArrays(1, &_blockDescriptors._blockVAO);
    glBindVertexArray(_blockDescriptors._blockVAO);

    glGenBuffers( 1, &_blockDescriptors._blockVBO );
    glBindBuffer( GL_ARRAY_BUFFER, _blockDescriptors._blockVBO );

    GLfloat cornerPoint = _sideLength / 2.0f;

    GLfloat vertices[36][3] = {
            // Left Face
            {-cornerPoint, -cornerPoint, -cornerPoint}, {-cornerPoint, -cornerPoint,  cornerPoint}, {-cornerPoint,  cornerPoint, -cornerPoint},
            {-cornerPoint,  cornerPoint, -cornerPoint}, {-cornerPoint, -cornerPoint,  cornerPoint}, {-cornerPoint,  cornerPoint,  cornerPoint},
            // Right Face
            { cornerPoint,  cornerPoint,  cornerPoint}, { cornerPoint, -cornerPoint,  cornerPoint}, { cornerPoint,  cornerPoint, -cornerPoint},
            { cornerPoint,  cornerPoint, -cornerPoint}, { cornerPoint, -cornerPoint,  cornerPoint}, { cornerPoint, -cornerPoint, -cornerPoint},
            // Top Face
            {-cornerPoint,  cornerPoint, -cornerPoint}, {-cornerPoint,  cornerPoint,  cornerPoint}, { cornerPoint,  cornerPoint, -cornerPoint},
            { cornerPoint,  cornerPoint, -cornerPoint}, {-cornerPoint,  cornerPoint,  cornerPoint}, { cornerPoint,  cornerPoint,  cornerPoint},
            // Bottom Face
            { cornerPoint, -cornerPoint,  cornerPoint}, {-cornerPoint, -cornerPoint,  cornerPoint}, { cornerPoint, -cornerPoint, -cornerPoint},
            { cornerPoint, -cornerPoint, -cornerPoint}, {-cornerPoint, -cornerPoint,  cornerPoint}, {-cornerPoint, -cornerPoint, -cornerPoint},
            // Back Face
            { cornerPoint,  cornerPoint, -cornerPoint}, { cornerPoint, -cornerPoint, -cornerPoint}, {-cornerPoint,  cornerPoint, -cornerPoint},
            {-cornerPoint,  cornerPoint, -cornerPoint}, { cornerPoint, -cornerPoint, -cornerPoint}, {-cornerPoint, -cornerPoint, -cornerPoint},
            // Front Face
            {-cornerPoint, -cornerPoint,  cornerPoint}, { cornerPoint, -cornerPoint,  cornerPoint}, {-cornerPoint,  cornerPoint,  cornerPoint},
            {-cornerPoint,  cornerPoint,  cornerPoint}, { cornerPoint, -cornerPoint,  cornerPoint}, { cornerPoint,  cornerPoint,  cornerPoint}
    };
    GLfloat texCoords[36][2] = {
            // Left Face
            {0.0f, 0.0f}, {1.0f, 0.0f}, {0.0f, 1.0f},
            {0.0f, 1.0f}, {1.0f, 0.0f}, {1.0f, 1.0f},
            // Right Face
            {0.0f, 1.0f}, {0.0f, 0.0f}, {1.0f, 1.0f},
            {1.0f, 1.0f}, {0.0f, 0.0f}, {1.0f, 0.0f},
            // Top Face
            {1.0f, 0.0f}, {1.0f, 1.0f}, {0.0f, 0.0f},
            {0.0f, 0.0f}, {1.0f, 1.0f}, {0.0f, 1.0f},
            // Bottom Face
            {1.0f, 0.0f}, {1.0f, 1.0f}, {0.0f, 0.0f},
            {0.0f, 0.0f}, {1.0f, 1.0f}, {0.0f, 1.0f},
            // Back Face
            {0.0f, 1.0f}, {0.0f, 0.0f}, {1.0f, 1.0f},
            {1.0f, 1.0f}, {0.0f, 0.0f}, {1.0f, 0.0f},
            // Front Face
            {0.0f, 0.0f}, {1.0f, 0.0f}, {0.0f, 1.0f},
            {0.0f, 1.0f}, {1.0f, 0.0f}, {1.0f, 1.0f}
    };
    GLfloat normals[36][3] = {
            // Left Face
            {-1.0f, 0.0f, 0.0f}, {-1.0f, 0.0f, 0.0f}, {-1.0f, 0.0f, 0.0f},
            {-1.0f, 0.0f, 0.0f}, {-1.0f, 0.0f, 0.0f}, {-1.0f, 0.0f, 0.0f},
            // Right Face
            {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f, 0.0f},
            {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f, 0.0f},
            // Top Face
            {0.0f, 1.0f, 0.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 1.0f, 0.0f},
            {0.0f, 1.0f, 0.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 1.0f, 0.0f},
            // Bottom Face
            {0.0f, -1.0f, 0.0f}, {0.0f, -1.0f, 0.0f}, {0.0f, -1.0f, 0.0f},
            {0.0f, -1.0f, 0.0f}, {0.0f, -1.0f, 0.0f}, {0.0f, -1.0f, 0.0f},
            // Back Face
            {0.0f, 0.0f, -1.0f}, {0.0f, 0.0f, -1.0f}, {0.0f, 0.0f, -1.0f},
            {0.0f, 0.0f, -1.0f}, {0.0f, 0.0f, -1.0f}, {0.0f, 0.0f, -1.0f},
            // Front Face
            {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f},
            {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f}
    };

    glBufferData( GL_ARRAY_BUFFER, sizeof(GLfloat) * 36 * 8, NULL, GL_STATIC_DRAW );
    glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * 36 * 3, vertices );
    glBufferSubData( GL_ARRAY_BUFFER, sizeof(GLfloat) * 36 * 3, sizeof(GLfloat) * 36 * 3, normals );
    glBufferSubData( GL_ARRAY_BUFFER, sizeof(GLfloat) * 36 * 6, sizeof(GLfloat) * 36 * 2, texCoords );
}

GLuint Block::getBlockVAO() {
    return(this->_blockDescriptors._blockVAO);
}

void Block::cleanupBlock() {
    // TODO cleanup
}


void Block::drawBlock(GLint numBlocks, glm::mat4 viewMtx, glm::mat4 projMtx) {
    glUseProgram(_shaderProgramHandle);

    // Send over Uniforms
    // the Model Matrix is sent over as an instancedArray
    glProgramUniformMatrix4fv(_shaderProgramHandle, _shaderUniformLocations.projection, 1, GL_FALSE, &projMtx[0][0]);
    glProgramUniformMatrix4fv(_shaderProgramHandle, _shaderUniformLocations.view, 1, GL_FALSE, &viewMtx[0][0]);
    // bind vao, vbo
    glBindVertexArray(_blockDescriptors._blockVAO);
    glBindBuffer( GL_ARRAY_BUFFER,  _blockDescriptors._blockVBO);

    // bind attribute information

    // vertex pos
    glEnableVertexAttribArray( _shaderAttributeLocations.vPos );
    glVertexAttribPointer(_shaderAttributeLocations.vPos, 3, GL_FLOAT, GL_FALSE, 0, (void*)0 );

    // vertex normal
    glEnableVertexAttribArray( _shaderAttributeLocations.vertexNormal );
    glVertexAttribPointer( _shaderAttributeLocations.vertexNormal, 3, GL_FLOAT, GL_FALSE, 0, (void*)(sizeof(GLfloat)*36 *3) );

    // texture coordinates
    glEnableVertexAttribArray( _shaderAttributeLocations.texCoord );
    glVertexAttribPointer( _shaderAttributeLocations.texCoord, 2, GL_FLOAT, GL_FALSE, 0, (void*)(sizeof(GLfloat)*36 *6) );

    glBindTexture(GL_TEXTURE_2D, _shaderUniformLocations.textureMap);
    glDrawArraysInstanced( GL_TRIANGLES, 0, 36, numBlocks);
}

void Block::setTexture(std::string name, GLuint handle) {
    this->textureName = name;
    _shaderUniformLocations.textureMap = handle;
}