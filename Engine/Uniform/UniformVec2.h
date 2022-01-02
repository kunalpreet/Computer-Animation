#ifndef UNIFORM_VEC2_H
#define UNIFORM_VEC2_H

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

class UniformVec2: public Uniform {
private:
	Eigen::Vector2f vec;
	bool used = false;

public:
	UniformVec2(std::string name);
	void loadVector(Eigen::Vector2f vec);
	void loadVector(float x, float y);
};

#endif