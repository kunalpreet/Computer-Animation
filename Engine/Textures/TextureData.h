#ifndef TEXTUREDATA_H
#define TEXTUREDATA_H

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

class TextureData {
private:
   int width;
   int height;
   GLubyte* dataArray;

public:
    TextureData(GLubyte* data, int width, int height);
    int getWidth();
    int getHeight();
    GLubyte* getDataArray();
};

#endif