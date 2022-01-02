

#include "AnimatedModel.h"
#include <vector>
#include <string>
#include "Joint.h"
#include "../Libraries/VAO.h"
#include "../Libraries/Eigen/Dense"
#include "../Engine/Textures/Texture.h"
AnimatedModel::AnimatedModel(Vao& vao_model, Texture& newTexture, Joint& root, int jCount) 
    : rootJoint(root)
    , jointCount(jCount)
    , model(vao_model) 
    , texture(newTexture)
    , animator(Animator()) {
}

Vao& AnimatedModel::getModel() {
    return this->model;
}

Texture& AnimatedModel::getTexture() {
    return this->texture;
}

Joint& AnimatedModel::getRootJoint() {
    return this->rootJoint;
}

// Deletes the OpenGL objects of VAO and (possibly) textures from this model
void AnimatedModel::deleteModel() {
    model.deleteVertexArrays();
    texture.deleteTex();
}

int AnimatedModel::getJointCount() {
    return jointCount;
}

/**
 * @brief prompts this entity to carry out this specific animation
 * @param animation The animation this entity should do next    
 */
void AnimatedModel::setAnimation(Animation& animation) {
    this->animator.setAnimation(animation);
}

// when this model updates, the animator should update as well
void AnimatedModel::update(float elapsedTime) {
    this->animator.update(elapsedTime, this->getRootJoint());
}




/**
 * @brief Gets a vector of all the joint's model-space transforms in this entity
 * 
 * @return std::vector<Eigen::Matrix4f> Vector of all Joint transforms in this entity
 */
std::vector<Eigen::Matrix4f> AnimatedModel::getJointTransforms() {
    std::map<int, Eigen::Matrix4f> jointMatrices;
    addJointsToMap(this->rootJoint, jointMatrices);
    //returns jointMatrices;
    // pair = <int, matrix>
    // want to add from map to vector in order of int in key

    std::vector<Eigen::Matrix4f> vecMatrices;
    for (auto it : jointMatrices) {
        // adds in the order of the key
        vecMatrices.push_back(it.second);
    }
    return vecMatrices;
}


/**
 * @brief Adds current model-space transforms for all joints in an entity to the given vector
 * 
 * @param headJoint current joint being added to the array
 * @param jointMatrices where we are storing the transforms into
 */
void AnimatedModel::addJointsToMap(Joint& headJoint, std::map<int, Eigen::Matrix4f>& jointMatrices) {
    std::pair<int, Eigen::Matrix4f> pair(headJoint.id, headJoint.getAnimatedTransform());
    jointMatrices.insert(pair);
    for (Joint childJoint : headJoint.children) {
        addJointsToMap(childJoint, jointMatrices);
    }
}