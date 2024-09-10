#pragma once

class VertexBuffer {
    private:
        unsigned int rendererId;
    public:
        VertexBuffer(const void* data, unsigned int size);
        ~VertexBuffer();

        void updateData(const void* data, unsigned int size) const;

        void bind() const;
        void unbind() const;
};
