//
// Created by malte on 5/15/2022.
//

#include "render/Mesh.h"

#include <iostream>

using namespace phyren;
using namespace std;

std::shared_ptr<Mesh>
Mesh::instance(std::vector<glm::vec3> verteces) {
    return shared_ptr<Mesh>(new Mesh(verteces));
}

Mesh::Mesh(std::vector<glm::vec3> vertices) : vertices(vertices) {
    // Generate the vertex array object
    glGenVertexArrays(1, &this->VAO);
    // Gerneate the buffers
    glGenBuffers(1, &this->VBO);

    // Make VAO the 'current' vertex array object
    glBindVertexArray(this->VAO);
    glBindBuffer(GL_ARRAY_BUFFER, this->VAO);
    // Send the data to the GPU
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

    // Vertex position attribute
    glEnableVertexAttribArray(0);
    // Set the offset of the vertex attribute. There is no offset here, as this is the first and only attrib
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void *) 0);
    // Unbind the vertex array
    glBindVertexArray(0);
}

void Mesh::render() {
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, vertices.size());
    // Unbind the vertex array again by setting the VAO-current to 0
    glBindVertexArray(0);
}

/*
 * Override the rule of 5 so that we can use this without destroying the opengl objects on copy.
 */
Mesh::Mesh(Mesh &&sm) {
    swap(this->VAO, sm.VAO);
    swap(this->VBO, sm.VBO);
}

Mesh &Mesh::operator=(Mesh &&sm) {
    if (this != &sm) {
        // sm is not the current object
        swap(this->VAO, sm.VAO);
        swap(this->VBO, sm.VBO);
    }
    return *this;
}

Mesh::~Mesh() {
    if (VAO) {
        glDeleteVertexArrays(1, &VAO);
        VAO = 0;
    }
    if (VBO) {
        glDeleteBuffers(1, &VBO);
        VBO = 0;
    }
}