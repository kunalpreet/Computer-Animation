#ifndef VBO_H
#define VBO_H

#ifdef __APPLE__
#  include <OpenGL/gl3.h>
#else
#  include <GL/glew.h>   
#  include <GL/gl.h>
#endif
#include <vector>

class Vbo {
// variables
private:
    GLuint vboId; // stores ID
    int type;

    // constructor
    Vbo(GLuint, int);
// functions
public:
    Vbo();
    static Vbo create(int); 
    void bind();
    void unbind();

    void storeData(std::vector<float>);
    void storeData(std::vector<int>);
    void deleteBuffers();
};

#endif