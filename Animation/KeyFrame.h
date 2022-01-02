#ifndef KEYFRAMES_H
#define KEYFRAMES_H

#include <string>
#include <map>
#include "JointTransform.h"

class KeyFrame {
private:
    float timestamp;    // timestamp of this keyframe, used for interpolation between other keyframes
    std::map<std::string, JointTransform> transforms; // for each joint name, store the joint transform at this specific keyframe

public:
    KeyFrame(float, std::map<std::string, JointTransform>&);
    float getTimeStamp();
    std::map<std::string, JointTransform> getJointKeyFrames();

};

#endif