#pragma once
#include <stdint.h>
#include "../VertexBuffer.h"
#include "../IndexBuffer.h"
#include "../VertexBufferLayout.h"

class DrawDetails {
    public:
        unsigned int vao = 0;
        unsigned int vbo = 0;
        unsigned int numElements = 0;
        DrawDetails(unsigned int vao, unsigned int vbo, unsigned int e);
        DrawDetails();
};
