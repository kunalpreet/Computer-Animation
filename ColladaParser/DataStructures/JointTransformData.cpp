#include "JointTransformData.h"
#include "../../Libraries/Eigen/Dense"
#include <string>

JointTransformData::JointTransformData(std::string& jointNameId, Eigen::Matrix4f& jointLocalTransform) 
	: jointNameId(jointNameId)
	, jointLocalTransform(jointLocalTransform) {
}