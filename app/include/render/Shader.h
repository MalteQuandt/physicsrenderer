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
        static std::shared_ptr<Shader> Factory(const std::string &source, ShaderType type);

        /**
        * Get the id of this shader object
        * @return the id of this shader
        */
        virtual const unsigned int  getId [[nodiscard]] () const;

        /**
         * Get the type of this shader object
         */
        virtual const ShaderType &getType [[nodiscard]] () const;

        /**
         * Delete this shader object
         */
        ~Shader();

        /* Copy operation is prohibited, as only one copy of this object can exist at the same time*/
        Shader(const Shader &) = delete;

        Shader &operator=(const Shader &) = delete;

        Shader(Shader &&) noexcept;

        Shader &operator=(Shader &&) noexcept;

    private:
        unsigned int shaderId{0};

        const ShaderType type{0};

        /**
         * Create a shader from the given source and compile it
         * @param source
         */
        explicit Shader(const std::string &shaderId, ShaderType type);

        /**
        * Create shader object and test for errors
        *
        * @param type the type of the shader object
        * @param source the source code of the shader object
        * @param shaderTypeName the name of the shader type
        *
        * @return true if there were no errors
        */
        bool
        compile(unsigned int type, const std::string &source, const std::string& shaderTypeName);

        /**
         * Check if there are errors in the given shader program
         *
         * @return if the shader encountered an error
         */
        bool checkCompileErrors(std::string type);
    };
}


#endif //PHYSICS_RENDERER_SHADER_H
