#include <iostream>
#include "drawdetails.h"

DrawDetails::DrawDetails(unsigned int vao, unsigned int vbo, unsigned int e) {
    this->vao = vao;
    this->vbo = vbo;
    this->numElements = e;
}

DrawDetails::DrawDetails() {
    std::cout << "default drawdetails constuctr used" << std::endl;
}
