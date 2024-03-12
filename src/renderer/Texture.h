#pragma once
#include <string>
#include <unordered_map>
#include "glwarpper.h"

class Texture {
    private:
        unsigned int rendererId;
        const std::string& filepath;
        unsigned char* localBuffer;
        int width, height, bitsPerPixel;
    public:
        Texture(const std::string& filepath);
        ~Texture();

    public:
        void bind(unsigned int slot = 0) const;
        void unbind() const;
        inline int getWidht() {return width;}
        inline int getHeight() {return height;}
};
