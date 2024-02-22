#include "pre.h"
#include <math.h>

void initConsole() {
    // Allocate a new console
    AllocConsole();

    // Attach the console to this process
    AttachConsole(GetCurrentProcessId());

    // Redirect standard input/output streams to the console
    freopen("CONIN$", "r", stdin);
    freopen("CONOUT$", "w", stdout);
    freopen("CONOUT$", "w", stderr);

}

int main(int argc, char** argv) {

    initConsole();

    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit()) {
        std::cout << "Could not init glfw" << std::endl;
        FreeConsole();
        return -1;
    }

    std::cout << "Glfw initilazed " << std::endl;

    // define used opengl version
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // no backwards compatible
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // allow compatible
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window) {
        std::cout << "Could not create window" << std::endl;
        glfwTerminate();
        FreeConsole();
        return -1;
    }
    std::cout << "Window created" << std::endl;

    int bufferWidth, bufferHeight;
    glfwGetFramebufferSize(window, &bufferWidth, &bufferHeight);

    // Make the window's context current. set context for glfw to use
    glfwMakeContextCurrent(window);

    // allow modern extension features - optional
    glewExperimental = GL_TRUE;

    // can only be used after a valid context is present
    // GLenum err = glewInit();
    if (GLEW_OK != glewInit()) {
        // fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
        std::cout << "Could not init glew" << std::endl;
        FreeConsole();
        return -1;
    }

    // set size to draw to
    glViewport(0, 0, bufferWidth, bufferHeight);

    // set used clear color when used glClear
    glClearColor(0.5f, 0.3f, 1.0f, 0.0f);

    float red = 0.02f;
    // Loop until the user closes the window
    while (!glfwWindowShouldClose(window)) {
        red += 0.02f;
        glClearColor(fmod(red, 1), 0.3f, 1.0f, 0.0f);

        // Render here
        // specify what to clear using defined clear color
        glClear(GL_COLOR_BUFFER_BIT);

        // Swap front and back buffers
        glfwSwapBuffers(window);

        // Poll for and process events
        glfwPollEvents();

    }

    glfwTerminate();

    // Detach the console
    FreeConsole();


    return 0;
}