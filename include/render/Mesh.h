//
// Created by malte on 5/15/2022.
//

#ifndef PHYSICS_RENDERER_MESH_H
#define PHYSICS_RENDERER_MESH_H

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "glm/vec3.hpp"

#include <vector>
#include <memory>

namespace phyren {
    /** Mesh class
     */
    class Mesh {
    public:
        static std::shared_ptr<Mesh>
        instance(std::vector<glm::vec3> verteces);

        /**
         * Render this mesh to the screen as-given without taking the indices into account
         */
        virtual void render();

        /**
         * Delete the associated VAO and EBO
         */
        virtual ~Mesh();

        virtual unsigned int getVAO() const;
        /*
         * Override the rule of 5
         */
        explicit Mesh(Mesh &&);
        Mesh &operator=(Mesh &&);
        // Copying this data type does not make sense, thus we prohibit it
        explicit Mesh(const Mesh &) = delete;
        Mesh &operator=(const Mesh &) = delete;

    protected:
        explicit Mesh();
    private:
        // Vector of vertex data
        std::vector<glm::vec3> vertices;
        // The reference value of the vertex array buffer, thin state wrapper around vao and certain api calls
        unsigned int VAO;
        // The reference value of the buffer containing all the vertex data
        unsigned int VBO;
        /**
         * Create a new mesh flyweight object that consists of these vertices
         *
         * @param vertices the vertices of this mesh
         */
        explicit Mesh(std::vector<glm::vec3> vertices);
    };
}


#endif //PHYSICS_RENDERER_MESH_H
