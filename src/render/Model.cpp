//
// Created by malte on 5/20/2022.
//

#include "render/Model.h"

using namespace std;
using namespace phyren;

void Model::render(std::shared_ptr<ShaderProgram> shader) {
    shader->use();
    // Iterate over the mesh's and draw them
    for(unsigned int i{0}; i< meshes.size();i++) {
        meshes[i].render(shader);
    }
    // Reset the active texture
    glActiveTexture(GL_TEXTURE0);
}

Model::Model(std::vector<Mesh>&& meshes) : meshes(move(meshes)) {}