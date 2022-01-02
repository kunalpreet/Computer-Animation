#include "AnimationData.h"
#include <vector>
#include "KeyFrameData.h"


AnimationData::AnimationData(float lengthSeconds, std::vector<KeyFrameData> keyFrames)
	: lengthSeconds(lengthSeconds), keyFrames(keyFrames) {
}