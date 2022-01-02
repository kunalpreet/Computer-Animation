#include <string>
#include <map>
#include "JointTransform.h"
#include "KeyFrame.h"

KeyFrame::KeyFrame(float timestamp, std::map<std::string, JointTransform> &transforms) {
    this->timestamp = timestamp;
    this->transforms = transforms;

}

float KeyFrame::getTimeStamp() {
    return this->timestamp;
}

std::map<std::string, JointTransform> KeyFrame::getJointKeyFrames() {
    return this->transforms;
}