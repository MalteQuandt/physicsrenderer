//
// Created by malte on 5/16/2022.
//

#ifndef PHYSICS_RENDERER_VERTEX_H
#define PHYSICS_RENDERER_VERTEX_H

#include "glm/vec3.hpp"
#include "glm/vec2.hpp"

namespace phyren {
    /**
     * Wrapper class for all the per-vertex attribute values
     */
    class Vertex {
    public:
        /**
         * Generate a simple vertex
         */
        explicit Vertex(glm::vec3 pos, glm::vec3 normal, glm::vec2 texcoord);
        // Enable the default constructor
        explicit Vertex() = default;
        // Vertex position data
        const glm::vec3 position{};
        // Normal vector for each vertex
        const glm::vec3 normal{};
        // Texture coordiantes for this vertex
        const glm::vec2 texCoords{};
    };
}


#endif //PHYSICS_RENDERER_VERTEX_H
