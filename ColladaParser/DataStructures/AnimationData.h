#ifndef ANIMATION_DATA_H
#define ANIMATION_DATA_H

#include <vector>
#include "KeyFrameData.h"

/**
 * @brief Contains the extracted data for an animation; includes length of
 * the entire animation + the data for all the keyframes of animation.
 * 
 */
class AnimationData {
public:
	const float lengthSeconds;
	std::vector<KeyFrameData> keyFrames;

	AnimationData(float, std::vector<KeyFrameData>);
};

#endif
