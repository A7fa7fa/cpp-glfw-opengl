#include "glwarpper.h"
#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(const void* data, unsigned int size) {
    // generates a buffer object for the vertex buffer (VBO) (here rendererId)
    GLCall(glGenBuffers(1, &rendererId));
    // binds it to context as an array buffer
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, rendererId));
    // uploads vertex data to GPU.
    // type of buffer, size in memory of verts data, pointer to start of data same as (&verticis[0]), draw mode -> we dont change the data after uploading so static draw
    GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

VertexBuffer::~VertexBuffer() {
    GLCall(glDeleteBuffers(1, &rendererId));
}

void VertexBuffer::bind() const {
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, rendererId));
}
void VertexBuffer::unbind() const {
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}