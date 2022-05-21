//
// Created by malte on 5/15/2022.
//

#include "SimpleMesh.h"

#include <iostream>

using namespace phyren;
using namespace std;

std::shared_ptr<SimpleMesh>
SimpleMesh::instance(std::vector<glm::vec3> verteces) {
    return shared_ptr<SimpleMesh>(new SimpleMesh(verteces));
}

SimpleMesh::SimpleMesh(std::vector<glm::vec3> vertices) : vertices(vertices) {
    // Generate the vertex array object
    glGenVertexArrays(1, &this->VAO);
    // Generate the buffers
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

void SimpleMesh::render() {
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, vertices.size());
    // Unbind the vertex array again by setting the VAO-current to 0
    glBindVertexArray(0);
}

unsigned int SimpleMesh::getVAO() const {
    return this->VAO;
}

/*
 * Override the rule of 5 so that we can use this without destroying the opengl objects on copy.
 */
SimpleMesh::SimpleMesh(SimpleMesh &&sm) {
    swap(this->VAO, sm.VAO);
    swap(this->VBO, sm.VBO);
}

SimpleMesh &SimpleMesh::operator=(SimpleMesh &&sm) {
    if (this != &sm) {
        // sm is not the current object
        swap(this->VAO, sm.VAO);
        swap(this->VBO, sm.VBO);
    }
    return *this;
}

SimpleMesh::~SimpleMesh() {
    if (VAO) {
        glDeleteVertexArrays(1, &VAO);
        VAO = 0;
    }
    if (VBO) {
        glDeleteBuffers(1, &VBO);
        VBO = 0;
    }
}