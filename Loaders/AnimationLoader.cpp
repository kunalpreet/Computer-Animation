#include "AnimationLoader.h"

#include <fstream> //ifstream
#include <vector>
#include <map>
#include <string>

#include "../Animation/Animation.h"
#include "../Animation/JointTransform.h"
#include "../Animation/KeyFrame.h"

#include "../ColladaParser/Loader/ColladaLoader.h"

#include "../ColladaParser/DataStructures/AnimationData.h"
#include "../ColladaParser/DataStructures/KeyFrameData.h"
#include "../ColladaParser/DataStructures/JointTransformData.h"
#include "../Libraries/Eigen/Dense"

/**
 * Loads up a collada animation file, and returns and animation created from
 * the extracted animation data from the file.
 * 
 * @param colladaFile
 *            - the collada file containing data about the desired
 *            animation.
 * @return The animation made from the data in the file.
 */
Animation AnimationLoader::loadAnimation(std::ifstream& colladaFile) {
	AnimationData animationData = ColladaLoader::loadColladaAnimation(colladaFile);
	int numKf = (int) animationData.keyFrames.size();
	std::vector<KeyFrame> frames;

	for (int i = 0; i < numKf; i++) {
		frames.push_back(createKeyFrame(animationData.keyFrames[i]));
	}
	return Animation(animationData.lengthSeconds, frames);
}
/**
 * Creates a keyframe from the data extracted from the collada file.
 * @param data
 *            - the data about the keyframe that was extracted from the
 *            collada file.
 * @return The keyframe.
 */
KeyFrame AnimationLoader::createKeyFrame(KeyFrameData data) {
	std::map<std::string, JointTransform> map;
	for (JointTransformData jointData : data.jointTransforms) {
		JointTransform jointTransform = createTransform(jointData);

		std::pair<std::string, JointTransform> pair(jointData.jointNameId, jointTransform);
		map.insert(pair);
	}
	return KeyFrame(data.time, map);
}

/**
 * Creates a joint transform from the data extracted from the collada file.
 * 
 * @param data
 *            - the data from the collada file.
 * @return The joint transform.
 */
JointTransform AnimationLoader::createTransform(JointTransformData data) {
	Eigen::Matrix4f mat = data.jointLocalTransform;
	Eigen::Vector3f translation = Eigen::Vector3f(mat(3, 0), mat(3, 1), mat(3, 2));

    Eigen::Matrix3f rotMat = mat.block(0, 0, 3, 3);       
	// selects 3x3 block from 4x4 at position 0, 0, and sets the values in that block equal to rotMatrix  

	Eigen::Quaternionf rotation = Eigen::Quaternionf(rotMat);
	return JointTransform(translation, rotation);
}

