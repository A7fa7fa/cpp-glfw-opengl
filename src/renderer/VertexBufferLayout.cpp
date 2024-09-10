#include "VertexBufferLayout.h"
#include <GL/glew.h>

VertexBufferLayout::VertexBufferLayout() {
    stride = 0;
};
VertexBufferLayout::~VertexBufferLayout() {};

void VertexBufferLayout::push(unsigned int type, unsigned int count) {
    elements.push_back({type, count, GL_FALSE});
    stride += count * VertexBufferLayoutElement::getSizeOfType(type);
}

unsigned int VertexBufferLayout::getStride() const {
    return stride;
}

const std::vector<VertexBufferLayoutElement> VertexBufferLayout::getElements() const {
    return elements;
}
