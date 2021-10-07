#include "header/attribute.hpp"

Attribute::Attribute() {
    glGenBuffers(1, &VBO);

    glGenVertexArrays(1, &VAO);

    glGenBuffers(1, &EBO);

    tot_attr_size = 0;
    vertices_size = 0;
    indices_size = 0;
}

void Attribute::add_attr(int layout, int size) {
    attr.push_back((struct attribute_info){layout, size});

    tot_attr_size += size;
}

void Attribute::set_vertices(int size, void* data) {
    vertices_size = size;
    vertices = data;
}
void Attribute::set_indices(int size, void* data) {
    indices_size = size;
    indices = data;
}

void Attribute::build(unsigned int usage) {
    glBindVertexArray(VAO);

    if (vertices_size == 0) {
        std::cerr << "no vertices\n";

        exit(-1);
    }
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices_size, vertices, usage);

    if (indices_size != 0) {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_size, indices, usage);
    }

    int offset = 0;

    for (auto x : attr) {
        glVertexAttribPointer(x.layout, x.size, GL_FLOAT, GL_FALSE, tot_attr_size * sizeof(float), (void*) (offset * sizeof(float)));

        offset += x.size;

        glEnableVertexAttribArray(x.layout);
    }

    glBindVertexArray(0);
}
void Attribute::activate() {
    glBindVertexArray(VAO);
}
void Attribute::deactivate() {
    glBindVertexArray(0);
}
void Attribute::destroy() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    if (indices_size != 0) {
        glDeleteBuffers(1, &EBO);
    }
}