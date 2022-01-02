#ifndef VAO_H
#define VAO_H


#ifdef __APPLE__
#  include <OpenGL/gl3.h>    
#else
#  include <GL/glew.h>    
#  include <GL/gl.h>    // GLuint
#endif

#include <vector>
#include "Vbo.h"

class Vao {
// values
public:
    GLuint id = 0;
    Vao();

private:
    static const int BYTES_PER_FLOAT = 4;
    static const int BYTES_PER_INT = 4;
    
    std::vector<Vbo> dataVbos;
    int indexCount;
    Vbo indexVbo;
// functions

public:
    static Vao& create();
    int getIndexCount();

    void bind();
    void unbind();
    void bind(std::vector<int>);
    void unbind(std::vector<int>);

    void createIndexBuffer(std::vector<int>);

    void createAttribute(int, std::vector<float>, int);
    void createIntAttribute(int, std::vector<int>, int);
    void deleteVertexArrays();
};
#endif