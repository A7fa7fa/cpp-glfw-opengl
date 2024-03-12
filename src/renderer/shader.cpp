#include <fstream>
#include <sstream>
#include <iostream>
#include "shader.h"

Shader::Shader(const std::string& filepath)
    : filepath(filepath), rendererId(0) {
    ShaderProgramSource source = parseShader(filepath);
    // std::cout << "Vertex..." << std::endl;
    // std::cout << source.vertexSource << std::endl;
    // std::cout << "Fragment..." << std::endl;
    // std::cout << source.fragmentSource << std::endl;
    rendererId = createShader(source.vertexSource, source.fragmentSource);
}

Shader::~Shader() {
    GLCall(glDeleteProgram(rendererId));
}

ShaderProgramSource Shader::parseShader(const std::string& filePath) {
    enum class ShaderType {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };
    const char* shaderTypeName[2] = {"vertex", "fragment"};

    std::fstream stream(filePath); // this opens file

    std::string line;
    std::stringstream ss[2]; // create two stringstreams. one fro fragment, one for vertex shader
    ShaderType currType = ShaderType::NONE;
    while(getline(stream, line)) {
        if (line.find("#shader") != std::string::npos) { // npos is not a valid position so find was not successfull
            if (line.find(shaderTypeName[(int)ShaderType::VERTEX]) != std::string::npos) {
                currType = ShaderType::VERTEX;
            } else if (line.find(shaderTypeName[(int)ShaderType::FRAGMENT]) != std::string::npos) {
                currType = ShaderType::FRAGMENT;
            } else {
                currType = ShaderType::NONE;
            }
        } else {
            ss[(int)currType] << line << '\n';
        }
    }
    return {ss[0].str(), ss[1].str()};
}

unsigned int Shader::createShader(const std::string& vertexShader, const std::string& fragmentShader) {
    unsigned int program = glCreateProgram();
    int vs = compileShader(GL_VERTEX_SHADER, vertexShader);
    int fs = compileShader(GL_FRAGMENT_SHADER, fragmentShader);

    if (!vs || !fs) {
        return 0;
    }

    GLCall(glAttachShader(program, vs));
    GLCall(glAttachShader(program, fs));
    GLCall(glLinkProgram(program));
    GLCall(glValidateProgram(program));

    GLCall(glDeleteShader(vs)); // can delete because shaders are linked to programm. deletes translation units. not worth it to do.
    GLCall(glDeleteShader(fs));
    return program;
}

unsigned int Shader::compileShader(unsigned int type, const std::string& source) {
    GLCall(unsigned int id = glCreateShader(type));
    const char* src = source.c_str(); // this string needs to exists. returns pointer to start of string
    GLCall(glShaderSource(id, 1, &src, nullptr)); // basicly tell ogl where the source is located in memory
    GLCall(glCompileShader(id));

    int result;
    GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
    if (result == GL_FALSE) {
        std::cout << "Could not compile shader : " << type << " " << source << std::endl;
        return 0;
    }

    return id;
}

void Shader::bind() const {
    GLCall(glUseProgram(rendererId));
}

void Shader::unbind() const  {
    GLCall(glUseProgram(0));
}

void Shader::setUniform4f(const std::string& name, float v0, float v1, float v2, float  v3) {
    GLCall(glUniform4f(getUniformLocation(name), v0, v1, v2, v3));
}

void Shader::setUniform1i(const std::string& name, int value) {
    GLCall(glUniform1i(getUniformLocation(name), value));
}

void Shader::setUniform1f(const std::string& name, float value) {
    GLCall(glUniform1f(getUniformLocation(name), value));
}

int Shader::getUniformLocation(const std::string& name) {

    if (uniformLocationCache.find(name) != uniformLocationCache.end()) {
        return uniformLocationCache[name];
    }
    GLCall(int uniforrmLocation = glGetUniformLocation(rendererId, name.c_str()));
    if (uniforrmLocation == -1) {
        std::cout << "Warning: uniform '" << name << "' not found" << std::endl;
    }
    uniformLocationCache[name] = uniforrmLocation;
    return uniforrmLocation;
}
