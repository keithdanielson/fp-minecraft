//
// Created by cmmeyers on 12/5/21.
//

#ifndef MP_TEXTUREMANAGER_HPP
#define MP_TEXTUREMANAGER_HPP

#include <CSCI441/objects.hpp>
#include <cmath>
#include <string>
#include "stb_image.h"
#include <iostream>
#include <map>
#include <vector>

class TextureManager {

public:
    TextureManager();
    void LoadTextures(std::string path); // textures/ ...
    GLuint getTextureHandle(std::string textureName);


private:
    /// \desc loads an image into CPU memory and registers it with the GPU
    /// \note sets the texture parameters and sends the data to the GPU
    /// \param FILENAME external image filename to load
    static GLuint _loadAndRegisterTexture(const char* FILENAME);

    static constexpr GLuint NUM_TEXTURES = 3;

    std::string textureFilenames[NUM_TEXTURES] = {
            "dirt.jpg",
            "stone.png",
            "water.jpg",
    };

    //  <dirt, handle>
    std::map<std::string, GLuint> texHandles;

};


#endif //MP_TEXTUREMANAGER_HPP
