#ifndef ANIMATED_MODEL_H
#define ANIMATED_MODEL_H

#include <vector>
#include <string>
#include "../Animation/Animator.h"
#include "Joint.h"
#include "../Libraries/Vao.h"
#include "../Engine/Textures/Texture.h"

// Represents an entity that can be animated
class AnimatedModel {
// variables


public:
    // skeleton
    Joint rootJoint;                   // contains root joint 
    int jointCount;
    // skins
    Vao model;                      // pointer to loaded mesh
    Texture texture;
public: 
    // Animator
    Animator animator;



public:
// Takes in the model, root joint and joint count of the entity
    AnimatedModel(Vao&, Texture&, Joint&, int);

    Vao& getModel();
    Texture& getTexture();
    Joint& getRootJoint();
    
    void deleteModel();

    int getJointCount();
    
    void setAnimation(Animation&);

    void update(float);

    std::vector<Eigen::Matrix4f> getJointTransforms();
private:
    void addJointsToMap(Joint& headJoint, std::map<int, Eigen::Matrix4f>&);

};


#endif
