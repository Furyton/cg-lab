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

GLfloat points[1024][3], path[1024][3];

int cnt, cnt_p; // number of points

GLfloat xpos, ypos;

GLfloat radius, radius_y, _x, _y, _z;

const GLfloat PI = acos(-1);

GLfloat position[] = { 2.0f,0.0f,0.f,1.f };
enum MODE{
    DRAW, PATH, GO
} mode;

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void process_input(GLFWwindow *window) {
    if (mode != GO) return;

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        radius += 0.1;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        radius -= 0.1;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        radius_y += 0.1;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        radius_y -= 0.1;
    if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)
        _z += 0.1;
    if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS)
        _z -= 0.1;
    if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS)
        _x += 0.1;
    if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
        _x -= 0.1;
    if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS)
        _y += 0.1;
    if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS)
        _y -= 0.1;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (action != GLFW_PRESS)
	switch (key) {
        case GLFW_KEY_ESCAPE:
            glfwSetWindowShouldClose(window, GL_TRUE);
            break;
        case GLFW_KEY_ENTER:
            if (mode == DRAW) {
                mode = PATH;
                // points[cnt][0] = points[0][0];
                // points[cnt][1] = points[0][1];
                // cnt++;
            } else if (mode == PATH) {
                mode = GO;

                for (int i = cnt_p - 1; i >= 0; i--) {
                    path[i][0] -= path[0][0];
                    path[i][1] -= path[0][1];
                }
            }
            break;
        case GLFW_KEY_R:
            cnt = 0;
            cnt_p = 0;
            mode = DRAW;
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
	if (action == GLFW_PRESS && button == GLFW_MOUSE_BUTTON_LEFT && mode == PATH) {
        path[cnt_p][0] = xpos;
        path[cnt_p][1] = ypos;
        cnt_p++;
    }
    if (action == GLFW_PRESS && button == GLFW_MOUSE_BUTTON_LEFT && mode == GO) {
        position[0] = xpos;
        position[2] = ypos;
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
        process_input(window);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glDisable(GL_LIGHTING);
        glDisable(GL_LIGHT0);
        if (mode == DRAW) {
            glLoadIdentity();
            glColor3f(1, 1, 1);
            glBegin(GL_LINE_STRIP);
            for (int i = 0; i < cnt; i ++) {
                glVertex3fv(points[i]);
            }
            glEnd();
        } else if (mode == PATH) {
            glLoadIdentity();

            glColor3f(1, 1, 1);
            glBegin(GL_LINE_STRIP);
            for (int i = 0; i < cnt_p; i ++) {
                glVertex3fv(path[i]);
            }
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

            x = glm::translate(glm::mat4(1.0f), glm::vec3(_x, _y, _z));
            x = glm::rotate(x, radius, glm::vec3(1, 0, 0));
            x = glm::rotate(x, radius_y, glm::vec3(0, 1, 0));
            x = glm::lookAt(glm::vec3(0.0, 0, -1), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0)) * x;

            glLoadMatrixf(glm::value_ptr(x));

            for (int k = 0; k < cnt - 1; k++) {
                glBegin(GL_TRIANGLE_STRIP);

                for (int i = 0; i < cnt_p; i++) {
                    GLfloat x1 = points[k][0], y1 = 0, z1 = points[k][1],
                            x2 = points[k + 1][0], y2 = 0, z2 = points[k + 1][1],
                            theta1 = atan2(z1 , x1), theta2 = atan2(z2 , x2),
                            dx1 = path[i][0] * cos(theta1), dz1 = path[i][0] * sin(theta1),
                            dx2 = path[i][0] * cos(theta2), dz2 = path[i][0] * sin(theta2),
                            dy = path[i][1];
                    glVertex3f(x1 + dx1, y1 + dy, z1 + dz1);
                    glVertex3f(x2 + dx2, y2 + dy, z2 + dz2);
                }
                glEnd();
            }
            glDisable(GL_LIGHTING);
            glDisable(GL_LIGHT0);
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}