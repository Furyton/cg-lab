#ifndef FRAME_H
#define FRAME_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "callbacks.hpp"
#include "transformers.hpp"

class MyWindow {
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
    void process_input(Transformers& t);
};

#endif