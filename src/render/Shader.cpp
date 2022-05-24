//
// Created by malte on 5/11/2022.
//

#include "render/Shader.h"

#include <iostream>
#include <string>

using namespace phyren;
using namespace std;

std::shared_ptr<Shader> Shader::Factory(const std::string &source, ShaderType type) {
    return make_shared<Shader>(Shader(source, type));
}

Shader::Shader(const std::string &source, ShaderType type) : type(type) {
    switch (type) {
        case ShaderType::VERTEX_SHADER:
            compile(GL_VERTEX_SHADER, source, "Vertex");
            break;
        case ShaderType::FRAGMENT_SHADER:
            compile(GL_FRAGMENT_SHADER, source, "Fragment");
            break;
    }
}

Shader::~Shader() {
    if (0 != shaderId) { glDeleteShader(this->shaderId); }
}

const unsigned int Shader::getId() const {
    return this->shaderId;
}

bool Shader::compile(unsigned int shaderType, const string &source, const string& shaderTypeName) {

    const char *code{phyren::filehandling::loadFileString(source).c_str()};
    this->shaderId = glCreateShader(shaderType);
    // Set the code to be the nullbit-terminated source code we just loaded
    glShaderSource(this->shaderId, 1, &code, nullptr);
    glCompileShader(this->shaderId);
    // Check for errors that might have occured:
    return checkCompileErrors(shaderTypeName);
}

bool Shader::checkCompileErrors(const string shaderType) {
    int success{};
    char info[1024]{};
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shaderId, 1024, nullptr, info);
        cerr <<
             "[ERROR] The shader of type " + shaderType + " could not be compiled!\n" + info
             << endl;
    }
    return success;
}

const ShaderType &Shader::getType() const {
    return this->type;
}

Shader::Shader(Shader&& s) noexcept{
    swap(this->shaderId, s.shaderId);
}
Shader& Shader::operator=(Shader&& s) noexcept {
    if(this != &s) {
        swap(this->shaderId, s.shaderId);
    }
    return *this;
}