//
// Created by malte on 5/11/2022.
//

#include "Shader.h"

#include <iostream>

using namespace phyren;
using namespace std;

std::shared_ptr<Shader> Shader::Factory(const char* source, ShaderType type) {
    return make_shared<Shader>(Shader(source, type));
}

Shader::Shader(const char *source, ShaderType type) : type(type){
    const char *shaderCode{phyren::filehandling::loadFileString(source).c_str()};
    switch (type) {
        case ShaderType::VERTEX_SHADER:
            compile(GL_VERTEX_SHADER, shaderId, shaderCode, "Vertex ShaderProgram");
            break;
        case ShaderType::FRAGMENT_SHADER:
            compile(GL_FRAGMENT_SHADER, shaderId, shaderCode, "Fragment ShaderProgram");
            break;
    }
}

Shader::~Shader() {
    if (0 != shaderId) { glDeleteShader(this->shaderId); }
}

unsigned int Shader::getId() const {
    return this->shaderId;
}

bool Shader::compile(unsigned int type, unsigned int &shader, const char *source, const string shaderTypeName) {
    shader = glCreateShader(type);
    // Set the code to be the nullbit-terminated source code we just loaded
    glShaderSource(shader, 1, &source, nullptr);
    glCompileShader(shader);
    // Check for errors that might have occured:
    return checkCompileErrors(shader, shaderTypeName);
}

bool Shader::checkCompileErrors(const unsigned int shader, const string type) {
    int success{};
    char info[1024]{};
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 1024, nullptr, info);
        cerr <<
             "[ERROR] The shader of type " + type + " could not be compiled!\n" + info
             << endl;
    }
    return success;
}