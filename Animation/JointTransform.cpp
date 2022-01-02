
#include "../Libraries/Eigen/Dense" // matrices, vector
#include "JointTransform.h"

// constructor
JointTransform::JointTransform(Eigen::Vector3f position, Eigen::Quaternionf rotation) {
    this->position = position;
    this->rotation = rotation;
}

// creates a matrix of its current transform with it's position and rotation
Eigen::Matrix4f JointTransform::getLocalTransform() {
    // translating the identity matrix to new position
    // https://stackoverflow.com/questions/20323487/how-translation-a-matrix4x4-in-eigen
    Eigen::Affine3f translate = Eigen::Affine3f(Eigen::Translation3f(position));  // creating translation 
    Eigen::Matrix4f mat = translate.matrix();

    // Converting Quaternion rotation to 3x3 rot matrix, then making it 4x4
    Eigen::Matrix3f rotMatrix = rotation.toRotationMatrix();
    Eigen::Matrix4f rot = Eigen::Matrix4f::Identity();          // creating 4x4 identity, then overwrites values in rot from rotMatrix
    rot.block(0, 0, 3, 3) = rotMatrix;                          // selects 3x3 block from rot4x4 at position 0, 0, and sets the values in that block equal to rotMatrix   

    // rot is our 4x4 rotation matrix
    mat *= rot;     // applying rotation to our translation matrix
    return mat;
}


// a static function that interpolates between two JointTransforms based on a value. progression is a number from [0,1] that indicates how far the interpolation is at
JointTransform JointTransform::interpolate(JointTransform frameA, JointTransform frameB, float progression) {
    Eigen::Vector3f pos = interpolate(frameA.position, frameB.position, progression);
    Eigen::Quaternionf rot = frameA.rotation.slerp(progression, frameB.rotation);
    return JointTransform(pos, rot);
}


// interpolates between two vecotrs based on a value. progression is a number from [0,1] that indicates how far the interpolation is at
Eigen::Vector3f JointTransform::interpolate(Eigen::Vector3f start, Eigen::Vector3f end, float progression) {
    // 0 = x, 1, = y, 2 = z
    float x = start(0) + (end(0) - start(0)) * progression;
    float y = start(1) + (end(1) - start(1)) * progression;
    float z = start(2) + (end(2) - start(2)) * progression;
    return Eigen::Vector3f(x, y, z);
}
