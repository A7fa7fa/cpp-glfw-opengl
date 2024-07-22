#include "pre.h"
#include <math.h>
#include <fstream>
#include <sstream>
#include "renderer/Renderer.h"
#include "renderer/shader.h"
#include "renderer/Texture.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

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
    // no backwards compatible - need of vao
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

    // glfwSwapInterval(1);

    {

        std::vector<Vertex> trianglePoints;
        trianglePoints.reserve(4);
        trianglePoints.emplace_back( 0.5f,  0.5f, 0.0f,   0,   0,   0, 255, 1.0f, 1.0f); //top right
        trianglePoints.emplace_back( 0.5f, -0.5f, 0.0f,   0, 255,   0, 255, 1.0f, 0.0f); //bottom right
        trianglePoints.emplace_back(-0.5f, -0.5f, 0.0f,   0,   0, 255, 255, 0.0f, 0.0f); //bottom left
        trianglePoints.emplace_back(-0.5f,  0.5f, 0.0f, 255,   0,   0, 255, 0.0f, 1.0f); //top left

        std::vector<unsigned int> triangleMesh = {2, 3, 0, 0, 2, 1};


        // enabling blending
        GLCall(glEnable(GL_BLEND));
        // define blending function -> how alpa channel should blend pixxel colors
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA))


        VertexArray vao;
        VertexBuffer vb(trianglePoints.data(), trianglePoints.size() * sizeof(Vertex));
        VertexBufferLayout layout;
        Vertex::registerLayout(layout);
        vao.addBuffer(vb, layout);

        IndexBuffer ib(triangleMesh.data(), triangleMesh.size());

        Shader shader("res/shaders/basiccolor.shader");
        shader.unbind();
        Shader shader2("res/shaders/basic.shader");
        shader2.unbind();
        Shader shader3("res/shaders/basicuniform.shader");
        shader3.unbind();
        Shader shaderTexture("res/shaders/basictexture.shader");
        shaderTexture.unbind();

        Texture texture("res/textures/test.png");
        texture.bind(0);
        shaderTexture.bind();
        shaderTexture.setUniform1i("u_Texture", 0); // set uniform to textture slot



        // Model matrix: defines position, rotation and scale of the vertices of the model in the world.
        glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 0));
        // View matrix: defines position and orientation of the "camera".
        glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(-1.0f, 0, 0));
        // Projection matrix: Maps what the "camera" sees to NDC, taking care of aspect ratio and perspective.
        // is used to transform position into normalized display coordinates.
        glm::mat4 projectionMat = glm::ortho(-2.0f, 2.0f, -1.5f, 1.5f, -1.0f, 1.0f); // 4*3 aspect ratio

        glm::mat4 mvp = projectionMat * view * model;
        shaderTexture.setUniformMat4f("u_MVP", mvp);

        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

        ImGui::StyleColorsDark();
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init();


        float r, g, b, a;
        r = 1.0f;
        g = 0.1f;
        b = 0.1f;
        a = 1.0f;
        float incr = 0.002f;

        vao.unbind();
        vb.unbind();
        ib.unbind();
        shader3.unbind();
        Renderer renderer;

        int counter = 0;

        bool show_demo_window = true;
        bool show_another_window = false;
        ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);


        // Loop until the user closes the window
        while (!glfwWindowShouldClose(window)) {
            processInput(window);
            // clear screen. specify what to clear using defined clear color
            renderer.clear();

            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();


            // red += 0.02f;
            // glClearColor(fmod(red, 1), 0.3f, 1.0f, 0.0f);
            trianglePoints[0].pos.x = fmod(trianglePoints[0].pos.x + 0.00001f, 1.0);
            //  fmod((trianglePoints[0].pos[0] + 0.02f), 1);
            vb.bind();
            vb.updateData(trianglePoints.data(), trianglePoints.size() * sizeof(Vertex) );
            // updateBuffer(vert, 0, drawDetails.at(0) );

            shader3.bind();
            shader3.setUniform4f("u_Color", r, g, b, a);
            shaderTexture.bind();
            shaderTexture.setUniform4f("u_Color", r, g, b, a);



            // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
            if (show_demo_window)
                ImGui::ShowDemoWindow(&show_demo_window);

            // 2. Show a simple window that we create ourselves. We use a Begin/End pair to create a named window.
            {
                static float f = 0.0f;
                static int counter = 0;

                ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

                ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
                ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
                ImGui::Checkbox("Another Window", &show_another_window);

                ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
                ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

                if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
                    counter++;
                ImGui::SameLine();
                ImGui::Text("counter = %d", counter);

                ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
                ImGui::End();
            }

            // 3. Show another simple window.
            if (show_another_window)
            {
                ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
                ImGui::Text("Hello from another window!");
                if (ImGui::Button("Close Me"))
                    show_another_window = false;
                ImGui::End();
            }


            // Render here
            if (counter > 1000) {
                renderer.draw(vao, ib, shaderTexture);
            } else {
                renderer.draw(vao, ib, shader3);
            }
            counter++;

            r = fmod(r + incr, 1.0f);


            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            // Swap front and back buffers
            glfwSwapBuffers(window);

            // Poll for and process events
            glfwPollEvents();
        }
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();

    // Detach the console
    FreeConsole();


    return 0;
}