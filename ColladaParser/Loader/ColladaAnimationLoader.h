#ifndef DAE_ANIM_LOADER_H
#define DAE_ANIM_LOADER_H

#include <string>
#include <vector>
#include "../XML/XmlParser.h"

#include "../DataStructures/JointTransformData.h"
#include "../DataStructures/AnimationData.h"
#include "../DataStructures/KeyFrameData.h"


class ColladaAnimationLoader {
private:	
	XmlNode animationData;
	XmlNode jointHierarchy;


public:
	ColladaAnimationLoader(XmlNode animationData, XmlNode jointHierarchy);
	AnimationData extractAnimation();

private:
	std::vector<float> getKeyTimes();
	
	std::vector<KeyFrameData> initKeyFrames(std::vector<float> times);
	
	void loadJointTransforms(std::vector<KeyFrameData>& frames, XmlNode jointData, std::string rootNodeId);
	
	std::string getDataId(XmlNode jointData);
	
	std::string getJointName(XmlNode jointData);
	
	void processTransforms(std::string jointName, std::vector<std::string> rawData, std::vector<KeyFrameData>& keyFrames, bool root);
	
	std::string findRootJointName();
};


#endif