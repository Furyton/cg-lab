#include "header/frame.hpp"

void MyWindow::set_window_hint() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

int MyWindow::init_window(int width, int height) {
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
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    return 0;
}

int MyWindow::should_close() {
    return glfwWindowShouldClose(window);
}

void MyWindow::close() {
    glfwTerminate();
}

void MyWindow::swap_buffers() {
    glfwSwapBuffers(window);
}

void MyWindow::polling_events() {
    glfwPollEvents();
}

void MyWindow::process_input(Transformers &t) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }

    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
        t.reset_acc_rotate();
        t.reset_acc_trans();

        return;
    }

    const float speed = 0.01f;

    float delta_x = 0.0f, delta_y = 0.0f, delta_z = 0.0f, norm = t.get_acc_trans_norm();

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        delta_y += speed * norm;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        delta_y -= speed * norm;

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        delta_x -= speed * norm;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        delta_x += speed * norm;

    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        delta_z -= speed * norm;
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        delta_z += speed * norm;
    
    t.input_translate(delta_x, delta_y, delta_z);

    const float radians = 0.05f;

    if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS)
        t.input_rotate(-radians, 1.0f, 0.0f, 0.0f);
    if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)
        t.input_rotate(radians, 1.0f, 0.0f, 0.0f);

    if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS)
        t.input_rotate(-radians, 0.0f, 1.0f, 0.0f);
    if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS)
        t.input_rotate(radians, 0.0f, 1.0f, 0.0f);

    if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS)
        t.input_rotate(-radians, 0.0f, 0.0f, 1.0f);
    if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS)
        t.input_rotate(radians, 0.0f, 0.0f, 1.0f);
}