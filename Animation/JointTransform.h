
#ifndef JOINTTRANSFORM_H
#define JOINTTRANSFORM_H

#include "../Libraries/Eigen/Dense" // matrices, vector

// represents a joint's position and rotation relative to their parent joint
class JointTransform {
private:
    Eigen::Vector3f position;
    Eigen::Quaternionf rotation;

public:
    // constructor
    JointTransform(Eigen::Vector3f, Eigen::Quaternionf);

    // creates a matrix of its current transform with it's position and rotation
    Eigen::Matrix4f getLocalTransform();

    // interpolates between two JointTransforms based on a value
    static JointTransform interpolate(JointTransform, JointTransform, float);


private:
    // interpolates between two vecotrs based on a value
    static Eigen::Vector3f interpolate(Eigen::Vector3f, Eigen::Vector3f, float);

};

#endif