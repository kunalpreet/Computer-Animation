#ifndef SKELETON_DATA_H
#define SKELETON_DATA_H


#include "JointData.h"

class SkeletonData {
public:
	const int jointCount;
	const JointData headJoint;
	
	SkeletonData(int jointCount, JointData& headJoint);

};

#endif