//
// Created by cmmeyers on 12/5/21.
//

#ifndef MP_CHUNK_HPP
#define MP_CHUNK_HPP

#include <string>
#include <algorithm>
#include <vector>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "Block.hpp"
#include "TextureManager.hpp"


class Chunk {

public:
    Chunk();
    Chunk(Block *_block);
    ~Chunk();
    void generateChunk(glm::vec3 center);
    void drawChunk(glm::mat4 viewMtx, glm::mat4 projMtx);
    void deleteBlock(int x, int y, int z);
    void addBlock(int x, int y, int z);
    void setGenerationMode();


private:
    struct block_attributes {
        int x,y,z;
    };



    glm::mat4* modelMatrices;
    GLuint _instanceMatrix;

    Block *_block = nullptr;

    glm::vec3 _chunkCenter;
    std::vector<block_attributes> _blockInformation;

    void _transferChunkToGPU(std::vector<glm::mat4> blocks);
    void _regenerateChunk();
    static const int CHUNK_WIDTH = 128;
    static const int CHUNK_HEIGHT = 8;
    static const int BLOCK_SPACING = 1;
};


#endif //MP_CHUNK_HPP
