#ifndef JOINTTRANSFORM_DATA_H
#define JOINTTRANSFORM_DATA_H

#include "../../Libraries/Eigen/Dense"
#include <string>

/**
 * @brief contains data for a transformation of one joint, at a certain time
 * in an animation. Has the name of the joint, and the
 * local transform of the joint in the pose position.
 * 
 */
class JointTransformData {
public:
	const std::string jointNameId;
	const Eigen::Matrix4f jointLocalTransform;

	JointTransformData(std::string&, Eigen::Matrix4f&);
};

#endif
