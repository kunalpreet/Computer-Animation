#include "TextureSettings.h"

TextureSettings::TextureSettings() {
}

void TextureSettings::setClampEdges(){
   clampEdges = true;
}

void TextureSettings::setNormalMipMap(){
   mipmap = false;
   anTropic = false;
}

void TextureSettings::setNearestFiltering(){
   mipmap = false;
   anTropic = false;
   nearest = true;
}

void TextureSettings::setAnisotropic(){
   mipmap = true;
   anTropic = true;
}

bool TextureSettings::isClampEdges(){
   return clampEdges;
}

bool TextureSettings::isMipmap(){
   return mipmap;
}

bool TextureSettings::isAnisotropic(){
   return anTropic;
}

bool TextureSettings::isNearest(){
   return nearest;
}