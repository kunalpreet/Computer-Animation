#ifndef KEYFRAME_DATA_H
#define KEYFRAME_DATA_H

#include <vector>
#include "JointTransformData.h"

class KeyFrameData {
public:
	const float time;
	std::vector<JointTransformData> jointTransforms;
	
	KeyFrameData(float time);
	void addJointTransform(JointTransformData transform);
};

#endif