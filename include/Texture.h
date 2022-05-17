//
// Created by malte on 5/16/2022.
//

#ifndef PHYSICS_RENDERER_TEXTURE_H
#define PHYSICS_RENDERER_TEXTURE_H

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <string>
#include <memory>

namespace phyren {
    class Texture {
    public:

        /**
         * Create a new shared pointer texture object
         *
         * @param path the path of the texture file
         * @return the shared pointer to the texture object
         */
        static std::shared_ptr<Texture> instance(const std::string& path);
        /**
         * Load a new texture from the file in the path
         *
         * @param path the path of the texture file
         * @return the texture
         */
        static Texture load(const std::string& path);
        /**
         * Load a new texture from the file in the path
         * and bind it to the given uniform value
         * @param uniform the unif
         * @param path the path of the texture file
         * @return the texture
         */
        static Texture load(const std::string& path, const std::string& uniform);
        // Getter:
        // -------
        /**
         * Return the reference value of this texture in the opengl context
         *
         * @return the reference value of this texture
         */
        unsigned int getTid() const;

        /**
         * Return the uniform string that this texture is referenced with in the shader
         *
         * @return the uniform string id
         */
        const std::string &getUniformId() const;

        /**
         * Set to which uniform this texture binds
         *
         * @param uniform the name of the uniform
         */
        void setUniformId(const std::string& uniform);
        /**
         * Set the specified parameter of the given type
         * @attention Overload this with your type as param if necessary!
         *
         * @param pname the name of the parameter to set
         * @param param the value of the parameter 'pname'
         */
        void setTextureParameter(GLenum pname, GLint param) const;

        /* Implemented move semantics */
        Texture(Texture&&);
        Texture& operator=(Texture&&);

        /**
         * Bind this texture as the current one of GL_TEXTURE_2D
         */
        void bind() const;

        /*
         * Remove the ability to copy, as creating multiple copies makes no sense
         */
        Texture(const Texture&) = delete;
        Texture& operator=(const Texture&) = delete;

        ~Texture();
    private:
        // Texture id
        unsigned int tid{0};
        // Shader uniform name of this texture
        std::string shaderTextureUniform{""};

        /**
         * Generate a texture
         *
         * @param name the texture uniform id in a shader
         * @param tid the id of the texture
         */
        explicit Texture( unsigned int tid, const std::string &name);
        /**
         * Generate a texture with no specified uniform attached yet
         *
         * @param tid the texutre id of the texture
         */
        explicit Texture(unsigned int tid);
    };
}

#endif //PHYSICS_RENDERER_TEXTURE_H
