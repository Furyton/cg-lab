#include "header/utils.hpp"

float* get_vertex(float height, float width, float depth) {
    Vertex v[8];

    float p[] = {-0.5 * height, -0.5 * width, -0.5 * depth};

    int t = 0;
    for (int i = 0; i < 2; i++)
    for (int j = 0; j < 2; j++)
    for (int k = 0; k < 2; k++) {
        v[t].v[0] = p[0] + i * depth;
        v[t].v[1] = p[1] + j * width;
        v[t].v[2] = p[2] + k * height;
        t++;
    }

    Face faces[6];

    faces[0].set(v[0], v[2], v[6], v[4]);
    faces[1].set(v[1], v[3], v[7], v[5]);

    faces[2].set(v[3], v[2], v[6], v[7]);
    faces[3].set(v[1], v[0], v[4], v[5]);

    faces[4].set(v[5], v[7], v[6], v[4]);
    faces[5].set(v[1], v[3], v[2], v[0]);

    float* vertices = new float[12 * 9]();
    t = 0;

    int indices[6] = {0, 1, 2, 2, 3, 0};

    for (int i = 0; i < 6; i++)
    for (int j = 0; j < 6; j++)
    for (int k = 0; k < 3; k++)
        vertices[t++] = faces[i].p[indices[j]].v[k];

    return vertices;
}