#ifndef UNIFORM_MAT4ARRAY_H
#define UNIFORM_MAT4ARRAY_H

#ifdef __APPLE__
#  include <OpenGL/gl3.h>
#  include <OpenGL/glu.h>
#  include <GLUT/glut.h>
#else
#  include <GL/glew.h>
#  include <GL/gl.h>
#  include <GL/glu.h>
#  include <GL/freeglut.h>
#endif


#include <vector>
#include <string>
#include "UniformMatrix.h"
#include "../../Libraries/Eigen/Dense"


class UniformMat4Array : public Uniform {
public:
	std::vector<UniformMatrix> uniformMatrices;

public:
	UniformMat4Array(std::string name, int size);
	void storeUniformLocation(GLuint programID);
	void loadMatrixArray(std::vector<Eigen::Matrix4f> matrices);
};

#endif