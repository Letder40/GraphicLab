#include "globjects/Window.h"
#include <GLFW/glfw3.h>

#include <cstdlib>
#include <print>

static void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
    (void)window;
}

Window::Window(uint32_t width, uint32_t height, const char* title) {
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

    GLFWwindow* window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (!window) {
        std::print(stderr, "Error: Failled to create a windows\n");
        glfwTerminate();
        exit(1);
    }

    glfwMakeContextCurrent(window);

    glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    this->window = window;
}

Window::~Window() { glfwTerminate(); };

int Window::should_close() { return glfwWindowShouldClose(window); };

void Window::swap_buffers() { glfwSwapBuffers(window); };

void Window::poll_events() { glfwPollEvents(); };

void Window::process_input() {
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) glfwSetWindowShouldClose(window, true);
}
