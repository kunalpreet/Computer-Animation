#ifndef ANIMATION_H
#define ANIMATION_H

#include <vector>
#include "KeyFrame.h"

// A short loop of keyframes, that contain the transforms for each joint, and the time for each
// I.e. A Running animation that is 3s long and loops
class Animation {
private:
    std::vector<KeyFrame> frames; // list of keyframes in this animation
    float length;       // length of this animation; in seconds

public:
    Animation();
    Animation(float, std::vector<KeyFrame>&);

    float getLength();
    std::vector<KeyFrame> getKeyFrames();

};

#endif