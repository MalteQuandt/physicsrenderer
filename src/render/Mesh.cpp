//
// Created by malte on 5/19/2022.
//

#include "render/Mesh.hpp"

#include <iostream>

using namespace phyren;
using namespace std;

Mesh Mesh::generateMesh(const std::vector<Vertex> &vertices,
                        const std::vector<unsigned int> &indices,
                        const std::vector<std::shared_ptr<Texture>> &textures) {
    return move(Mesh(vertices, indices, textures));
}

Mesh::Mesh(std::vector<Vertex> &&vertices, std::vector<unsigned int> &&indices,
           std::vector<std::shared_ptr<Texture>> &&textures) : vertices(vertices), indices(indices),
                                                               textures(textures) {
    setup();
}

Mesh::Mesh(const std::vector<Vertex> &vertices,
           const std::vector<unsigned int> &indices, const std::vector<std::shared_ptr<Texture>> &textures)
        : vertices(vertices), indices(indices), textures(textures) {
    setup();
}


std::shared_ptr<Mesh>
Mesh::shared_instance(const std::vector<Vertex> &vertices,
                      const std::vector<unsigned int> &indices,
                      const std::vector<std::shared_ptr<Texture>> &textures) {
    return make_shared<Mesh>(move(Mesh(vertices, indices, textures)));
}

void Mesh::setup() {
    // Generate the vertex array object
    glGenVertexArrays(1, &this->VAO);
    // Generate the vertex buffer object
    glGenBuffers(1, &this->VBO);
    // Generate the index buffer
    glGenBuffers(1, &this->EBO);

    // Make the vao the 'current' vao, so that it does not have to be referenced constantly
    glBindVertexArray(this->VAO);
    // Set the vao state in the following lines:
    // -----------------------------------------
    // Set the buffer vbo to be the 'current' array buffer
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    // Send the vertex data to the just-bound buffer on the gpu
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

    // Send the index data to the gpu
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

    // Set the attribute locations of the vertex data
    // Enable the vertex positions
    glEnableVertexAttribArray(0);
    // Set the locations and attributes of the vertex attribute data in the vertex data array
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) (0));
    // Enable the texture coordinates
    glEnableVertexAttribArray(1);
    unsigned long long offset{offsetof(Vertex, normal)};
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void *>(offset));

    // Enable the normal vectors
    glEnableVertexAttribArray(2);
    offset = offsetof(Vertex, texCoords);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void *>(offset));

    // Reset the vertex array
    glBindVertexArray(0);
}

void Mesh::render(std::shared_ptr<phyren::ShaderProgram> &shader) const {
    loadTextures(shader);
    renderElements();
}

void Mesh::renderElements() const {
    glBindVertexArray(this->VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    // Unbind this vertex
    glBindVertexArray(0);
    // Unbind the texture
    glActiveTexture(GL_TEXTURE0);

}

void Mesh::renderNI(std::shared_ptr<phyren::ShaderProgram> shader) const {
    loadTextures(shader);
    renderBuffer();
}

void Mesh::renderBuffer() const {
    glBindVertexArray(this->VAO);
    glDrawArrays(GL_TRIANGLES, 0, vertices.size());
    // Unbind this vertex
    glBindVertexArray(0);
    // Unbind the texture
    glActiveTexture(GL_TEXTURE0);
}

/*
 * Override the rule of 5 so that we can use this without destroying the opengl objects on copy.
 */
Mesh::Mesh(Mesh &&sm) noexcept {
    swap(this->VAO, sm.VAO);
    swap(this->VBO, sm.VBO);
    swap(this->EBO, sm.EBO);

    swap(this->indices, sm.indices);
    swap(this->vertices, sm.vertices);
    swap(this->textures, sm.textures);
}

Mesh &Mesh::operator=(Mesh &&sm) noexcept {
    if (this != &sm) {
        // sm is not the current object
        swap(this->VAO, sm.VAO);
        swap(this->VBO, sm.VBO);
        swap(this->EBO, sm.EBO);

        swap(this->indices, sm.indices);
        swap(this->vertices, sm.vertices);
        swap(this->textures, sm.textures);
    }
    return *this;
}

Mesh::~Mesh() {
    if (0 != VAO) {
        glDeleteVertexArrays(1, &this->VAO);
        VAO = 0;
    }
    if (0 != EBO) {
        glDeleteBuffers(1, &this->EBO);
    }
    if (0 != VBO) {
        glDeleteBuffers(1, &this->VBO);
        VBO = 0;
    }

}

void Mesh::loadTextures(std::shared_ptr<ShaderProgram> shader) const {
    unsigned int diffuse{0};
    unsigned int specular{0};
    // Check, if there actually are textures loaded:
    if (0 == textures.size()) {
        return;
    }
    // Send all the texture data to the gpu and 'link' it to their respective uniforms
    for (unsigned int i{0}; i < textures.size(); i++) {
        std::string num{};
        // Make the active texture
        glActiveTexture(GL_TEXTURE0 + 1 + i);
        // Get the reference id of the texture
        std::string name{textures.at(i)->getUniformId()};
        // Switch-like constructor to get the number-string for the texture type
        if ("texture_diffuse" == name) {
            diffuse++;
            num = to_string(diffuse);
        } else if ("texture_specular" == name) {
            specular++;
            num = to_string(specular);
        } else {
            cerr <<
                 "[ERROR] This texture name does not conform to any given naming convention, and can therefore not be loaded! " +
                 name << endl;
            continue;
        }
        // If there are other types, we can include them here later
        // Link together the texture to the material struct in the shader
        shader->set((name + num).c_str(), static_cast<int>(textures[i]->getTid()));
        textures[i]->bind();
    }
}