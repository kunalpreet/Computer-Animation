#ifndef UNIFORM_H
#define UNIFORM_H

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

class Uniform {
public:
	static const GLuint NOT_FOUND = -1;
	GLuint location;
	const std::string name;

public:
	Uniform(std::string name);
	virtual ~Uniform();
	virtual void storeUniformLocation(GLuint programID);
	virtual GLuint getLocation();

};

#endif