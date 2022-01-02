#include "JointData.h"
#include <vector>
#include <string>
#include "../../Libraries/Eigen/Dense"


JointData::JointData(int index, std::string &nameId, Eigen::Matrix4f& bindLocalTransform) 
	: index(index)
	, nameId(nameId)
	, bindLocalTransform(bindLocalTransform) {

}

void JointData::addChild(JointData& child) {
	children.push_back(child);
}