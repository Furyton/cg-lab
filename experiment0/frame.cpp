#include "header/frame.hpp"

void Window::set_window_hint() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

int Window::init_window(int width, int height) {
    this->width = width;
    this->height = height;

    set_window_hint();

    GLFWwindow* window = glfwCreateWindow(width, height, "LearnOpenGL", NULL, NULL);
    if (!window) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -2;
    }

    glViewport(0, 0, width, height);

    this->window = window;

    glEnable(GL_DEPTH_TEST);

    return 0;
}

int Window::should_close() {
    return glfwWindowShouldClose(window);
}

void Window::close() {
    glfwTerminate();
}

void Window::swap_buffers() {
    glfwSwapBuffers(window);
}

void Window::polling_events() {
    glfwPollEvents();
}

void Window::process_input() {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}