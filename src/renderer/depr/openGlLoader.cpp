#include "openGlLoader.h"
#include <GL/glew.h>
#include <string>
#include "../Renderer.h"
#include "../VertexBuffer.h"
#include "../IndexBuffer.h"

DrawDetails uploadMesh(const std::vector<Vertex>& verticis, const std::vector<unsigned int> elem) {
    if (verticis.empty() || elem.empty()) {
        throw("empty vector");
    }

    // vertext array object, vertex buffer object, element buffer object
    unsigned int VAO, VBO, EBO;

    // generates 1 vertext and asignes id to AO
    GLCall(glGenVertexArrays(1, &VAO));
    // switches context to work on. every following command is with this vao context
    glBindVertexArray(VAO);

    // generates a buffer object for the vertex buffer (VBO)
    glGenBuffers(1, &VBO);
    // binds it to context as an array buffer
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // uploads vertex data to GPU.
    // type of buffer, size in memory of verts data, pointer to start of data same as (&verticis[0]), draw mode -> we dont change the data after uploading so static draw
    glBufferData(GL_ARRAY_BUFFER, verticis.size() * sizeof(Vertex), verticis.data(), GL_STATIC_DRAW);

    // defines verts layout of buffer. so opengl can understand the data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, pos));
    // must enable this attribute definition. or the glVertexAttribPointer is ignore
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, color));
    glEnableVertexAttribArray(1);

    // generates 1 buffer object for the element buffer (EBO) (in general it is called an index buffer)
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    // describe buffer data
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, elem.size()*sizeof(unsigned int), elem.data(), GL_STATIC_DRAW);

    // after finish changeing change back to default context
    // after uploading vbo and ebo can be unbound
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // glDeleteBuffers(1, &VBO);
    // glDeleteBuffers(1, &EBO);

    return DrawDetails(VAO, VBO, elem.size());
}

void unloadMesh(std::vector<DrawDetails>& details) {
    for (int i = 0; i < details.size(); i++) {
        glDeleteBuffers(1, &details.at(i).vao);
    }
    details.clear();
}

void updateBuffer(const Vertex& verticis, int verOffset, const DrawDetails& drawDetails) {
    // glBindBuffer(GL_ARRAY_BUFFER, drawDetails.vb. vbo);

    glBufferSubData(GL_ARRAY_BUFFER, verOffset * sizeof(Vertex), sizeof(verticis), (const void*)offsetof(Vertex, pos));
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

