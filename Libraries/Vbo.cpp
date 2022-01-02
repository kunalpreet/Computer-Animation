
#ifdef __APPLE__
#  include <OpenGL/gl3.h>
#  include <OpenGL/glu.h>
// I don't know if glext.h is in OpenGL or GLUT
#  include <OpenGL/glext.h>
#  include <GLUT/glut.h>
#else
#  define GL_GLEXT_LEGACY
#  define GL_GLEXT_PROTOTYPES
#  include <GL/glew.h>
#  include <GL/gl.h>
#  include <GL/glu.h>
#  include <GL/freeglut.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include "Vbo.h"
#include <vector>
#include <algorithm> // vec to array

// constructor
/**
 * @brief Construct a new Vbo:: Vbo object
 * 
 * @param vboId 
 * @param type GL_ARRAY_BUFFER
 */
Vbo::Vbo(GLuint vboId, int type) {
    this->vboId = vboId;
    this->type = type;
}

Vbo::Vbo() {
    create(GL_ARRAY_BUFFER);
}

// functions
/**
 * @brief static function that calls constructor
 * 
 * @param type GL_ARRAY_BUFFER, GL_ELEMENT_ARRAY_BUFFER
 * @return Vbo 
 */
Vbo Vbo::create(int type) {
    GLuint vbo;
    glGenBuffers(1, &vbo);
    return Vbo(vbo, type);
}

/**
 * @brief Binds VBO to be usable - type = GL_ARRAY_BUFFER generally
 * 
 */
void Vbo::bind() {  
    glBindBuffer(type, this->vboId);
}

void Vbo::unbind() {
    glBindBuffer(type, 0);
}

/**
 * @brief parses data and then binds it to buffer. bind() must be run first
 * 
 * @param data 
 */
void Vbo::storeData(std::vector<float> data) {
    // pass type, bytesize of array, pointer to array, then how to draw
    float arrData[(int)data.size()];
    std::copy(data.begin(), data.end(), arrData);
    glBufferData(type, sizeof(float) * (int) data.size(), arrData, GL_STATIC_DRAW);
}

void Vbo::storeData(std::vector<int> data) {
    // pass type, bytesize of array, pointer to array, then how to draw
    int arrData[(int)data.size()];
    std::copy(data.begin(), data.end(), arrData);
    glBufferData(type, sizeof(int) * (int) data.size(), arrData, GL_STATIC_DRAW);
}

// void Vbo::storeData(IntBuffer data);
// void Vbo::storeData(FloatBuffer data);

void Vbo::deleteBuffers() {
    glDeleteBuffers(1, &vboId);
}
