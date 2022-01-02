#ifndef SCENE_H
#define SCENE_H

#include "AnimatedModel/AnimatedModel.h"
#include "Engine/Shaders/EntityShader.h"
#include <fstream>
class Scene {
    bool animate = true;
    bool showTexture = false;
public:
    AnimatedModel entity;
    EntityShader shader;


    Scene(AnimatedModel entity);

    // prepares shaders - loads new values
    void prepare();
    // stops shaders
    void finish();

    void update(float);
    void render();

    void toggleAnimate();


    void setShowTexture(bool b);
    void toggleShowTexture();
};


#endif