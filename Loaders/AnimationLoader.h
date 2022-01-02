#ifndef ANIMATION_LOADER_H 
#define ANIMATION_LOADER_H 

#include <fstream> //ifstream
#include "../Animation/Animation.h"
#include "../Animation/JointTransform.h"
#include "../Animation/KeyFrame.h"

#include "../ColladaParser/DataStructures/AnimationData.h"
#include "../ColladaParser/DataStructures/KeyFrameData.h"
#include "../ColladaParser/DataStructures/JointTransformData.h"

class AnimationLoader {
public:
	/**
	 * Loads up a collada animation file, and returns and animation created from
	 * the extracted animation data from the file.
	 * @param colladaFile
	 *            - the collada file containing data about the desired
	 *            animation.
	 * @return The animation made from the data in the file.
	 */
	static Animation loadAnimation(std::ifstream& colladaFile);

private:
	/**
	 * Creates a keyframe from the data extracted from the collada file.
	 * @param data
	 *            - the data about the keyframe that was extracted from the
	 *            collada file.
	 * @return The keyframe.
	 */
	static KeyFrame createKeyFrame(KeyFrameData data);

	/**
	 * Creates a joint transform from the data extracted from the collada file.
	 * @param data
	 *            - the data from the collada file.
	 * @return The joint transform.
	 */
	static JointTransform createTransform(JointTransformData data);

};

#endif