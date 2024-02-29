#include "callback.h"
#include <iostream>

void glfw_error_callback(int error, const char* description) {
    std::cout << "Glfw Error : " << error << " " << description << std::endl;
    throw ("glfw error");
}

void glfw_framebuffer_size_callback(GLFWwindow* window, int w, int h) {
    std::cout << "resize window" << std::endl;
    // otherwise viewport would stay the same size after resizing the window
    glViewport(0, 0, w, h);
}

void GLAPIENTRY opengl_debug_message_callback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam) {
    std::cout << "OpenGL Debug Message [Source: " << source << ", Type: " << type << ", ID: " << id << ", Severity: " << severity << "]: " << message << std::endl;
}