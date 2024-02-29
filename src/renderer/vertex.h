#pragma once
#include <stdint.h>

class Vertex {
    public:
        float pos[3] = {0.0f, 0.0f, 0.0f};
        float color[4] = {0.0f, 0.0f, 0.0f, 0.0f};
        // uint32_t color = 0xFFFFFFFF; // #rgba
        Vertex(float x, float y, float z);
        Vertex(float x, float y, float z, unsigned char r, unsigned char g, unsigned char b, unsigned char a);
        Vertex();
        Vertex(const Vertex& vertex);
        void setColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a);
};

class DrawDetails {
    public:
        unsigned int vao = 0;
        unsigned int vbo = 0;
        unsigned int numElements = 0;
        DrawDetails(unsigned int vao, unsigned int vbo, unsigned int e);
        DrawDetails();
};
