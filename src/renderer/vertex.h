#pragma once
#include <stdint.h>
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexBufferLayout.h"

struct Pos {
    float x;
    float y;
    float z;
};

struct Color {
    float r;
    float g;
    float b;
    float a;
};

struct TextureKoord {
    float s;
    float t;
};

class Vertex {
    public:
        Pos pos = {0.0f, 0.0f, 0.0f};
        Color color = {0.0f, 0.0f, 0.0f, 0.0f};
        TextureKoord texture = {0.0f, 0.0f};
        // uint32_t color = 0xFFFFFFFF; // #rgba
        Vertex(float x, float y, float z);
        Vertex(float x, float y, float z, unsigned char r, unsigned char g, unsigned char b, unsigned char a, float textureX, float textureY);
        Vertex();
        Vertex(const Vertex& vertex);
        void setColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a);
        static void registerLayout(VertexBufferLayout& layout);
};
