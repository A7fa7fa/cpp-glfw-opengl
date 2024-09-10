#include "vertex.h"
#include <iostream>

Vertex::Vertex(float x, float y, float z) {
    this->pos.x = x;
    this->pos.y = y;
    this->pos.z = z;
    this->setColor(0, 0, 0, 255);
    std::cout << "pos vert constructor used" << std::endl;
}

Vertex::Vertex(float x, float y, float z, unsigned char r, unsigned char g, unsigned char b, unsigned char a, float textureX, float textureY){
    this->pos.x = x;
    this->pos.y = y;
    this->pos.z = z;
    this->setColor(r, g, b, a);
    this->texture.s = textureX;
    this->texture.t = textureY;
}

Vertex::Vertex() {
    std::cout << "default vert constuctr used" << std::endl;
}

Vertex::Vertex(const Vertex& vertex) {
    this->pos.x = vertex.pos.x;
    this->pos.y = vertex.pos.y;
    this->pos.z = vertex.pos.z;
    std::cout << "copied vert" << std::endl;
}

void Vertex::setColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a) {
    this->color.r = r / 255.0;
    this->color.g = g / 255.0;
    this->color.b = b / 255.0;
    this->color.a = a / 255.0;
}

void Vertex::registerLayout(VertexBufferLayout& layout) {
    layout.push(GL_FLOAT, sizeof(Vertex::pos)/sizeof(Vertex::pos.x));
    layout.push(GL_FLOAT, sizeof(Vertex::color)/sizeof(Vertex::color.r));
    layout.push(GL_FLOAT, sizeof(Vertex::texture)/sizeof(Vertex::texture.s));
}
