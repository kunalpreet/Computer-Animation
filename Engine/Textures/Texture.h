#ifndef TEXTURE_H
#define TEXTURE_H

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

#include "TextureSettings.h"
#include "TextureData.h"
#include "TextureUtils.h"
#include <fstream>

class Texture {
public:
   GLuint textureId[1];   // texture is binded to this ID; to access, textureId[0]
   TextureData data;
   TextureSettings settings;
   int size;
   int type;
   // check if data already binded
   bool isSetup = false;

   Texture(std::ifstream& file);
   Texture(std::ifstream& file, int type);
   void bindToUnit(int unit);
   void unbind();
   void deleteTex();

   void setup();

};

#endif