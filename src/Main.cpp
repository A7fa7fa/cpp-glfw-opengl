#include <iostream>
#include "strings.h"
#include <GLFW/glfw3.h>

int main(int argc, char** argv) {

	int res = glfwInit();
	if (res == GLFW_FALSE) {
		std::cout << "Could not init glfw" << std::endl;
		return -1;
	}

	std::cout << "Glfw initilazed " << res << std::endl;

	GLFWwindow* window = glfwCreateWindow(640, 480, "my title", nullptr, nullptr);
    if(!window)
    {
        glfwTerminate();
        return -1;
    }

	std::cout << "Window created" << std::endl;

    glfwMakeContextCurrent(window);

    // Application (Game) loop
    while(!glfwWindowShouldClose(window))
    {
        // glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

	// charArray();
	// stdString();

	glfwTerminate();

	return 0;
}