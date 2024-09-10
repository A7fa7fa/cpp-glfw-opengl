#include "glwarpper.h"
#include "IndexBuffer.h"

IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count) : count(count) {

    // generates 1 buffer object for the element buffer (EBO) (in general it is called an index buffer)
    GLCall(glGenBuffers(1, &rendererId));
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererId));
    // describe buffer data
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count*sizeof(unsigned int), data, GL_STATIC_DRAW));

}

IndexBuffer::~IndexBuffer() {
    GLCall(glDeleteBuffers(1, &rendererId));
}

void IndexBuffer::bind() const {
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererId));
}
void IndexBuffer::unbind() const {
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}