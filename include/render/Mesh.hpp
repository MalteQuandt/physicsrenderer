#pragma once

#include "Vertex.h"
#include "Texture.h"
#include "render/ShaderProgram.h"

#include <vector>
#include <memory>

namespace phyren {
    /**
     * Representation of mesh data
     */
    class Mesh final {
    public:
        static std::shared_ptr<Mesh>
        shared_instance(const std::vector<Vertex> &vertices,
                        const std::vector<unsigned int> &indices = std::vector<unsigned int>(
                                0),
                        const std::vector<std::shared_ptr<Texture>> &textures = std::vector<std::shared_ptr<Texture>>(
                                0));

        static Mesh generateMesh(const std::vector<Vertex> &vertices,
                                 const std::vector<unsigned int> &indices = std::vector<unsigned int>(
                                         0),
                                 const std::vector<std::shared_ptr<Texture>> &textures = std::vector<std::shared_ptr<Texture>>(
                                         0));

        /**
        * @brief Construct a new Mesh object
        *
        * @param vertices the vertices of this mesh object
        * @param indices  the indices/the order in which the vertices are rendered
        * @param textures the textures for the shader
        */
        explicit Mesh(const std::vector<Vertex> &vertices,
                      const std::vector<unsigned int> &indices, const std::vector<std::shared_ptr<Texture>> &textures);

        /**
        * @brief Construct a new Mesh object by moving the vector data inside it
        *
        * @param vertices the vertices of this mesh object
        * @param indices  the indices/the order in which the vertices are rendered
        * @param textures the textures for the shader
        */
        explicit Mesh(std::vector<Vertex>&& vertices,
                      std::vector<unsigned int>&& indices, std::vector<std::shared_ptr<Texture>>&& textures);
        /**
         * Render this mesh using buffer objects
         *
         * @param shader the shader to render with
         */
        void render(std::shared_ptr<phyren::ShaderProgram> &shader) const;

        /**
         * Render this mesh using the passed shader program without utilizing the index list
         *
         * @param shader the shader to use for rendering
         */
        void renderNI(std::shared_ptr<phyren::ShaderProgram> shader) const;

        /* Delete copy operations because creating a copy of this is nonsensical */
        Mesh(const Mesh &) = delete;

        Mesh &operator=(const Mesh &) = delete;

        /* Implementation of move-semantics */
        Mesh(Mesh &&) noexcept;

        Mesh &operator=(Mesh &&) noexcept;

        /* Destroy all the mesh data on object-destruction */
        ~Mesh();

    private:
        // Vertex data for this mesh
        std::vector<Vertex> vertices{};
        // Index data
        std::vector<unsigned int> indices{};
        // Texture data
        std::vector<std::shared_ptr<Texture>> textures{};

        // reference value to the opengl objects
        unsigned int VAO{0};
        unsigned int EBO{0};
        unsigned int VBO{0};

        /**
         * Generate this mesh from the input data and setup the data in the opengl context
         */
        void setup();

        /**
        * Render the mesh using the elements buffer
        */
        void renderElements() const;

        /**
         * Render the mesh using the array buffer without indices
         */
        void renderBuffer() const;

        /**
         * Load the textures into the shader/gpu
         *
         * @param shader the shader used for rendering
         */
        void loadTextures(std::shared_ptr<ShaderProgram> shader) const;
    };
}