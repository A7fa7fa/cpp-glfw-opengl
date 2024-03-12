#pragma once
#include <string>
#include <unordered_map>
#include "glwarpper.h"

struct ShaderProgramSource {
    std::string vertexSource;
    std::string fragmentSource;
};

class Shader {
    private:
        unsigned int rendererId;
        const std::string& filepath;
        std::unordered_map<std::string, int> uniformLocationCache;
    public:
        Shader(const std::string& filepath);
        ~Shader();

    private:
        ShaderProgramSource parseShader(const std::string& filePath);
        unsigned int createShader(const std::string& vertexShader, const std::string& fragmentShader);
        unsigned int compileShader(unsigned int type, const std::string& source);
        int getUniformLocation(const std::string& name);

    public:
        void bind() const;
        void unbind() const;

        void setUniform1i(const std::string& name, int value);
        void setUniform1f(const std::string& name, float value);
        void setUniform4f(const std::string& name, float v0, float v1, float v2, float  v3);

};
