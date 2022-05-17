//
// Created by malte on 5/16/2022.
//

#include "Texture.h"
#include "stb_image.h"

#include <iostream>

using namespace std;
using namespace phyren;

std::shared_ptr<Texture> Texture::instance(const std::string &path) {
    return make_shared<Texture>(load(path));
}

Texture Texture::load(const std::string &path) {
    // Generate a texture buffer referenced by it's texture id
    unsigned int tid;
    glGenTextures(1, &tid);
    glBindTexture(GL_TEXTURE_2D, tid);
    Texture &&tex{tid};
    tex.setTextureParameter(GL_TEXTURE_WRAP_S, GL_REPEAT);
    tex.setTextureParameter(GL_TEXTURE_WRAP_T, GL_REPEAT);
    tex.setTextureParameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    tex.setTextureParameter(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    int width;
    int height;
    int nrChannels;
    // Load the texture from the file
    unsigned char *data{stbi_load(path.c_str(), &width, &height, &nrChannels, 0)};
    if (nullptr == data) {
        cerr << "[ERROR] The file " + path + " could not be load!" << endl;
    } else {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        // Generate the mip-maps for this file:
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    // Free the stb image memory
    stbi_image_free(data);
    return tex;
}

Texture Texture::load(const std::string &path, const std::string &uniform) {
    Texture &&temp{load(path)};
    temp.setUniformId(uniform);
    return temp;
}

unsigned int Texture::getTid() const {
    return this->tid;
}

const string &Texture::getUniformId() const {
    return this->shaderTextureUniform;
}

void Texture::setUniformId(const std::string &uniform) {
    this->shaderTextureUniform = uniform;
}

void Texture::setTextureParameter(GLenum pname, GLint param) const {
    glTexParameteri(GL_TEXTURE_2D, pname, param);
}

void Texture::bind() const {
    glBindTexture(GL_TEXTURE_2D, this->tid);
}

Texture::Texture(unsigned int tid, const string &name = std::string{""}) : shaderTextureUniform(name), tid(tid) {}

Texture::Texture(Texture &&t) {
    swap(this->tid, t.tid);
    swap(this->shaderTextureUniform, t.shaderTextureUniform);
}

Texture &Texture::operator=(Texture &&t) {
    if (this != &t) {
        swap(this->tid, t.tid);
        swap(this->shaderTextureUniform, t.shaderTextureUniform);
    }
    return *this;
}

Texture::~Texture() {
    glDeleteTextures(1, &this->tid);
}
