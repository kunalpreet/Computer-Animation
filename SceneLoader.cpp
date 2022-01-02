
#include "SceneLoader.h"

#include "Animation/Animation.h"

#include "Loaders/AnimatedModelLoader.h"
#include "Loaders/AnimationLoader.h"
#include <fstream>
#include <iostream>


using namespace std;

Scene SceneLoader::loadScene(ifstream& myModel, ifstream& myTexture, ifstream& myAnim) {
    AnimatedModel entity = AnimatedModelLoader::loadEntity(myModel, myTexture);
    cout << "Animated Model loaded from file" << endl;
    cout << "Entity loaded with " << entity.getJointCount() << " joints" << endl << endl;

    Animation anim = AnimationLoader::loadAnimation(myAnim);
    cout << "Animation loaded from file" << endl << endl;

    entity.setAnimation(anim);
    cout << "Entity assigned with " << entity.getJointCount() << " joints" << endl;
    cout << "Entity assigned animation with " << anim.getKeyFrames().size() << " keyframes of length " << anim.getLength() << endl << endl;

    return Scene(entity);
}