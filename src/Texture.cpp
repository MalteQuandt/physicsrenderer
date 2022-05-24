//
// Created by malte on 5/16/2022.
//

#include "Texture.h"
#include "stb_image.h"

#include <iostream>

using namespace std;
using namespace phyren;

std::shared_ptr<Texture> Texture::loadShared(const std::string &path, const std::string& typeName) {
    return make_shared<Texture>(load(path, typeName));
}

Texture::Texture(unsigned int tid) : tid(tid) {
}

Texture Texture::load(const std::string &path, const std::string& typeName) {
    // Generate a texture buffer referenced by it's texture id
    unsigned int tid;
    glGenTextures(1, &tid);
    glBindTexture(GL_TEXTURE_2D, tid);
    Texture tex{tid};
    tex.setPath(path);
    tex.setUniformId(typeName);
    // Set the parameters for the texture, meaning that the s axis will repeat for tex coords outside of the [0,1] range etc
    tex.setTextureParameter(GL_TEXTURE_WRAP_S, GL_REPEAT);
    tex.setTextureParameter(GL_TEXTURE_WRAP_T, GL_REPEAT);
    tex.setTextureParameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    tex.setTextureParameter(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // Storage containers for the texture
    int width;
    int height;
    int nrChannels;
    // Load the texture from the file
    unsigned char *data{stbi_load(path.c_str(), &width, &height, &nrChannels, 0)};
    if (nullptr == data) {
        cerr << "[ERROR] The file " + path + " could not be loaded!" << endl;
    } else {
        // Specify the format for the just-loaded texture
        GLenum format{};
        switch (nrChannels) {
            case 1:
                format = GL_RED;
                break;
            case 3:
                format = GL_RGB;
                break;
            case 4:
                format = GL_RGBA;
                break;
        }
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        // Generate the mip-maps for this file:
        glGenerateMipmap(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
    // Set the texture parameters
    tex.setWidth(width);
    tex.setHeight(height);
    tex.setNrChannels(nrChannels);
    // Free the stb image memory
    stbi_image_free(data);
    return std::move(tex);
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

void Texture::setPath(const std::string &path) {
    this->path = path;
}

std::string &Texture::getPath() {
    return this->path;
}

void Texture::bind() const {
    glBindTexture(GL_TEXTURE_2D, this->tid);
}

Texture::Texture(unsigned int tid, const string &name = std::string{""}) : shaderTextureUniform(name), tid(tid) {}

Texture::Texture(Texture &&t) noexcept : width(t.width), height(t.height), nrChannels(t.nrChannels) {
    swap(this->tid, t.tid);
    swap(this->shaderTextureUniform, t.shaderTextureUniform);
    swap(this->path, t.path);

}

Texture &Texture::operator=(Texture &&t) noexcept {
    if (this != &t) {
        swap(this->tid, t.tid);
        swap(this->shaderTextureUniform, t.shaderTextureUniform);
        swap(this->path, t.path);
        swap(this->width, t.width);
        swap(this->height, t.height);
        swap(this->nrChannels, t.nrChannels);
    }
    return *this;
}

Texture::~Texture() {
    glDeleteTextures(1, &this->tid);
}

int Texture::getWidth() const {
    return width;
}

void Texture::setWidth(int width) {
    Texture::width = width;
}

int Texture::getHeight() const {
    return height;
}

void Texture::setHeight(int height) {
    Texture::height = height;
}

int Texture::getNrChannels() const {
    return nrChannels;
}

void Texture::setNrChannels(int nrChannels) {
    Texture::nrChannels = nrChannels;
}
