
#include "SkeletonData.h"
#include "JointData.h"

// initlizer list for constructor
SkeletonData::SkeletonData(int jointCount, JointData& headJoint) 
	: jointCount(jointCount)
	, headJoint(headJoint) {

}