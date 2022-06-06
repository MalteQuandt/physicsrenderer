//
// Created by malte on 6/6/2022.
//

#include "Line.h"

using namespace std;
using namespace phyren;

std::shared_ptr<Line> Line::generate(std::vector<glm::vec3> points) {
    return make_shared<Line>(move(Line(points)));
}

Line::Line(std::vector<glm::vec3> points) : points(points) {
    setup(points);
}

void Line::draw(std::shared_ptr<ShaderProgram> shader) {
    shader->use();
    glBindVertexArray(this->VAO);
    glDrawArrays(GL_LINES, 0, points.size());
    glBindVertexArray(0);
}

Line &Line::operator=(Line &&l) {
    if (this != &l) {
        swap(this->VBO, l.VBO);
        swap(this->VAO, l.VAO);
        swap(l.points, this->points);
    }
    return *this;
}

Line::Line(Line &&l) {
    std::swap(l.VBO, this->VBO);
    std::swap(l.VAO, this->VAO);
    std::swap(l.points, this->points);
}

void Line::setup(std::vector<glm::vec3> points) {
    // Generate the buffers of the current opengl context
    glGenVertexArrays(1, &this->VAO);
    glGenBuffers(1, &this->VBO);

    glBindVertexArray(this->VAO);
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(this->points.size() * sizeof(glm::vec3)), &points[0],
                 GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void *) (0));
    // Unbind the vao
    glBindVertexArray(0);
}