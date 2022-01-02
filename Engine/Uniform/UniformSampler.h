#ifndef UNIFORM_SAMPLER_H
#define UNIFORM_SAMPLER_H

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

class UniformSampler: public Uniform {
private:
	int currentValue;
	bool used = false;

public:
	UniformSampler(std::string name);
	void loadTexUnit(int texUnit);
};

#endif