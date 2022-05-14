//
// Created by malte on 5/11/2022.
//

#ifndef PHYSICS_RENDERER_SHADERPROGRAM_H
#define PHYSICS_RENDERER_SHADERPROGRAM_H

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "glm/gtc/type_ptr.hpp"

#include "glm/matrix.hpp"
#include <glm/glm.hpp>

#include "render/Shader.h"

#include <string>
#include <memory>

namespace phyren {
    /**
     * Encapsulation for GLSL shader programs
     */
    class ShaderProgram final {
    public:
        /**
         * Create a shader program from the given shaders
         *
         * @param vShader the vertex shader
         * @param fShader the fragment shader
         *
         * @return a shared pointer reference to the shader program
         */
        static std::shared_ptr<ShaderProgram> Factory(const Shader &vShader, const Shader &fShader);

        /**
         * Create a shader program from the given shared pointers to shaders
         *
         * @param vShader the vertex shader
         * @param fShader the fragment shader
         *
         * @return a shared pointer reference to the shader program
         */
        static std::shared_ptr<ShaderProgram> Factory(std::shared_ptr<Shader> vShader, std::shared_ptr<Shader> fShader);

        /**
         * Bind this shader object
         */
        void use();

        /**
         * Set the vec4 uniform referenced by the reference value in the shader
         *
         * @param reference the name of the uniform
         * @param value the value to be set
         */
        void setMat4(const std::string &reference, glm::mat4 &value);

        /**
         * Set the vec3 uniform referenced by the reference value in the shader
         *
         * @param reference the name of the uniform
         * @param value the value to be set
         */
        void setVec3(const std::string &reference, glm::vec3 &value);

        /**
         * Set the float uniform referenced by the reference value in the shader
         *
         * @param reference the name of the uniform
         * @param value the value to be set
         */
        void setFloat(const std::string &reference, float value);

        /**
         * Delete this shader program
         */
        ~ShaderProgram();

    private:
        // Id of the shader program
        unsigned int PID{0};

        /**
         * Create a shader object consisting of a vertex and fragment shader from
         * shaders in the parameter.
         *
         * @param vertexShader path of the vertex shader
         * @param fragmentShader path of the fragment shader
         */
        explicit ShaderProgram(const Shader &vertexShader, const Shader &fragmentShader);

        /**
         * Create a shader object consisting of a vertex and fragment shader from
         * shaders in the parameter.
         *
         * @param vertexShader path of the vertex shader
         * @param fragmentShader path of the fragment shader
         */
        explicit ShaderProgram(std::shared_ptr<Shader> vShader, std::shared_ptr<Shader> fShader);

        /**
         * Check the errors in the given shader object
         *
         * @return if the shader encountered an error
         */
        bool checkCompileErrorsProgram();

    };
}


#endif //PHYSICS_RENDERER_SHADERPROGRAM_H
