#include "Joint.h"

#include <list>
#include <string>
#include "../Libraries/Eigen/Dense" // Matrices

/**
 * @brief Construct a new Joint object
 * 
 * @param index the id of this joint
 * @param name the name of the joint; it is what the joint is named in the .dae file, 
 * and is used to identify the respective joint transforms for a joint
 * @param localBindTransform the local 'bone-space' transform of the joint in this bind position
 */
Joint::Joint(int index, std::string name, Eigen::Matrix4f localBindTransform, Eigen::Matrix4f parentBindTransform) :
    id(index), name(name), localBindTransform(localBindTransform), inverseBindTransform(calcInverseBindTransform(parentBindTransform)) {
}

/**
 * @brief Adds a child joint to this joint. Used during the creation of the joint
 * hierarchy. Joints can have multiple children, which is why they are
 * stored in a list 
 * 
 * @param child The joint to be added - passed by reference
 */
void Joint::addChild(Joint child) {
    this->children.push_back(child);
}

/**
 * @brief Getter function for the animated transform. This is the transform that gets loaded up to the shader
 * and is used to deform the vertices of the "skin". It represents the
 * transformation from the joint's bind position (original position in
 * model-space) to the joint's desired animation pose (also in model-space).
 * 
 * @return The transformation matrix of the joint which is used to deform
 *         associated vertices of the skin in the shaders.
 */
Eigen::Matrix4f Joint::getAnimatedTransform() {
    return this->animatedTransform;
}

/**
 * @brief Setter function for animated transform. Allows the joint's position to be moved by the animator
 * 
 * @param animationTransform the new joint transform
 */
void Joint::setAnimationTransform(Eigen::Matrix4f animationTransform) {
    this->animatedTransform = animationTransform;
}


/**
 * @brief Returns the inverted model-space bind transform. The bind transform is the original model-space of the joint
 * This returns the inverse of that bind, which is used to calculate the animated tranformation matrix;
 * 
 * @return Returns the inverse matrix of the model's bind transform
 */
Eigen::Matrix4f Joint::getInverseBindTransform() {
    return this->inverseBindTransform;
}



// gets the world space of this joint by multiplying the local with the parent's world space
Eigen::Matrix4f Joint::calcBindTransform(Eigen::Matrix4f parentBindTransform) {
    return parentBindTransform * this->localBindTransform;
}


/**
 * This is called during set-up, after the joints hierarchy has been
 * created. It first finds the bind transform of this joint by multiplying the 
 * parent's bind transform with its own local bind transform.
 * It then calculates and stores the inverse of this model-space bind
 * transform, which is used later for calculating the final transformation. 
 * It then recursively calls the method for all of the children
 * joints, so that they too calculate and store their inverse bind-pose
 * transform.
 * 
 * @param parentBindTransform the bind transform of the parent joint. This is the model-space transform.
 */
Eigen::Matrix4f Joint::calcInverseBindTransform(Eigen::Matrix4f parentBindTransform) {
    Eigen::Matrix4f bindTransform = calcBindTransform(parentBindTransform);
    return bindTransform.inverse();
}