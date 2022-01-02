#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H
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
#include <memory>
#include <string>
#include <fstream>
#include "../Uniform/Uniform.h"

class ShaderProgram {
private:
	GLuint programID;

public:
	ShaderProgram(std::ifstream& vertexFile, std::ifstream& fragmentFile, std::vector<std::string> inVariables);

protected:
	void storeAllUniformLocations(std::vector<Uniform*> uniforms);

public:
	void start();
	void stop();
	void cleanUp();

private:
	void bindAttributes(std::vector<std::string> inVariables);
	int loadShader(std::ifstream& file, int type);
};

#endif