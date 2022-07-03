#include "sqlutil.h"
#include "entry.h"
#include "logbook.h"
#include "menu.h"
#include "gui.h"
// glad§
#include <glad/glad.h>
// include glfw3.h
#include <GLFW/glfw3.h>

#define ever ;;

// Make a logging function
void log(const char* msg) {
    printf("%s\n", msg);
}

auto main(int argc, char** argv) -> int{
    // Initialize glfw3
    log("Initializing glfw3");
    if (!glfwInit())
        return -1;
    
    // Create a windowed mode window and its OpenGL context
    // GL 3.0 + GLSL 130. https://www.khronos.org/opengl/wiki/Core_Language_(GLSL)
    const std::string glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    log("Creating window");
    GLFWwindow* window = glfwCreateWindow(640, 480, "Hello Imgui", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }
    // Make the window's context current
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    log("Initializing glad");
    // glad
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Unable to context to OpenGL\n";
        return -1;
    }
    log("Initializing imgui");
    GUI gui;
    gui.init(window, glsl_version);
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        gui.new_frame();
        gui.update();
        gui.render();
        glfwSwapBuffers(window);
    }
    log("Shutting down");
    gui.shutdown();
    return 0;
}