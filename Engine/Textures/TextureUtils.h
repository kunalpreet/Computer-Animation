#ifndef TEXTUREUTILS_H
#define TEXTUREUTILS_H

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

// contains a list of static functiosn that help in the encoding of a .png file into a Texture file to be used
#include "TextureSettings.h"
#include "TextureData.h"
#include <fstream>

class TextureUtils {

public:
   // given a fstream file, read and return a TextureData class containing that png image
	static TextureData decodeTextureFile(std::ifstream& file);

   // Given a TextureData and Texture settings, load that texture into the given GLuint* array 
	static void loadTextureToOpenGL(GLuint* textures, TextureData& data, TextureSettings& settings);

};

#endif
