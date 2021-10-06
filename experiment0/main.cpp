#include <math.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "header/shader.hpp"
#include "header/frame.hpp"
#include "header/attribute.hpp"


float vertices[] = {
    // positions          // colors
     0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,
     0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,
    -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,
    -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,
}; 

unsigned int indices[] = {
    0, 1, 3,
    1, 2, 3
};

int main() {

    Window window;

    if (window.init_window(800, 600)) {
        return -1;
    }

    Shader shader("./experiment0/shaders/shader.vs", "./experiment0/shaders/shader.fs");

    Attribute attr = Attribute();

    attr.set_vertices(sizeof(vertices), vertices);
    attr.set_indices(sizeof(indices), indices);
    attr.add_attr(0, 3);
    attr.add_attr(1, 3);

    attr.build(GL_DYNAMIC_DRAW);

    while(!window.should_close())
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        float t = glfwGetTime();
        // draw our first triangle
        shader.use();
        
        attr.activate();

        // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        shader.setFloat("offset", sin(t));
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        // glDrawArrays(GL_TRIANGLES, 0, 6);
        attr.deactivate();

        window.swap_buffers();
        window.polling_events();
    }

    attr.destroy();

    window.close();

    return 0;
}