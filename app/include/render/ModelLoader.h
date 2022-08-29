#pragma once

#include <map>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <render/Model.h>
#include <render/Line.h>

namespace phyren {
    enum class PreModelType {
        CUBE,
        SPHERE
    };

    /**
     * Loader class that is able to utilize the assimp model
     * loading capabilitites and create mesh objects from them.
     */
    class ModelLoader final {
    public:
        /**
         * Get the singleton modelloader instance
         */
        static phyren::ModelLoader &getInstance();

        /**
         * @brief   Load the path into assimp and generate a new model object from the assimp data
         *
         * @param   path the path to the model to be loaded
         *
         * @return  the model created from the assimp data
         */
        std::shared_ptr<Model> load(const std::string &path);

        /**
         * @brief   Makes the user choose to load a model from a collection of pre-allocated default models
         * @param   type the type of the previously calculated model to return
         */
        std::shared_ptr<Model> getModel(PreModelType type);

        // Make the singleton un-copyable
        ModelLoader(const ModelLoader & loader) = delete;
        ModelLoader& operator=(ModelLoader&&) = delete;

    private:
        // The directory this loader currently operates on
        std::string directory{};
        // The textures that are already in memory
        std::vector<std::shared_ptr<Texture>> texturesLoaded{};
        // The precalculated model types, initially empty, but get's filled as more items get requestet.
        // Therefore this is another example of the flywheight pattern
        std::map<std::string, std::shared_ptr<Model>> models{};

        /**
         * @brief   Create a new model loader
         */
        explicit ModelLoader() = default;

        /**
         * @brief   Recursively process the nodes in the assimp scene and convert them into the user-defined
         *          model data structure
         *
         * @param   node the node that this function call processes
         * @param   scene the scene on which this node is bound
         * @param   model the model on which we operate
         * @param   directory the directory we are loading
         */
        void
        processNode(std::shared_ptr<Model> model, aiNode *node, const aiScene *scene);

        /**
         * @brief   Convert the mesh data loaded from assimp in a given mesh into the mesh data structure that was user
         *          defined in this application.
         *
         * @param   model the model we are working on
         * @param   mesh the mesh we are transforming currently
         * @param   scene the scene object we are working on
         * @param   directory the directory we are loading
         *
         * @return  a new mesh item
         */
        Mesh
        processMesh(std::shared_ptr<Model> model, aiMesh *mesh, const aiScene *scene);

        /**
         * Fetch the texture data for a given mesh form the file system and connect it with the current mesh
         *
         * @param model the model object we are working on/creating
         * @param mat the material for the currently worked-on mesh
         * @param type the material type that we are loading with this function
         * @param typeName the name of the type, useful for the shader and the linking process with it
         * @param directory the directory we are loading
         *
         * @return a vector of all the textures that are used for this mesh
         */
        std::vector<std::shared_ptr<Texture>>
        loadTextures(std::shared_ptr<Model> model, aiMaterial *mat,
                     aiTextureType type, const std::string &typeName);

        // Private Helper Functions
        // ------------------------
        /**
        * Helper function to grant the access to the cube flyweight,
        * or to create it if it does not exist already
        *
        * @return the cube flyweight
        */
        std::shared_ptr<Model> getCube();
        /**
         * Helper function to grant the access to the sphere flyweight
         * or to create it (if it does not exists already)
         * @return the sphere either object created or fetched from the map
         */
        std::shared_ptr<Model> getSphere();
    };
}