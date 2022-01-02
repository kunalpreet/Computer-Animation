#ifndef UNIFORM_VEC4_H
#define UNIFORM_VEC4_H

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

class UniformVec4: public Uniform {
private:
	Eigen::Vector4f vec;
	bool used = false;

public:
	UniformVec4(std::string name);
	void loadVector(Eigen::Vector4f vec);
	void loadVector(float x, float y, float z, float w);
};

#endif