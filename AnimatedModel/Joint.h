#ifndef JOINT_H
#define JOINT_H

#include <vector>
#include <string>
#include "../Libraries/Eigen/Dense" // Matrices

// The individual joint of a skeleton in animation
class Joint {
public:
// parameters
    int id;                       // joint ID
    std::string name;             // joint name
    std::vector<Joint> children;    // contains child joints 
public:
    // transformation matrices here 
    Eigen::Matrix4f animatedTransform = Eigen::Matrix4f::Identity();              // changed world space w/ animation
    const Eigen::Matrix4f localBindTransform;       // local world space
    const Eigen::Matrix4f inverseBindTransform;     // inverse of world space


public:
    Joint(int, std::string, Eigen::Matrix4f, Eigen::Matrix4f);
    void addChild(Joint child);

	Eigen::Matrix4f getAnimatedTransform();
	void setAnimationTransform(Eigen::Matrix4f animationTransform);

	Eigen::Matrix4f getInverseBindTransform();
    

    Eigen::Matrix4f calcBindTransform(Eigen::Matrix4f parentBindTransform);
    Eigen::Matrix4f calcInverseBindTransform(Eigen::Matrix4f parentBindTransform);


};


#endif
