//
// Created by malte on 5/15/2022.
//

#ifndef PHYSICS_RENDERER_SIMPLE_MESH_H
#define PHYSICS_RENDERER_SIMPLE_MESH_H

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "glm/vec3.hpp"

#include <vector>
#include <memory>

namespace phyren {
    /** SimpleMesh class
     */
    class SimpleMesh {
    public:
        static std::shared_ptr<SimpleMesh>
        instance(std::vector<glm::vec3> verteces);

        /**
         * Render this SimpleMesh to the screen as-given without taking the indices into account
         */
        virtual void render();

        /**
         * Delete the associated VAO and EBO
         */
        virtual ~SimpleMesh();

        virtual unsigned int getVAO() const;
        /*
         * Override the rule of 5
         */
        explicit SimpleMesh(SimpleMesh &&);
        SimpleMesh &operator=(SimpleMesh &&);
        // Copying this data type does not make sense, thus we prohibit it
        explicit SimpleMesh(const SimpleMesh &) = delete;
        SimpleMesh &operator=(const SimpleMesh &) = delete;

    protected:
        explicit SimpleMesh();
    private:
        // Vector of vertex data
        std::vector<glm::vec3> vertices;
        // The reference value of the vertex array buffer, thin state wrapper around vao and certain api calls
        unsigned int VAO;
        // The reference value of the buffer containing all the vertex data
        unsigned int VBO;
        /**
         * Create a new SimpleMesh flyweight object that consists of these vertices
         *
         * @param vertices the vertices of this SimpleMesh
         */
        explicit SimpleMesh(std::vector<glm::vec3> vertices);
    };
}


#endif //PHYSICS_RENDERER_SimpleMesh_H
