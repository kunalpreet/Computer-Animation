#include <vector>
#include "Animation.h"
#include "KeyFrame.h"

Animation::Animation() {
    this->length = -1;
}

/**
 * @brief Construct a new Animation:: Animation object
 * 
 * @param length in seconds
 * @param frames all keyframes in animation
 */
Animation::Animation(float length, std::vector<KeyFrame> &frames) {
    this->length = length;
    this->frames = frames;
}

float Animation::getLength() {
    return this->length;
}
std::vector<KeyFrame> Animation::getKeyFrames() {
    return this->frames;
}
