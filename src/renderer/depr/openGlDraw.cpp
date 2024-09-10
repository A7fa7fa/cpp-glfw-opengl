#include "openGlDraw.h"
#include <GL/glew.h>

void draw(const std::vector<DrawDetails>& details) {

    for (int i = 0; i < details.size(); i++) {
        glBindVertexArray(details.at(i).vao);
        glDrawElements(GL_TRIANGLES, details.at(i).numElements, GL_UNSIGNED_INT, nullptr);
    }

    glBindVertexArray(0);
}
