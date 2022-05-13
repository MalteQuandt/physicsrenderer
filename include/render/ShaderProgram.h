//
// Created by malte on 5/11/2022.
//

#ifndef PHYSICS_RENDERER_SHADERPROGRAM_H
#define PHYSICS_RENDERER_SHADERPROGRAM_H

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "render/Shader.h"

#include <string>
#include <memory>

namespace phyren {
    /**
     * Encapsulation for GLSL shader programs
     */
    class ShaderProgram {
    public:
        static std::shared_ptr<ShaderProgram> Factory(const Shader& vShader, const Shader& fShader);
        /**
         * Bind this shader object
         */
        void use();

        /**
         * Delete this shader program
         */
        ~ShaderProgram();
    private:
        // Id of the shader program
        unsigned int PID{0};
        /**
         * Create a shader object consisting of a vertex and fragment shader from
         * files in the parameter.
         *
         * @param vertexShader path of the vertex shader
         * @param fragmentShader path of the fragment shader
         */
        explicit ShaderProgram(const Shader &vertexShader, const Shader &fragmentShader);

        /**
         * Check the errors in the given shader object
         *
         * @param shader reference to the shader object
         *
         * @return if the shader encountered an error
         */
        bool checkCompileErrorsProgram(const unsigned int shader);

    };
}


#endif //PHYSICS_RENDERER_SHADERPROGRAM_H
