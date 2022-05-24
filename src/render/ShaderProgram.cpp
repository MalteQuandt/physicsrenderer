//
// Created by malte on 5/11/2022.
//
#include <iostream>

#include "render/ShaderProgram.h"
#include "util/FileHandler.h"

using namespace std;
using namespace phyren::filehandling;

namespace phyren {

    std::shared_ptr<ShaderProgram> ShaderProgram::Factory(const Shader& vShader, const Shader& fShader) {
        return make_shared<ShaderProgram>(ShaderProgram(vShader, fShader));
    }

    std::shared_ptr<ShaderProgram> ShaderProgram::Factory(std::shared_ptr<Shader> vShader, std::shared_ptr<Shader> fShader) {
        return make_shared<ShaderProgram>(ShaderProgram(vShader, fShader));
    }

    ShaderProgram::ShaderProgram(const Shader& vertexShader, const Shader& fragmentShader) {
        // Link the shaders together
        this->PID = glCreateProgram();
        glAttachShader(this->PID, vertexShader.getId());
        glAttachShader(this->PID, fragmentShader.getId());
        glLinkProgram(this->PID);
        // Check for errors encountered during the linking process
        checkCompileErrorsProgram();
    }

    ShaderProgram::ShaderProgram(std::shared_ptr<Shader> vShader, std::shared_ptr<Shader> fShader) {
        // Link the shaders together
        this->PID = glCreateProgram();
        glAttachShader(this->PID, vShader->getId());
        glAttachShader(this->PID, fShader->getId());
        glLinkProgram(this->PID);
        // Check for errors encountered during the linking process
        checkCompileErrorsProgram();
    }

    bool ShaderProgram::checkCompileErrorsProgram() {
        int success{};
        char info[1024]{};
        glGetProgramiv(this->PID, GL_LINK_STATUS, &success);
        if(!success) {
            glGetProgramInfoLog(this->PID, 1024, nullptr, info);
            cerr <<
            "[ERROR] The shader object could not be linked!\n" + std::string(info)
            << endl;
        }
        return success;
    }

    ShaderProgram::~ShaderProgram() {
        glDeleteProgram(this->PID);
    }

    void ShaderProgram::use() {
        glUseProgram(this->PID);
    }

    void ShaderProgram::set(const std::string &reference, glm::mat4 &value) {

        glUniformMatrix4fv(glGetUniformLocation(this->PID, reference.c_str()),1,GL_FALSE, glm::value_ptr(value));
    }

    void ShaderProgram::set(const std::string &reference, glm::vec3 &value) {
        glUniform3fv(glGetUniformLocation(this->PID, reference.c_str()), 1, &value[0]);
    }

    void ShaderProgram::set(const std::string &reference, float value) {
        glUniform1f(glGetUniformLocation(this->PID, reference.c_str()), value);
    }
    void ShaderProgram::set(const std::string& reference, int value) {
        glUniform1i(glGetUniformLocation(this->PID, reference.c_str()), value);
    }
    ShaderProgram::ShaderProgram(ShaderProgram && sp) {
        swap(this->PID, sp.PID);
    }
    ShaderProgram &ShaderProgram::operator=(ShaderProgram && sp) {
        if(this != &sp) {
            swap(this->PID, sp.PID);
        }
        return *this;
    }

}
