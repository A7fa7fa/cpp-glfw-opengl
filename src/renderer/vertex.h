#pragma once
#include <cstdint>

class Vertex {
    public:
        float pos[3] = {0.0f, 0.0f, 0.0f};
        Vertex(float x, float y, float z);
        Vertex();
        Vertex(const Vertex& vertex);
};

class DrawDetails {
    public:
        uint32_t vao = 0;
        uint32_t numElements = 0;
        DrawDetails(uint32_t v, uint32_t e);
        DrawDetails();
};
