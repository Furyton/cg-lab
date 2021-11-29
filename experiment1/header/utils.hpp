#include <stdlib.h>
#include <iostream>
#include <fstream>

struct Vertex {
    float v[3];

    Vertex() {}
    Vertex(Vertex& o) {
        set(o);
    }
    void set(Vertex& o) {
        for (int i = 0; i < 3; i++)
            v[i] = o.v[i];
    }
};

struct Face {
    Vertex p[4];

    void set(Vertex& a, Vertex& b, Vertex& c, Vertex& d) {
        p[0].set(a);
        p[1].set(b);
        p[2].set(c);
        p[3].set(d);
    }
};

float* get_vertex(float p[], float height, float width, float depth);
