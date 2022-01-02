#include "Animator.h"
#include "Animation.h"

#include "../Libraries/Eigen/Dense"
#include <map>
#include <vector>

// 
/**
 * @brief Constructs a new Animator:: Animator object 
 */
Animator::Animator() {

}

void Animator::setAnimation(Animation& animation) {
    this->animationTime = 0;
    this->currentAnimation = animation;
}


/**
 * @brief Updates the rootJoint of an entity with the elapsed time interpolating between actions
 * 
 * @param elapsedTime 
 * @param entityRoot 
 */
void Animator::update(float elapsedTime, Joint& entityRoot) {
    // Default Constructor is invalid, and sets length to -1. We check if this animator exists
    // Alternatively, we check if there are any keyframes at all
    if (currentAnimation.getLength() < 0 || currentAnimation.getKeyFrames().size() == 0) {
        return;
    }
    increaseAnimationTime(elapsedTime);
    std::map<std::string, Eigen::Matrix4f> currentPose = calculateCurrentAnimationPose();
    Eigen::Matrix4f mat = Eigen::Matrix4f::Identity(); // identity matrix for the root node
    applyPoseToJoints(currentPose, entityRoot, mat);    // recursively change the joint structure of the given entity
}


/**
 * @brief Increases animation time; if current animation time is longer the entire animation, restart
 * 
 */
void Animator::increaseAnimationTime(float elapsedTime) {
    animationTime += elapsedTime;     
    while (animationTime > currentAnimation.getLength()) {
        animationTime -= currentAnimation.getLength();
    }
}

/**
 * @brief Calculates the current animation pose by interpolating the poses with the curren ttime
 * 
 * @return std::map<std::string, Eigen::Matrix4f> Contains the name and the associate transform of each joint based on current pose
 */
std::map<std::string, Eigen::Matrix4f> Animator::calculateCurrentAnimationPose() {
    std::vector<KeyFrame> frames = getPreviousAndNextFrames();
    assert(frames.size() == 2);
    float progression = calculateProgression(frames.front(), frames.back());
    return interpolatePoses(frames.front(), frames.back(), progression);

}

/**
 * @brief Applies the map of joint transforms to each joint
 * 
 * @param currentPose map with details of each joint's transform
 * @param joint The joint to be transformed
 * @param parentTransform The parent's tranform - used for converting from local space to world space
 */
void Animator::applyPoseToJoints(std::map<std::string, Eigen::Matrix4f>& currentPose, Joint& joint, Eigen::Matrix4f& parentTransform) {
    Eigen::Matrix4f currentLocalTransform = currentPose.at(joint.name); // gets the transform from map based on joint's name
    
    
    // turning it into world space based on parent's world space
    Eigen::Matrix4f currentTransform = parentTransform * currentLocalTransform;
    
    // recursively apply this function to all child joints of this joint; remember to pass by reference!
    for (Joint &childJoint : joint.children) {
        applyPoseToJoints(currentPose, childJoint, currentTransform);
    }

    // subtracting joint's original bind from desired pose transform
    // results in the needed transform to move from joint's original model-space to desired model-space
    // this matrix is loaded to vertex shader, and transforms vertices to original pose
    currentTransform = currentTransform * joint.getInverseBindTransform();

    // setting the new animation transform 
    joint.setAnimationTransform(currentTransform);
}



/**
 * @brief Returns a vector of size 2, containing the two KeyFrames that our animation is currently between
 * 
 * @return std::vector<KeyFrame> Two keyframes containing the frames we need to interpolate between
 */
std::vector<KeyFrame> Animator::getPreviousAndNextFrames() {
    std::vector<KeyFrame> allFrames = currentAnimation.getKeyFrames();
    KeyFrame previousFrame = allFrames[0];
    KeyFrame nextFrame = allFrames[0];
    for (int i = 1; i < (int) allFrames.size(); i++) {
        nextFrame = allFrames[i];
        // we are right before the next KeyFrame; we have already selected the two keyframes needed
        if (nextFrame.getTimeStamp() > animationTime) {
            break;
        } 
        // haven't reached timestamp yet; keep moving up
        previousFrame = allFrames[i];
    }
    // vector to contain the two frames that the current animation is interpolating between
    std::vector<KeyFrame> twoFrames;
    twoFrames.push_back(previousFrame);     // previousFrame at position 0
    twoFrames.push_back(nextFrame);         // nextFrame at position 1
    return twoFrames;
}

/**
 * @brief Calculates the progression [0,1] between two keyframes, and the current animation time
 * 
 * @param previousFrame 
 * @param nextFrame 
 * @return float Progression of value [0,1]
 */
float Animator::calculateProgression(KeyFrame& previousFrame, KeyFrame& nextFrame) {
    float totalTime = nextFrame.getTimeStamp() - previousFrame.getTimeStamp();
    float currentTime = animationTime - previousFrame.getTimeStamp();
    return currentTime/totalTime; // used for progression
}

/**
 * @brief 
 * 
 * @param previousFrame 
 * @param nextFrame 
 * @return std::map<std::string, Eigen::Matrix4f> 
 */
std::map<std::string, Eigen::Matrix4f> Animator::interpolatePoses(KeyFrame& previousFrame, KeyFrame& nextFrame, float progression) {
    std::map<std::string, Eigen::Matrix4f> currentPose;

    // for each joint
    for (auto joint : previousFrame.getJointKeyFrames()) {
        std::string jointName = joint.first;

        // we store the JointTransform of this joint for the previous, and next frames
        // joint.second is the JointTransform associated with the current iterator
        JointTransform previousTransform = joint.second;

        // accessing nextFrame's map, but using the same name for same joint
        JointTransform nextTransform = nextFrame.getJointKeyFrames().at(jointName);

        // interpolating between the two transforms
        JointTransform currentTransform = JointTransform::interpolate(previousTransform, nextTransform, progression);

        // adding calculated transform to map; convert from JointTransform to Matrix4f
        // we place jointName and the conversion of currentTransform to Matrix into a pair class, which we use to insert into currentPose
        currentPose.insert(std::pair<std::string, Eigen::Matrix4f>(jointName, currentTransform.getLocalTransform()));
    }
    return currentPose;
}
