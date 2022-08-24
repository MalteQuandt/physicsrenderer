//
// Created by malte on 5/16/2022.
//

#include "render/Vertex.h"

using namespace std;
using namespace phyren;

Vertex::Vertex(glm::vec3 pos, glm::vec3 normal, glm::vec2 texcoord) : position(pos), normal(normal),
                                                                      texCoords(texcoord) {}