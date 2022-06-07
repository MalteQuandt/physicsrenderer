//
// Created by malte on 5/20/2022.
//

#include <iostream>
#include <numeric>

#include "render/ModelLoader.h"
#include "../include/Logger.h"


using namespace phyren;
using namespace std;
using namespace Assimp;

ModelLoader &ModelLoader::getInstance() {
    static ModelLoader loader{};
    return loader;
}

std::shared_ptr<Model> ModelLoader::load(const std::string &path) {
    if (this->models.contains(path)) {
        // Contains the item, thus we return it
        return this->models.at(path);
    } else {
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
        const unsigned int postProcessingOptions{
                aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenSmoothNormals};
        // Load the model from the given directory
        const aiScene *scene{importer.ReadFile(path, postProcessingOptions)};
        // Check if the scene and root node exists, and if the incomplete flag is set
        if (!scene || (AI_SCENE_FLAGS_INCOMPLETE & scene->mFlags) || !scene->mRootNode) {
            logging::Logger::GetLogger()->LogMessage(
                    "[ERROR] The model in the directory " + path + " could not be loaded!",
                    true, "Error");
            return nullptr;
        }
        // Set up the model storage unit
        std::shared_ptr<Model> model{make_shared<Model>(Model{})};
        // Recursively process the nodes, starting form the root node
        processNode(model, scene->mRootNode, scene);
        // Push the previously created type into the shared map
        this->models.emplace(path, model);
        return model;
    }
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
            tex.x = mesh->mTextureCoords[0][i].x;
            tex.y = mesh->mTextureCoords[0][i].y;
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
    return move(textures);
}

std::shared_ptr<Model> ModelLoader::getModel(PreModelType type) {
    switch (type) {
        case PreModelType::CUBE:
            return getCube();
        case PreModelType::SPHERE:
            return getSphere();
        default:
            logging::Logger::GetLogger()->LogMessage("[ERROR] There is no model of the type value "
                                                     + static_cast<const unsigned int>(type), true, "Error");
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
    if (this->models.contains("CUBE")) {
        // Contains the item, thus we return it
        return this->models.at("CUBE");
    } else {
        // Vertices for the vertex buffer
        const vector<float> vertices{
                -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
                0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
                0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
                0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
                -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
                -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,

                -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
                0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
                0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
                0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
                -0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
                -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,

                -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
                -0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
                -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
                -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
                -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
                -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

                0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
                0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
                0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
                0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
                0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
                0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

                -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
                0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
                0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
                0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
                -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
                -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

                -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
                0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
                0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
                0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
                -0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
                -0.5f, 0.5f, -0.5f, 0.0f, 1.0f
        };

        vector<Vertex> cubeVertices{};
        for (int i{0}; i < vertices.size(); i += 5) {
            cubeVertices.emplace_back(
                    Vertex{glm::vec3{vertices[i],
                                     vertices[i + 1],
                                     vertices[i + 2]}, glm::vec3{0, 0, 0},
                           glm::vec2{vertices[i + 3], vertices[i + 4]}}
            );
        }
        /*
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
         */
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
        this->models.emplace("CUBE", modelPtr);
        return modelPtr;
    }
}

#define radius 1
#define sectors 100
#define stacks 100


std::shared_ptr<Model> ModelLoader::getSphere() {
    if (this->models.contains("SPHERE")) {
        // Contains the item, thus we return it
        return this->models.at("SPHERE");
    } else {
        // Calculate the normals, vertices and texture coordinates of the sphere
        vector<glm::vec3> vertices{};
        vector<glm::vec3> normals{};
        vector<glm::vec2> texCoords{};

        float invLength = 1.0f / radius;

        float sectorstep{2 * glm::pi<float>() / sectors};
        float stackstep{glm::pi<float>() / stacks};


        for (int i{0}; i <= stacks; i++) {
            // Vertex position coordinates

            float angleSector{0};
            float angleStack{0};

            angleStack = glm::pi<float>() / 2 - i * stackstep;
            float xy{radius * glm::cos(angleStack)};
            float z{radius * glm::sin(angleStack)};

            for (int j{0}; j <= sectors; j++) {
                // Calculate the coordinates of the vertex
                angleSector = j * sectorstep;
                float x{xy * glm::cos(angleSector)};
                float y{xy * glm::sin(angleSector)};
                vertices.push_back(glm::vec3{x, y, z});

                // Normal coordinates
                // Calculate the normal for this vertex
                float nx{x * invLength};
                float ny{y * invLength};
                float nz{
                        z * invLength};
                normals.push_back(glm::vec3{nx, ny, nz});

                // Calculate the texture coordinates for this vertex
                float s{static_cast<float>(j) / sectors};
                float t{static_cast<float>(i) / stacks};
                texCoords.push_back(glm::vec2{s, t});
            }
        }
        // Calculate the indices
        vector<unsigned int> indices;

        for (int i{0}; i < stacks; i++) {
            int k1{i * (sectors + 1)};
            int k2{k1 + sectors + 1};
            for (int j{0}; j < sectors; j++, k1++, k2++) {
                if (i != 0) {
                    indices.push_back(k1);
                    indices.push_back(k2);
                    indices.push_back(k1 + 1);
                }
                if (i != (stacks - 1)) {
                    indices.push_back(k1 + 1);
                    indices.push_back(k2);
                    indices.push_back(k2 + 1);
                }
            }
        }
        std::vector<Vertex> sphereVertices{};
        // Generate the sphereVertices vector
        for (unsigned int i{0}; i < vertices.size(); i++) {
            sphereVertices.push_back(Vertex{
                    vertices.at(i),
                    normals.at(i),
                    texCoords.at(i)
            });
        }

        // Generate the mesh
        std::shared_ptr<Texture> textures{Texture::loadShared("..\\assets\\cube-texture.jpg")};
        Mesh &&mesh{
                Mesh::generateMesh(sphereVertices, indices, std::vector<std::shared_ptr<Texture>>{textures})};
        // Generate the model and fill it with the previously created mesh
        Model &&model{};
        model.meshes.push_back(move(mesh));
        shared_ptr<Model> modelPtr{make_shared<Model>(move(model))};
        // Push the previously created type into the shared map
        this->models.emplace("SPHERE", modelPtr);
        return modelPtr;
    }
}