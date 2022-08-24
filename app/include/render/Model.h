//
// Created by malte on 5/20/2022.
//

#ifndef PHYSICS_RENDERER_MODEL_H
#define PHYSICS_RENDERER_MODEL_H

#include <vector>
#include <memory>

#include "Mesh.hpp"
#include "ShaderProgram.h"

namespace phyren {
    /**
     * Model class that wraps around a model loaded from the assimp library
     */
    class Model final {
    public:

        /**
         * Render the model with a single, unique shader as-given
         *
         * @param shader the shader to render with
         */
        void render(std::shared_ptr<ShaderProgram> shader);

        /**
         * Render the model with a single, unique shader as-given and while not using
         * the index buffer.
         *
         * @param shader the shader to render with
         */
        void renderNI(std::shared_ptr<ShaderProgram> shader);
    private:
        /* All the mesh data for this given model */
        std::vector<Mesh> meshes{};

        /**
        * Generate a new Model from the set of mesh data in the constructor
        *
        * @param meshes the mesh data for this model
        */
        explicit Model(std::vector<Mesh>&& meshes);
        Model() = default;

        friend class ModelLoader;
    };
}


#endif //PHYSICS_RENDERER_MODEL_H
