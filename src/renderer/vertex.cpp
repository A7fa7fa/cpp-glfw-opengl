#include "vertex.h"
#include <iostream>

Vertex::Vertex(float x, float y, float z) {
    this->pos[0] = x;
    this->pos[1] = y;
    this->pos[2] = z;
}

Vertex::Vertex() {
    std::cout << "default vert constuctr used" << std::endl;
}

Vertex::Vertex(const Vertex& vertex) {
    this->pos[0] = vertex.pos[0];
    this->pos[1] = vertex.pos[1];
    this->pos[2] = vertex.pos[2];
    std::cout << "copied vert" << std::endl;
}

DrawDetails::DrawDetails(uint32_t v, uint32_t e) {
    this->vao = v;
    this->numElements = e;
}

DrawDetails::DrawDetails() {
    std::cout << "default drawdetails constuctr used" << std::endl;
}
