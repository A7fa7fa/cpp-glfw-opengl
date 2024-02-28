#pragma once
#include <GLFW/glfw3.h>

void glfw_error_callback(int error, const char* description);
void glfw_framebuffer_size_callback(GLFWwindow* window, int w, int h);
