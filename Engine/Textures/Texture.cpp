#include "Texture.h"
#include <fstream>
#include <iostream>
Texture::Texture(std::ifstream& file)
	: data(TextureUtils::decodeTextureFile(file))
   , settings(TextureSettings()) {

      
   std::cout << "\tTexture Data Read!" <<std::endl;
   settings.setAnisotropic();
   size = this->data.getWidth();
   type = GL_TEXTURE_2D;
   std::cout << "\t\tsize = " << size << std::endl;
   std::cout << "\tBinding Texture Data" <<std::endl;
   this->setup();
   std::cout << "\tTexture created and binded!" <<std::endl;
}

Texture::Texture(std::ifstream& file, int type)
	: data(TextureUtils::decodeTextureFile(file))
   , settings(TextureSettings())
   , size(this->data.getWidth())
   , type(type) {
}


// Bind texture to show this Texture class
void Texture::bindToUnit(int unit){
   glActiveTexture(GL_TEXTURE0 + unit);
   glBindTexture(type, textureId[0]);
}

void Texture::unbind() {
   glBindTexture(type, textureId[-1]);
}

void Texture::deleteTex(){
   // deleting textures
   glDeleteTextures(1 , textureId);
}



void Texture::setup() {
   if (isSetup)
      return;

   // load into given variable the parsed data + this texture builder's settings
   std::cout << textureId << std::endl;
   TextureUtils::loadTextureToOpenGL(textureId, data, settings);
   std::cout << "Binded: " << textureId << " - " << textureId[0] << " w/ size " << data.getWidth()  << std::endl;

   isSetup = true;
}