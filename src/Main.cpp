#include "pre.h"
#include <math.h>
#include <fstream>
#include <sstream>

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

struct ShaderProgramSource {
    std::string vertexSource;
    std::string fragmentSource;
};

static ShaderProgramSource parseShader(const std::string& filePath) {
    enum class ShaderType {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };
    const char* shaderTypeName[2] = {"vertex", "fragment"};

    std::fstream stream(filePath); // this opens file

    std::string line;
    std::stringstream ss[2]; // create two stringstreams. one fro fragment, one for vertex shader
    ShaderType currType = ShaderType::NONE;
    while(getline(stream, line)) {
        if (line.find("#shader") != std::string::npos) { // npos is not a valid position so find was not successfull
            if (line.find(shaderTypeName[(int)ShaderType::VERTEX]) != std::string::npos) {
                currType = ShaderType::VERTEX;
            } else if (line.find(shaderTypeName[(int)ShaderType::FRAGMENT]) != std::string::npos) {
                currType = ShaderType::FRAGMENT;
            } else {
                currType = ShaderType::NONE;
            }
        } else {
            ss[(int)currType] << line << '\n';
        }
    }
    return {ss[0].str(), ss[1].str()};
}

int main(int argc, char** argv) {

    initConsole();

    GLFWwindow* window;

    glfwSetErrorCallback(glfw_error_callback);

    /* Initialize the library */
    if (!glfwInit()) {
        std::cout << "Could not init glfw" << std::endl;
        FreeConsole();
        return -1;
    }

    std::cout << "Glfw initilazed " << std::endl;

    // define used opengl version
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
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
    // resizes viewport size on window siz change
    glfwSetFramebufferSizeCallback(window, glfw_framebuffer_size_callback);

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

    // enable debug messages
    glEnable(GL_DEBUG_OUTPUT);
    // register gl error callback function
    glDebugMessageCallback(opengl_debug_message_callback, nullptr);
    // to enable all types of debug messages
    glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);

    // set size to draw to
    glViewport(0, 0, bufferWidth, bufferHeight);

    // set used clear color when used glClear
    glClearColor(0.5f, 0.3f, 1.0f, 0.0f);

    float red = 0.02f;

    std::vector<DrawDetails> drawDetails;
    drawDetails.reserve(1);
    Vertex vert = Vertex(0.5f, -0.5f, 0.0f);
    {
        std::vector<Vertex> trianglePoints;
        trianglePoints.reserve(4);
        trianglePoints.emplace_back(vert);
        trianglePoints.emplace_back(-0.5f, -0.5f, 0.0f, 0, 255, 0, 255);
        trianglePoints.emplace_back( 0.0f,  0.5f, 0.0f, 0, 0, 255, 255);
        trianglePoints.emplace_back( 1.0f,  0.5f, 0.0f, 0, 0, 0, 255);

        std::vector<unsigned int> triangleMesh = {0, 1, 2, 0, 1, 3};

        drawDetails.emplace_back(uploadMesh(trianglePoints, triangleMesh));
    }


    ShaderProgramSource source = parseShader("res/shaders/basiccolor.shader");
    std::cout << "Vertex..." << std::endl;
    std::cout << source.vertexSource << std::endl;
    std::cout << "Fragment..." << std::endl;
    std::cout << source.fragmentSource << std::endl;

    unsigned int shader = createShader(source.vertexSource, source.fragmentSource);
    if (!shader) {
        std::cout << "Could not compile shader" << std::endl;
        std::cin.get();
        return -1;
    }
    glUseProgram(shader);

    // Loop until the user closes the window
    while (!glfwWindowShouldClose(window)) {
        processInput(window);

        // red += 0.02f;
        // glClearColor(fmod(red, 1), 0.3f, 1.0f, 0.0f);
        vert.pos[0] += fmod((vert.pos[0] + 0.02f), 1);
        updateBuffer(vert, 0, drawDetails.at(0) );

        // clear screen. specify what to clear using defined clear color
        glClear(GL_COLOR_BUFFER_BIT);
        // Render here
        draw(drawDetails);

        // Swap front and back buffers
        glfwSwapBuffers(window);

        // Poll for and process events
        glfwPollEvents();
    }

    // not strictly neccessary here because programm cleans up after termination
    unloadMesh(drawDetails);
    glDeleteProgram(shader);

    glfwTerminate();

    // Detach the console
    FreeConsole();


    return 0;
}