#ifndef UNIFORM_BOOLEAN_H
#define UNIFORM_BOOLEAN_H

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

class UniformBoolean: public Uniform {
private:
	bool currentBool;
	bool used = false;

public:
	UniformBoolean(std::string name);
	void loadBoolean(bool boolean);
};

#endif