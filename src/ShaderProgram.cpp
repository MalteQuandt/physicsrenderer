//
// Created by malte on 5/11/2022.
//

#include <iostream>

#include "ShaderProgram.h"
#include "FileHandler.h"

using namespace std;
using namespace phyren::filehandling;

namespace phyren {
    std::shared_ptr<ShaderProgram> ShaderProgram::Factory(const Shader& vShader, const Shader& fShader) {
        return make_shared<ShaderProgram>(ShaderProgram(vShader, fShader));
    }
    ShaderProgram::ShaderProgram(const Shader& vertexShader, const Shader& fragmentShader) {
        // Link the shaders together
        this->PID = glCreateProgram();
        glAttachShader(this->PID, vertexShader.getId());
        glAttachShader(this->PID, fragmentShader.getId());
        glLinkProgram(this->PID);
        // Check for errors encountered during the linking process
        checkCompileErrorsProgram(this->PID);
    }

    bool ShaderProgram::checkCompileErrorsProgram(const unsigned int shader) {
        int success{};
        char info[1024]{};
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if(!success) {
            glGetProgramInfoLog(shader, 1024, nullptr, info);
            cerr <<
            "[ERROR] The shader object could not be linked!\n" + std::string(info)
            << endl;
        }
        return success;
    }
    ShaderProgram::~ShaderProgram() {
        glDeleteProgram(this->PID);
    }

}
