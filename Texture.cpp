//
// Created by malte on 5/16/2022.
//

#include "Texture.h"

unsigned int Texture::getTid() const {
    return this->tid;
}

const std::string &Texture::getUniformId() const {
    return this->shaderTextureUniform;

}

Texture::Texture(const std::string &name, unsigned int id) : shaderTextureUniform(name), tid(tid) {

}