#ifndef JOINT_DATA_H
#define JOINT_DATA_H

#include <vector>
#include <string>
#include "../../Libraries/Eigen/Dense"

/**
 * @brief Contains the extracted data for a single joint in the model. This stores the
 * joint's index, name, and local bind transform.
 */
class JointData {
public:
	const int index;
	const std::string nameId;
	const Eigen::Matrix4f bindLocalTransform;

	std::vector<JointData> children;

	JointData(int, std::string&, Eigen::Matrix4f&);

	void addChild(JointData&);

};


#endif