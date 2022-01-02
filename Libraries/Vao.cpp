
#define GL_GLEXT_PROTOTYPES
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

#include <vector>
#include "Vbo.h"
#include "Vao.h"

#include <iostream>

Vao::Vao() {
    glGenVertexArrays(1, &id);
}


int Vao::getIndexCount(){
    return indexCount;
}

void Vao::bind() {
    glBindVertexArray(id);
}

void Vao::unbind() {
    glBindVertexArray(0);
}

void Vao::bind(std::vector<int> attributes){
    bind();
    for (int i : attributes) {
        glEnableVertexAttribArray(i);
    }
}

void Vao::unbind(std::vector<int> attributes){
    for (int i : attributes) {
        glDisableVertexAttribArray(i);
    }
    unbind();
}

void Vao::createIndexBuffer(std::vector<int> indices){
    this->indexVbo = Vbo::create(GL_ELEMENT_ARRAY_BUFFER);
    indexVbo.bind();
    indexVbo.storeData(indices);
    this->indexCount = (int) indices.size();
}

/**
 * @brief 
 * 
 * @param attribute  the type of attribute determines what array we bind this 
 * @param data      array or vector of data
 * @param attrSize  how many values for each attribute
 */
void Vao::createAttribute(int attribute, std::vector<float> data, int attrSize){
    Vbo dataVbo = Vbo::create(GL_ARRAY_BUFFER);
    dataVbo.bind();         // create and bind a new buffer
    dataVbo.storeData(data);// store data into that buffer
    glVertexAttribPointer(attribute, attrSize, GL_FLOAT, false, attrSize * BYTES_PER_FLOAT, 0); // reading from current buffer into vertexattrib
    dataVbo.unbind();
    dataVbos.push_back(dataVbo);        // after creating attribute for vbo, push back
}

/**
 * @brief 
 * 
 * @param attribute the type of attribute determines what array we bind this 
 * @param data      array or vector of data
 * @param attrSize how many values for each attribute
 */
void Vao::createIntAttribute(int attribute, std::vector<int> data, int attrSize){
    Vbo dataVbo = Vbo::create(GL_ARRAY_BUFFER);
    dataVbo.bind();
    dataVbo.storeData(data);
    glVertexAttribIPointer(attribute, attrSize, GL_INT, attrSize * BYTES_PER_INT, 0);
    dataVbo.unbind();
    dataVbos.push_back(dataVbo);
}

void Vao::deleteVertexArrays() {
    glDeleteVertexArrays(1, &id);
    for(Vbo vbo : dataVbos){
        vbo.deleteBuffers();
    }
    indexVbo.deleteBuffers();
}
