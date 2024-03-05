#include "VertexArray.h"
#include "glwarpper.h"

VertexArray::VertexArray(){
    GLCall(glGenVertexArrays(1, &rendererId))
};
VertexArray::~VertexArray(){
    GLCall(glDeleteVertexArrays(1, &rendererId));
};

void VertexArray::addBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout) {
    bind();
    vb.bind();

    const auto& elements = layout.getElements();

    uintptr_t offset = 0;

    for (unsigned int i = 0; i < elements.size(); i++) {
        const auto& element = elements[i];
        GLCall(glEnableVertexAttribArray(i));
        GLCall(glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.getStride(), (const void*)offset));
        offset += element.count * VertexBufferLayoutElement::getSizeOfType(element.type);

    }

}

void VertexArray::bind() const {
    GLCall(glBindVertexArray(rendererId));
}
void VertexArray::unbind() const {
    GLCall(glBindVertexArray(0));
}

