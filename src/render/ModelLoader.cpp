//
// Created by malte on 5/20/2022.
//

#include <iostream>
#include <numeric>

#include "render/ModelLoader.h"

using namespace phyren;
using namespace std;
using namespace Assimp;


ModelLoader &ModelLoader::getInstance() {
    static ModelLoader loader{};
    return loader;
}

std::shared_ptr<Model> ModelLoader::load(const std::string &path) {
    // Extract the directory from the path
    this->directory = path.substr(0, path.find_last_of('\\'));
    // Clear the data from the last read
    this->texturesLoaded.clear();

    Importer importer{};
    // Options that are applied to the model after loading it
    // Essentially:
    // -Triangulate: If gl primitives in object are not all triangles, triangulate them
    // -FlipUV's: Flip the y-axis for the textures, as opengl textures are flipped on that axis
    // -GenNormals: If normal vectors do not exist, create them
    const unsigned int postProcessingOptions{aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenSmoothNormals};
    // Load the model from the given directory
    const aiScene *scene{importer.ReadFile(path, postProcessingOptions)};
    // Check if the scene and root node exists, and if the incomplete flag is set
    if (!scene || (AI_SCENE_FLAGS_INCOMPLETE & scene->mFlags) || !scene->mRootNode) {
        cerr << "[ERROR] The model in the directory " << path << " could not be loaded!" << endl;
        cerr << "[ERROR]: " << importer.GetErrorString() << endl;
        return nullptr;
    }
    // Set up the model storage unit
    std::shared_ptr<Model> model{make_shared<Model>(Model{})};
    // Recursively process the nodes, starting form the root node
    processNode(model, scene->mRootNode, scene);
    return model;
}

void ModelLoader::processNode(std::shared_ptr<Model> model, aiNode *node,
                              const aiScene *scene) {
    // Process this node's internal structure/it's mesh
    for (unsigned int i = 0; i < node->mNumMeshes; i++) {
        // Fetch the mesh data
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
        model->meshes.push_back(processMesh(model, mesh, scene));
    }
    // And once we are done with this node, we process the child nodes
    for (unsigned int i = 0; i < node->mNumChildren; i++) {
        processNode(model, node->mChildren[i], scene);
    }
}

