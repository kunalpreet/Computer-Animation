#ifndef UNIFORM_MATRIX_H
#define UNIFORM_MATRIX_H

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


#include <string>
#include "Uniform.h"
#include "../../Libraries/Eigen/Dense"

class UniformMatrix: public Uniform {
public:
	float data[16] = {};

public:
	UniformMatrix(std::string name);
	void loadMatrix(Eigen::Matrix4f matrix);
	void loadMatrix(float data[16]);
};

#endif