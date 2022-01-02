#include "TextureData.h"
#include <string>
#include <iostream>
#include <sstream>

TextureData::TextureData(GLubyte* data, int width, int height)
	: width(width), height(height), dataArray(data)  {
}

int TextureData::getHeight(){
   return height;
}

int TextureData::getWidth(){
   return width;
}


GLubyte* TextureData::getDataArray() {
   return dataArray;
}