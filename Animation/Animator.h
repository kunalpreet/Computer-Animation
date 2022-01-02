#ifndef ANIMATOR_H
#define ANIMATOR_H

#include "Animation.h"
#include "../AnimatedModel/Joint.h"
#include <map>
#include <vector>
#include "../Libraries/Eigen/Dense"

// Takes in an Animation, and a time, and interpolates between keyframes the necessary joint transforms
class AnimatedModel;
class Animator {
public:
    // Joint& entityRoot; // the root joint of the entity that this animator is controlling

    Animation currentAnimation; // current animation being rendered
    float animationTime = 0;    // animation time

public:
    // Animator(Joint&);
    Animator();

    void setAnimation(Animation&);

    void update(float elapsedTime, Joint& rootJoint);

    void increaseAnimationTime(float elapsedTime);

private:
    std::map<std::string, Eigen::Matrix4f> calculateCurrentAnimationPose();
	void applyPoseToJoints(std::map<std::string, Eigen::Matrix4f>&, Joint&, Eigen::Matrix4f&);
	std::vector<KeyFrame> getPreviousAndNextFrames();
	float calculateProgression(KeyFrame&, KeyFrame&);
	std::map<std::string, Eigen::Matrix4f>  interpolatePoses(KeyFrame&, KeyFrame&, float);

};

#endif