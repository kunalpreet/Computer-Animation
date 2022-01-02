#ifndef TEXTURESETTINGS_H
#define TEXTURESETTINGS_H

class TextureSettings {
private:
   bool clampEdges = false;
   bool mipmap = false;
   bool anTropic = true;
   bool nearest = false;

public:
   TextureSettings();
   
   // sets properties for this texture builder
   void setClampEdges();
   void setNormalMipMap();
   void setNearestFiltering();
   void setAnisotropic();

// checking settings inside this TextureSettings
   bool isClampEdges();
   bool isMipmap();
   bool isAnisotropic();
   bool isNearest();
};

#endif