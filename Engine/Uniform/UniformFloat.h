#ifndef UNIFORM_FLOAT_H
#define UNIFORM_FLOAT_H

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

class UniformFloat: public Uniform {
private:
	float currentValue;
	bool used = false;

public:
	UniformFloat(std::string name);
	void loadFloat(float value);
};

#endif