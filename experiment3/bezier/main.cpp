#include <math.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <stdio.h>
#include <fstream>

int width = 800, height = 800;

GLfloat ctrlpoints[1024][3];

int cnt; // number of ctrl points

GLfloat xpos, ypos;

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (action != GLFW_PRESS)
		return;
	switch (key) {
        case GLFW_KEY_ESCAPE:
            glfwSetWindowShouldClose(window, GL_TRUE);
            break;
        default:
            break;
    }
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
	if (action == GLFW_PRESS && button == GLFW_MOUSE_BUTTON_LEFT) {
        ctrlpoints[cnt][0] = xpos;
        ctrlpoints[cnt][1] = ypos;
        cnt++;
    }
	return;
}

void cursor_position_callback(GLFWwindow* window, double x, double y) {
	xpos=float((x-width/2)/width)*2;
	ypos=float(0-(y-height/2)/height)*2;
	return;
}

int main() {
    glfwInit();

    GLFWwindow* window = glfwCreateWindow(width, height, "LearnOpenGL", NULL, NULL);
    if (!window) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetCursorPosCallback(window, cursor_position_callback);
    glfwSetKeyCallback(window, key_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -2;
    }

    glViewport(0, 0, width, height);

    // glEnable(GL_DEPTH_TEST);
    // glEnable(GL_BLEND);
    // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glShadeModel(GL_FLAT); 

    glEnable(GL_MAP1_VERTEX_3);

    while(!glfwWindowShouldClose(window)) {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glLoadIdentity();
        glColor3f(1.0, 0.0, 0.0);

        int i, j;
        if (cnt >= 3) {
            for (i = 0; i < cnt - 3 + 1; i+=2) {
                glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 3, &ctrlpoints[i][0]);

                glBegin(GL_LINE_STRIP);

                for (j = 0; j <= 1000; j++)
                    glEvalCoord1f((GLfloat)j/ 1000.0);
                glEnd();
            }
        }

        glPointSize(5.0);
        glBegin(GL_POINTS);
        for (i = 0; i < cnt; i++)
            glVertex3fv(&ctrlpoints[i][0]);
        glEnd();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}