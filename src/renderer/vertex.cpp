#include "vertex.h"
#include <iostream>
#include "VertexBuffer.h"
#include "IndexBuffer.h"

Vertex::Vertex(float x, float y, float z) {
    this->pos[0] = x;
    this->pos[1] = y;
    this->pos[2] = z;
    this->setColor(0, 0, 0, 255);
    std::cout << "pos vert constructor used" << std::endl;
}

Vertex::Vertex(float x, float y, float z, unsigned char r, unsigned char g, unsigned char b, unsigned char a){
    this->pos[0] = x;
    this->pos[1] = y;
    this->pos[2] = z;
    this->setColor(r, g, b, a);
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

void Vertex::setColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a) {
    this->color[0] = r / 255.0;
    this->color[1] = g / 255.0;
    this->color[2] = b / 255.0;
    this->color[3] = a / 255.0;
}

void Vertex::registerLayout(VertexBufferLayout& layout) {
    layout.push(GL_FLOAT, sizeof(Vertex::pos)/sizeof(Vertex::pos[0]));
    layout.push(GL_FLOAT, sizeof(Vertex::color)/sizeof(Vertex::color[0]));
}

DrawDetails::DrawDetails(unsigned int vao, unsigned int vbo, unsigned int e) {
    this->vao = vao;
    this->vbo = vbo;
    this->numElements = e;
}

DrawDetails::DrawDetails() {
    std::cout << "default drawdetails constuctr used" << std::endl;
}
