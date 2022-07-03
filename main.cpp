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
    // Setup window
	if (!glfwInit())
		return 1;

	// GL 3.0 + GLSL 130
	const char *glsl_version = "#version 130";
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

	// Create window with graphics context
	GLFWwindow *window = glfwCreateWindow(1280, 720, "Logbook", NULL, NULL);
	if (window == NULL)
		return 1;
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1); // Enable vsync

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))  // tie window context to glad's opengl funcs
		throw("Unable to context to OpenGL");

	int screen_width, screen_height;
	glfwGetFramebufferSize(window, &screen_width, &screen_height);
	glViewport(0, 0, screen_width, screen_height);

	GUI gui;
	gui.init(window, glsl_version);
	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
		glClear(GL_COLOR_BUFFER_BIT);
		gui.new_frame();
		gui.update();
		gui.render();
		glfwSwapBuffers(window);
	}
	gui.shutdown();
    return 0;
}