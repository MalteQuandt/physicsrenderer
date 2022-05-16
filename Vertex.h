//
// Created by malte on 5/16/2022.
//

#ifndef PHYSICS_RENDERER_VERTEX_H
#define PHYSICS_RENDERER_VERTEX_H

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

namespace phyren {
    /**
     * Wrapper class for all the vertex attribute values
     */
    class Vertex {
    public:
        /**
         * Generate a simple vertex
         */
        explicit Vertex(glm::vec3 pos, glm::vec3 normal, glm::vec2 texcoord);

        // Getter
        // ------
        glm::vec2 &getTexCoords();

        glm::vec3 &getNormal();

        glm::vec3 &getPosition();

    private:
        // Vertex position data
        glm::vec3 position{};
        // Normal vector for each vertex
        glm::vec3 normal{};
        // Texture coordiantes for this vertex
        glm::vec2 texCoords{};
    };
}


#endif //PHYSICS_RENDERER_VERTEX_H
