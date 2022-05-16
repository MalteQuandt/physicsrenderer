//
// Created by malte on 5/16/2022.
//

#ifndef PHYSICS_RENDERER_TEXTURE_H
#define PHYSICS_RENDERER_TEXTURE_H

#include <string>

class Texture {
public:
    /**
     * Generate a texture
     *
     * @param name the texture uniform id in a shader
     * @param tid the id of the texture
     */
    explicit Texture(const std::string &name, unsigned int tid);

    // Getter:
    // -------
    unsigned int getTid() const;

    const std::string &getUniformId() const;

private:
    // Texture id
    unsigned int tid;
    // Shader uniform name of this texture
    const std::string shaderTextureUniform;
};


#endif //PHYSICS_RENDERER_TEXTURE_H
