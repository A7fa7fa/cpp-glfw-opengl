#pragma once
#include <vector>
#include <stdexcept>
#include <GL/glew.h>
#include <iostream>
#include "glwarpper.h"

struct VertexBufferLayoutElement
{
    unsigned int type;
    unsigned int count;
    unsigned int normalized;

    static unsigned int getSizeOfType(int type) {
        switch (type) {
            case GL_FLOAT: return 4;
            case GL_UNSIGNED_INT: return 4;
            case GL_UNSIGNED_BYTE: return 1;
        }
        ASSERT(false);
        return 0;
    }
};

class VertexBufferLayout {

    private:
        std::vector<VertexBufferLayoutElement> elements;
        unsigned int stride;
    public:
        VertexBufferLayout();
        ~VertexBufferLayout();

        void push(unsigned int type, unsigned int count);

        const std::vector<VertexBufferLayoutElement> getElements() const;
        unsigned int getStride() const;
};
