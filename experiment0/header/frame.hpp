#ifndef FRAME_H
#define FRAME_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "callbacks.hpp"

class Window {
private:
    GLFWwindow *window;
    int major = 3, minor = 3;
    int width = 800, height = 600;

    void set_window_hint();

public:
    int init_window(int width, int height);
    int should_close();
    void close();
    void swap_buffers();
    void polling_events();
};

#endif