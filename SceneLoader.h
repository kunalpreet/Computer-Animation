#ifndef SCENE_LOADER_H
#define SCENE_LOADER_H


#include <fstream>
#include "Scene.h"
class SceneLoader {
public:
    static Scene loadScene(std::ifstream& myModel, std::ifstream& myTexture, std::ifstream& myAnim);
};

#endif