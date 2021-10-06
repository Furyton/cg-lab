#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <vector>
#include <iostream>


class Attribute {
private:
    unsigned int VBO, VAO, EBO;

    int vertices_size, indices_size;
    void *vertices, *indices;

    int tot_attr_size;
    
    struct attribute_info{
        int layout, size;
    };

    std::vector<struct attribute_info> attr;
public:
    Attribute();
    
    void add_attr(int layout, int size);
    
    void set_vertices(int size, void* data);
    
    void set_indices(int size, void* data);

    // usage: GL_STATIC_DRAW, GL_DYNAMIC_DRAW...
    void build(unsigned int usage);    
    
    void activate();
    
    void deactivate();
    
    void destroy();
};

#endif