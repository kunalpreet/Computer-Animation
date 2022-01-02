
#include "KeyFrameData.h"	
#include <vector>
#include "JointTransformData.h"
KeyFrameData::KeyFrameData(float time) : time(time) {

}

void KeyFrameData::addJointTransform(JointTransformData transform){
	jointTransforms.push_back(transform);
}