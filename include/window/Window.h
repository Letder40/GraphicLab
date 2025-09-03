#ifndef WINDOW_H
#define WINDOW_H

#include <GLFW/glfw3.h>

class Window {
    GLFWwindow* window;

    public:
        Window(uint32_t width, uint32_t height, const char* title);
        ~Window();

        int should_close();
        void swap_buffers();
        void poll_events();
        void process_input();
};

#endif
