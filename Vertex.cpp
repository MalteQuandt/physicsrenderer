//
// Created by malte on 5/16/2022.
//

#include "Vertex.h"

using namespace std;
using namespace phyren;

glm::vec3 &Vertex::getNormal() {
    return this->normal;
}

glm::vec3 &Vertex::getPosition() {
    return this->position;
}

glm::vec2 &Vertex::getTexCoords() {
    return this->getTexCoords();
}

Vertex::Vertex(glm::vec3 pos, glm::vec3 normal, glm::vec2 texcoord) : position(pos), normal(normal),
                                                                      texCoords(texcoord) {}