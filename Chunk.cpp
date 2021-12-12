//
// Created by cmmeyers on 12/5/21.
//

#include <iostream>
#include "Chunk.hpp"


Chunk::Chunk(Block *_block) {
    this->_block = _block;
}

Chunk::~Chunk() {
    delete(_block);
}


void Chunk::deleteBlock(int x, int y, int z) {
    // iterate through _blockInformation to find block w/ matching cords (x + y + z) = index
    // if a _blockInformation is found we can delete that object
    for (int i = 0; i < _blockInformation.size(); ++i){
        auto block_attr = _blockInformation[i];
        if (block_attr.x == x && block_attr.y == y && block_attr.z == z){
            _blockInformation.erase(_blockInformation.begin() + i);
            std::cout << "Deleting block" << std::endl;
            return;
        }
    }
    std::cerr << "Could not find block in chunk" << std::endl;

    _regenerateChunk();
}

void Chunk::addBlock(int x, int y, int z) {
    // iterate through _blockInformation to find block w/ matching cords (x + y + z) = index
    // figure out the orientation of block viewed
    // add _block and _blockInformation at corresponding index
    // regenerate the chunk
}


void Chunk::_regenerateChunk() {

    glm::mat4 chunkCenterModel = glm::translate(glm::mat4(1.0f),_chunkCenter);
    std::vector<glm::mat4> blockModelMatrices;

    // loop through block information and reconstruct array of model matrices
    for (auto block_attr : _blockInformation){
        blockModelMatrices.emplace_back(glm::translate(chunkCenterModel, glm::vec3(block_attr.x, block_attr.y, block_attr.z)));
    }
    _transferChunkToGPU(blockModelMatrices);
}



void Chunk::generateChunk(glm::vec3 center) {
    this->_chunkCenter = center;

    glm::mat4 chunkCenterModel = glm::translate(glm::mat4(1.0f),center);
    std::vector<glm::mat4> blockModelMatrices;

    // iterate through the chunk and place blocks
    // since the array is 1d keep a block information struct to help us index back in
    for (int x = (int)center.x - CHUNK_WIDTH / 2; x < CHUNK_WIDTH / 2; ++x){
        for (int z = (int)center.x - CHUNK_WIDTH / 2; z < CHUNK_WIDTH / 2; ++z){
            for (int y = 0; y < CHUNK_HEIGHT; ++y){
                glm::mat4 model = glm::translate(chunkCenterModel, glm::vec3(x,y,z));
                blockModelMatrices.push_back(model);
                _blockInformation.push_back({x,y,z});
            }
        }
    }

    _transferChunkToGPU(blockModelMatrices);
}

void Chunk::_transferChunkToGPU(std::vector<glm::mat4> blocks) {
    // configured instanced array to represent those modelMatrices
    glGenBuffers(1, &_instanceMatrix);
    glBindBuffer(GL_ARRAY_BUFFER, _instanceMatrix);
    // transfer the entire array
    glBufferData(GL_ARRAY_BUFFER, CHUNK_WIDTH * CHUNK_WIDTH * CHUNK_HEIGHT * sizeof(glm::mat4), &blocks[0], GL_STATIC_DRAW);

    glBindVertexArray(_block->getBlockVAO());
    // vertex attributes
    std::size_t vec4Size = sizeof(glm::vec4);
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)0);
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)(1 * vec4Size));
    glEnableVertexAttribArray(5);
    glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)(2 * vec4Size));
    glEnableVertexAttribArray(6);
    glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)(3 * vec4Size));
    glVertexAttribDivisor(3, 1);
    glVertexAttribDivisor(4, 1);
    glVertexAttribDivisor(5, 1);
    glVertexAttribDivisor(6, 1);
    // reset
    glBindVertexArray(0);
}


void Chunk::drawChunk(glm::mat4 viewMtx, glm::mat4 projMtx) {
    int amount = CHUNK_WIDTH;
    _block->drawBlock(CHUNK_WIDTH * CHUNK_WIDTH * CHUNK_HEIGHT, viewMtx, projMtx);
    glBindVertexArray(0);
    std::cout << "63 : " << glGetError() << std::endl;
}