Mesh ModelLoader::processMesh(std::shared_ptr<Model> model, aiMesh *mesh,
                              const aiScene *scene) {
    vector<Vertex> vertices{};
    vector<unsigned int> indices{};
    vector<shared_ptr<Texture>> textures{};
    // Loop over all the vertices of this node and process them
    for (unsigned int i{0}; i < mesh->mNumVertices; i++) {
        // Fetch the position vector
        glm::vec3 pos = {
                mesh->mVertices[i].x,
                mesh->mVertices[i].y,
                mesh->mVertices[i].z
        };
        glm::vec3 norm{0.0f, 0.0f, 0.0f};
        // Check if the mesh contains normal vectors:
        if (mesh->HasNormals()) {
            // Fetch the normal vector
            norm = glm::vec3{
                    mesh->mNormals[i].x,
                    mesh->mNormals[i].y,
                    mesh->mNormals[i].z
            };
        }
        glm::vec2 tex{0.0f, 0.0f};
        // Check, if this mesh contains texture information
        if (mesh->mTextureCoords[0]) {
            tex = glm::vec2{mesh->mTextureCoords[0][i].x,
                            mesh->mTextureCoords[0][i].y};
        }

        // Push all that data together
        vertices.push_back(Vertex{pos, norm, tex});
    }
    // Process the index data
    for (unsigned int i{0}; i < mesh->mNumFaces; i++) {
        aiFace face{mesh->mFaces[i]};
        // retrieve all indices of the face and store them in the indices vector
        for (unsigned int j{0}; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }
    // Process the material data
    if (mesh->mMaterialIndex >= 0) {
        // Get the material from the material index of this node
        aiMaterial *material{scene->mMaterials[mesh->mMaterialIndex]};
        // Load the diffuse texture maps
        std::vector<std::shared_ptr<Texture>> diffuse{
                loadTextures(model, material, aiTextureType_DIFFUSE, "texture_diffuse")};
        // Append/Insert the diffuse textures into the textures vector
        textures.insert(textures.end(), diffuse.begin(), diffuse.end());
        // Load the specular texture maps
        std::vector<std::shared_ptr<Texture>> specular{
                loadTextures(model, material, aiTextureType_SPECULAR, "texture_specular")};
        // Append the textures into the textures vector
        textures.insert(textures.end(), specular.begin(), specular.end());
    }
    // Create the mesh instance
    return move(Mesh(move(vertices), move(indices), move(textures)));
}

std::vector<std::shared_ptr<Texture>>
ModelLoader::loadTextures(std::shared_ptr<Model> model, aiMaterial *mat,
                          aiTextureType type, const std::string &typeName) {
    vector<std::shared_ptr<Texture>> textures{};
    // Get the textures amount for the given material
    for (unsigned int i{0}; i < mat->GetTextureCount(type); i++) {
        // Path of the texture file
        aiString path{};
        // Get the texture path for the given texture
        mat->GetTexture(type, i, &path);
        bool skip{false};
        // Check if this texture has been loaded already
        for (unsigned int j{0}; j < this->texturesLoaded.size(); j++) {
            // If the texture is already loaded:
            if (this->texturesLoaded[j]->getPath() == std::string(path.C_Str())) {
                textures.push_back(texturesLoaded[j]);
                skip = true;
                break;
            }
        }
        // The texture was not loaded
        if (!skip) {
            // Generate the texture
            std::shared_ptr<Texture> tex{make_shared<Texture>(Texture::load(directory + "\\" + path.C_Str()))};
            tex->setUniformId(typeName);
            textures.push_back(tex);
        }
    }
    return textures;
}

std::shared_ptr<Model> ModelLoader::getModel(PreModelType type) {
    switch (type) {
        case PreModelType::CUBE:
            return getCube();
        case PreModelType::SPHERE:
            return getSphere();
        default:
            cerr << "[ERROR] There is no model of the type value " + static_cast<const unsigned int>(type) << endl;
            return nullptr;
    }
}
// Private helper functions
// ------------------------
/**
 * Helper function to grant the access to the cube flywheight,
 * or to create it if it does not exist already
 *
 * @return the cube flyweight
 */
std::shared_ptr<Model> ModelLoader::getCube() {

    // Check if this object has already been created or not
    if (this->models.contains(PreModelType::CUBE)) {
        // Contains the item, thus we return it
        return this->models.at(PreModelType::CUBE);
    } else {
        // Vertices for the vertex buffer
        const vector<Vertex> cubeVertices{
                Vertex{glm::vec3{-0.5f, -0.5f, -0.5f},
                       glm::vec3{0.0f, 0.0f, 0.0f},
                       glm::vec2{0.0f, 0.0f}},
                Vertex{glm::vec3{0.5f, -0.5f, -0.5f},
                       glm::vec3{0.0f, 0.0f, 0.0f},
                       glm::vec2{1.0f, 0.0f}},
                Vertex{glm::vec3{0.5f, 0.5f, -0.5f},
                       glm::vec3{0.0f, 0.0f, 0.0f},
                       glm::vec2{1.0f, 1.0f}},
                Vertex{glm::vec3{0.5f, 0.5f, -0.5f},
                       glm::vec3{0.0f, 0.0f, 0.0f},
                       glm::vec2{1.0f, 1.0f}},
                Vertex{glm::vec3{-0.5f, 0.5f, -0.5f},
                       glm::vec3{0.0f, 0.0f, 0.0f},
                       glm::vec2{0.0f, 1.0f}},
                Vertex{glm::vec3{-0.5f, -0.5f, -0.5f},
                       glm::vec3{0.0f, 0.0f, 0.0f},
                       glm::vec2{0.0f, 0.0f}},

                Vertex{glm::vec3{-0.5f, -0.5f, 0.5f},
                       glm::vec3{0.0f, 0.0f, 0.0f},
                       glm::vec2{0.0f, 0.0f}},
                Vertex{glm::vec3{0.5f, -0.5f, 0.5f},
                       glm::vec3{0.0f, 0.0f, 0.0f},
                       glm::vec2{1.0f, 0.0f}},
                Vertex{glm::vec3{0.5f, 0.5f, 0.5f},
                       glm::vec3{0.0f, 0.0f, 0.0f},
                       glm::vec2{1.0f, 1.0f}},
                Vertex{glm::vec3{0.5f, 0.5f, 0.5f},
                       glm::vec3{0.0f, 0.0f, 0.0f},
                       glm::vec2{1.0f, 1.0f}},
                Vertex{glm::vec3{-0.5f, 0.5f, 0.5f},
                       glm::vec3{0.0f, 0.0f, 0.0f},
                       glm::vec2{0.0f, 1.0f}},
                Vertex{glm::vec3{-0.5f, -0.5f, 0.5f},
                       glm::vec3{0.0f, 0.0f, 0.0f},
                       glm::vec2{0.0f, 0.0f}},

                Vertex{glm::vec3{-0.5f, 0.5f, 0.5f},
                       glm::vec3{0.0f, 0.0f, 0.0f},
                       glm::vec2{1.0f, 0.0f}},
                Vertex{glm::vec3{-0.5f, 0.5f, -0.5f},
                       glm::vec3{0.0f, 0.0f, 0.0f},
                       glm::vec2{1.0f, 1.0f}},
                Vertex{glm::vec3{-0.5f, -0.5f, -0.5f},
                       glm::vec3{0.0f, 0.0f, 0.0f},
                       glm::vec2{0.0f, 1.0f}},
                Vertex{glm::vec3{-0.5f, -0.5f, -0.5f},
                       glm::vec3{0.0f, 0.0f, 0.0f},
                       glm::vec2{0.0f, 1.0f}},
                Vertex{glm::vec3{-0.5f, -0.5f, 0.5f},
                       glm::vec3{0.0f, 0.0f, 0.0f},
                       glm::vec2{0.0f, 0.0f}},
                Vertex{glm::vec3{-0.5f, 0.5f, 0.5f},
                       glm::vec3{0.0f, 0.0f, 0.0f},
                       glm::vec2{1.0f, 0.0f}},

                Vertex{glm::vec3{0.5f, 0.5f, 0.5f},
                       glm::vec3{0.0f, 0.0f, 0.0f},
                       glm::vec2{1.0f, 0.0f}},
                Vertex{glm::vec3{0.5f, 0.5f, -0.5f},
                       glm::vec3{0.0f, 0.0f, 0.0f},
                       glm::vec2{1.0f, 1.0f}},
                Vertex{glm::vec3{0.5f, -0.5f, -0.5f},
                       glm::vec3{0.0f, 0.0f, 0.0f},
                       glm::vec2{0.0f, 1.0f}},
                Vertex{glm::vec3{0.5f, -0.5f, -0.5f},
                       glm::vec3{0.0f, 0.0f, 0.0f},
                       glm::vec2{0.0f, 1.0f}},
                Vertex{glm::vec3{0.5f, -0.5f, 0.5f},
                       glm::vec3{0.0f, 0.0f, 0.0f},
                       glm::vec2{0.0f, 0.0f}},
                Vertex{glm::vec3{0.5f, 0.5f, 0.5f},
                       glm::vec3{0.0f, 0.0f, 0.0f},
                       glm::vec2{1.0f, 0.0f}},

                Vertex{glm::vec3{-0.5f, -0.5f, -0.5f},
                       glm::vec3{0.0f, 0.0f, 0.0f},
                       glm::vec2{0.0f, 1.0f}},
                Vertex{glm::vec3{0.5f, -0.5f, -0.5f},
                       glm::vec3{0.0f, 0.0f, 0.0f},
                       glm::vec2{1.0f, 1.0f}},
                Vertex{glm::vec3{0.5f, -0.5f, 0.5f},
                       glm::vec3{0.0f, 0.0f, 0.0f},
                       glm::vec2{1.0f, 0.0f}},
                Vertex{glm::vec3{0.5f, -0.5f, 0.5f},
                       glm::vec3{0.0f, 0.0f, 0.0f},
                       glm::vec2{1.0f, 0.0f}},
                Vertex{glm::vec3{-0.5f, -0.5f, 0.5f},
                       glm::vec3{0.0f, 0.0f, 0.0f},
                       glm::vec2{0.0f, 0.0f}},
                Vertex{glm::vec3{-0.5f, -0.5f, -0.5f},
                       glm::vec3{0.0f, 0.0f, 0.0f},
                       glm::vec2{0.0f, 1.0f}},

                Vertex{glm::vec3{-0.5f, 0.5f, -0.5f},
                       glm::vec3{0.0f, 0.0f, 0.0f},
                       glm::vec2{0.0f, 1.0f}},
                Vertex{glm::vec3{0.5f, 0.5f, -0.5f},
                       glm::vec3{0.0f, 0.0f, 0.0f},
                       glm::vec2{1.0f, 1.0f}},
                Vertex{glm::vec3{0.5f, 0.5f, 0.5f},
                       glm::vec3{0.0f, 0.0f, 0.0f},
                       glm::vec2{1.0f, 0.0f}},
                Vertex{glm::vec3{0.5f, 0.5f, 0.5f},
                       glm::vec3{0.0f, 0.0f, 0.0f},
                       glm::vec2{1.0f, 0.0f}},
                Vertex{glm::vec3{-0.5f, 0.5f, 0.5f},
                       glm::vec3{0.0f, 0.0f, 0.0f},
                       glm::vec2{0.0f, 0.0f}},
                Vertex{glm::vec3{-0.5f, 0.5f, -0.5f},
                       glm::vec3{0.0f, 0.0f, 0.0f},
                       glm::vec2{0.0f, 1.0f}}
        };
        std::shared_ptr<Texture> textures{Texture::loadShared("..\\assets\\cube-texture.jpg")};
        // Generate the index buffer, just in case the user wants to render with it, even though it is not necessary
        std::vector<unsigned int> indices(cubeVertices.size());
        // Fill the indices vector with the range [0, cubeVertices.size()-1]
        std::iota(std::begin(indices), std::end(indices), 0);
        // Generate the one and only mesh
        Mesh &&mesh{Mesh::generateMesh(cubeVertices, indices, std::vector<std::shared_ptr<Texture>>{textures})};
        // Generate the model and fill it with the previously created mesh
        Model &&model{};
        model.meshes.push_back(move(mesh));
        shared_ptr<Model> modelPtr{make_shared<Model>(move(model))};
        // Push the previously created type into the shared map
        this->models.emplace(PreModelType::CUBE, modelPtr);
        return modelPtr;
    }
}

std::shared_ptr<Model> ModelLoader::getSphere() {
    if (this->models.contains(PreModelType::SPHERE)) {
        // Contains the item, thus we return it
        return this->models.at(PreModelType::SPHERE);
    } else {
        // TODO: Implement the function to generate this model/mesh
        return nullptr;
    }
}