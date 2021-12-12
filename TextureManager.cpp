//
// Created by cmmeyers on 12/5/21.
//

#include "TextureManager.hpp"


TextureManager::TextureManager() {
}

GLuint TextureManager::getTextureHandle(std::string textureName) {
    auto handleItr = texHandles.find(textureName);
    assert(handleItr != texHandles.end());
    return(handleItr->second);
}

void TextureManager::LoadTextures(std::string path) {
    for (auto filename : textureFilenames){
        std::string fullPath = path + filename;
        GLuint texHandle = _loadAndRegisterTexture(fullPath.c_str());
        std::string parsedFileName = filename.substr(0, filename.find('.')); // dirt.jpg -> dirt
        texHandles.insert({parsedFileName,texHandle});
    }
}


GLuint TextureManager::_loadAndRegisterTexture(const char* FILENAME) {
    // our handle to the GPU
    GLuint textureHandle = 0;

    // enable setting to prevent image from being upside down
    stbi_set_flip_vertically_on_load(true);

    // will hold image parameters after load
    GLint imageWidth, imageHeight, imageChannels;
    // load image from file
    GLubyte* data = stbi_load( FILENAME, &imageWidth, &imageHeight, &imageChannels, 0);

    // if data was read from file
    if( data ) {
        const GLint STORAGE_TYPE = (imageChannels == 4 ? GL_RGBA : GL_RGB);

        // TODO #01
        glGenTextures(1, &textureHandle);

        // TODO #02
        glBindTexture(GL_TEXTURE_2D, textureHandle);

        // TODO #03
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        // TODO #04
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        // TODO #05
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        // gl texture wrap s , gl repeat
        // TODO #06
        glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        // TODO #07
        glTexImage2D(
                GL_TEXTURE_2D,
                0,
                STORAGE_TYPE,
                imageWidth,
                imageHeight,
                0,
                STORAGE_TYPE,
                GL_UNSIGNED_BYTE,
                data
        );

        fprintf( stdout, "[INFO]: %s texture map read in with handle %d\n", FILENAME, textureHandle);

        // release image memory from CPU - it now lives on the GPU
        // be free memory. You can fly free and be used in another Chrome tab
        stbi_image_free(data);
    } else {
        // load failed
        fprintf( stderr, "[ERROR]: Could not load texture map \"%s\"\n", FILENAME );
    }

    // return generated texture handle
    return textureHandle;
}


