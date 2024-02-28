#include "openGlLoader.h"
#include <GL/glew.h>

DrawDetails uploadMesh(const std::vector<Vertex>& verticis, const std::vector<uint32_t> elem) {
    if (verticis.empty() || elem.empty()) {
        throw("empty vector");
    }

    // vertext array object, vertex buffer object, element buffer object
    uint32_t VAO, VBO, EBO;

    // generates vertext and asignes id to AO
    glGenVertexArrays(1, &VAO);
    // switches context to work on. every following command is with this vao context
    glBindVertexArray(VAO);

    // generates a buffer object for the vertex buffer (VBO)
    glGenBuffers(1, &VBO);
    // binds it to context as an array buffer
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // uploads vertex data to GPU.
    // type of buffer, size in memory of verts data, pointer to start of data same as (&verticis[0]), draw mode -> we dont change the data after uploading so static draw
    glBufferData(GL_ARRAY_BUFFER, verticis.size() * sizeof(Vertex), verticis.data(), GL_STATIC_DRAW);
    // defines verts in buffer.
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, pos));
    glEnableVertexAttribArray(0);

    // generates a buffer object for the element buffer (EBO)
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    // describe buffer data
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, elem.size()*sizeof(uint32_t), elem.data(), GL_STATIC_DRAW);

    // after finish changeing change back to default context
    glBindVertexArray(0);
    // after uploading vbo and ebo can be deleted
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    return DrawDetails(VAO, elem.size());
}

void unloadMesh(std::vector<DrawDetails>& details) {
    for (int i = 0; i < details.size(); i++) {
        glDeleteBuffers(1, &details.at(i).vao);
    }
    details.clear();
}

