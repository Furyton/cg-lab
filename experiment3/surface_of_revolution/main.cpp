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

GLfloat points[1024][3];

int cnt; // number of points

GLfloat xpos, ypos;

GLfloat radius;

const GLfloat PI = acos(-1);

GLfloat position[] = { 2.0f,0.0f,0.f,1.f };
enum MODE{
    DRAW, SPIN
} mode;

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
        case GLFW_KEY_ENTER:
            mode = SPIN;
            break;
        case GLFW_KEY_W:
            radius += 0.1;
            break;
        case GLFW_KEY_S:
            radius -= 0.1;
            break;
        default:
            break;
    }
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
	if (action == GLFW_PRESS && button == GLFW_MOUSE_BUTTON_LEFT && mode == DRAW) {
        points[cnt][0] = xpos;
        points[cnt][1] = ypos;
        cnt++;
    }
	if (action == GLFW_PRESS && button == GLFW_MOUSE_BUTTON_LEFT && mode == SPIN) {
        position[0] = xpos * 2;
        position[2] = ypos * 2;
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

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);


    while(!glfwWindowShouldClose(window)) {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        if (mode == DRAW) {
            glLoadIdentity();

            glBegin(GL_LINE_STRIP);
            for (int i = 0; i < cnt; i ++) {
                glVertex3fv(points[i]);
            }
            glEnd();

            glBegin(GL_LINE_STRIP);

            glVertex3f(0, 1, 0);
            glVertex3f(0, -1, 0);
            glEnd();
        } else {
            glEnable(GL_LIGHTING);
            glEnable(GL_LIGHT0);

            GLfloat ambient[] = { 1.0f,1.0f,1.0f,1.f };
            GLfloat diffuse[] = { .9f,.9f,.9f,1.f };
            GLfloat specular[] = { .5f,.5f,.5f,1.f };

            glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
            glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
            glLightfv(GL_LIGHT0, GL_SPECULAR, specular);

            glLightfv(GL_LIGHT0, GL_POSITION, position);

            glMatrixMode(GL_PROJECTION);
            auto x = glm::perspective(90.0f, 1.0f, 0.5f, 20.0f);
            glLoadMatrixf(glm::value_ptr(x));

            glMatrixMode(GL_MODELVIEW);
            x = glm::lookAt(glm::vec3(0.0, 1, -1), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0)) * glm::rotate(glm::mat4(1.0f), radius, glm::vec3(1, 0, 0));
            glLoadMatrixf(glm::value_ptr(x));
            glBegin(GL_LINE_STRIP);
            glVertex3f(0, 1, 0);
            glVertex3f(0, -1, 0);
            glEnd();

            for (int k = 0; k < cnt - 1; k++) {
                glBegin(GL_TRIANGLE_STRIP);

                for (int i = 0; i <= 1000; i++) {
                    GLfloat theta = 2.0 * i / 1000.0 * PI, x1 = points[k][0], y1 = points[k][1], x2 = points[k + 1][0], y2 = points[k + 1][1];

                    glVertex3f(x1 * cos(theta), y1, x1 * sin(theta));
                    glVertex3f(x2 * cos(theta), y2, x2 * sin(theta));
                }
                glEnd();
            }
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}