//
// Created by malte on 5/11/2022.
//

#ifndef PHYSICS_RENDERER_SHADER_H
#define PHYSICS_RENDERER_SHADER_H

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "util/FileHandler.h"

#include <string>
#include <memory>


namespace phyren {
    /**
     * Shader types that can be created
     */
    enum class ShaderType : unsigned int {
        VERTEX_SHADER,
        FRAGMENT_SHADER
    };
    /**
     * Encapsulation for GLSL Shader objects
     */
    class Shader {
    public:
        /**
         * Factory for a shader. Due to the nature of shader objects
         *
         * @param source the source of the shader
         * @param type the type of the shader
         *
         * @return the created instance
         */
        static std::shared_ptr<Shader> Factory(const char* source, ShaderType type);
        /**
        * Get the id of this shader object
        * @return the id of this shader
        */
        unsigned int getId() const;

        /**
         * Delete this shader object
         */
        ~Shader();
    private:
        unsigned int shaderId{0};

        ShaderType type{0};
        /**
         * Create a shader from the given source and compile it
         * @param source
         */
        explicit Shader(const char* shaderId, ShaderType type);
        /**
        * Create shader object and test for errors
        *
        * @param type the type of the shader object
        * @param shader the shader objects reference value
        * @param source the source code of the shader object
        * @param shaderTYpeName the name of the shader type
        *
        * @return true if there were no errors
        */
        bool
        compile(unsigned int type, unsigned int &shader, const char *source, const std::string shaderTypeName);

        /**
         * Check if there are errors in the given shader program
         *
         * @param shader reference to the shader program
         *
         * @return if the shader encountered an error
         */
        bool checkCompileErrors(const unsigned int shader, std::string type);
    };
}


#endif //PHYSICS_RENDERER_SHADER_H
