
#include "ColladaAnimationLoader.h"
#include <string>
#include <vector>

#include "../XML/XmlParser.h"

#include "../DataStructures/JointTransformData.h"
#include "../DataStructures/AnimationData.h"
#include "../DataStructures/KeyFrameData.h"
#include "../../Libraries/stringfn.h"
#include "../../Libraries/Eigen/Dense"

using namespace std;

ColladaAnimationLoader::ColladaAnimationLoader(XmlNode animationData, XmlNode jointHierarchy) :
	animationData(animationData), jointHierarchy(jointHierarchy) {
}

AnimationData ColladaAnimationLoader::extractAnimation(){
	string rootNode = findRootJointName();
	vector<float> times = getKeyTimes();
	float duration = times[times.size()-1];

	vector<KeyFrameData> keyFrames = initKeyFrames(times);
	vector<XmlNode> animationNodes = animationData.getChildren("animation");

	for(XmlNode jointNode : animationNodes){
		loadJointTransforms(keyFrames, jointNode, rootNode);
	}
	return AnimationData(duration, keyFrames);
}

vector<float> ColladaAnimationLoader::getKeyTimes(){
	XmlNode timeData = animationData.getChild("animation").getChild("source").getChild("float_array");
	vector<string> rawTimes = StringFn::splitString(timeData.getData(), ' ');
	vector<float> times;
	for(int i = 0; i < (int)rawTimes.size(); i++){
		times.push_back(stof(rawTimes[i]));
	}
	return times;
}

vector<KeyFrameData> ColladaAnimationLoader::initKeyFrames(vector<float> times){
	vector<KeyFrameData> frames;
	for(int i = 0; i < (int) times.size(); i++){
		frames.push_back(KeyFrameData(times[i]));
	}
	return frames;
}

void ColladaAnimationLoader::loadJointTransforms(vector<KeyFrameData>& frames, XmlNode jointData, string rootNodeId){
	string jointNameId = getJointName(jointData);
	string dataId = getDataId(jointData);
	
	XmlNode transformData = jointData.getChildWithAttribute("source", "id", dataId);
	vector<string> rawData =  StringFn::splitString(transformData.getChild("float_array").getData(), ' ');
	
	processTransforms(jointNameId, rawData, frames, (jointNameId == rootNodeId));
}

string ColladaAnimationLoader::getDataId(XmlNode jointData){
	XmlNode node = jointData.getChild("sampler").getChildWithAttribute("input", "semantic", "OUTPUT");
	return node.getAttribute("source").substr(1);
}

string ColladaAnimationLoader::getJointName(XmlNode jointData){
	XmlNode channelNode = jointData.getChild("channel");
	string data = channelNode.getAttribute("target");
	vector<string> splitData =  StringFn::splitString(data, '/');
	return splitData.front();
}

void ColladaAnimationLoader::processTransforms(string jointName, vector<string> rawData, vector<KeyFrameData>& keyFrames, bool root){
    // assert(rawData.size() == 16);
    // length should be 16, 4x4
	Eigen::Matrix4f mat;
	for(int kf = 0; kf < (int) keyFrames.size(); kf++){
		// populating matrix
    	// we populate from left to right, top to down, row by row
		for(int i = 0; i < 4; i++){
			for (int j = 0; j < 4; j++) {
				// each kf has 16 values for matrix
				mat(i, j) = stof(rawData[kf*16 + i*4 + j]);
			}
		}
		// TODO: Check if this is necessary
		// mat = mat.transpose();
		// mat.transpose();
		if(root){
			//because up axis in Blender is different to up axis in game
			Eigen::Matrix3f rotationAngle = Eigen::AngleAxisf(-1.5708, Eigen::Vector3f::UnitX()).toRotationMatrix();
			Eigen::Matrix4f CORRECTION = Eigen::Matrix4f::Identity();
			CORRECTION.block(0, 0, 3, 3) = rotationAngle;
			mat = CORRECTION * mat;
		}
		KeyFrameData& kfdata = keyFrames[kf];
		kfdata.addJointTransform(JointTransformData(jointName, mat));
	}
}

string ColladaAnimationLoader::findRootJointName(){
	XmlNode skeleton = jointHierarchy.getChild("visual_scene").getChildWithAttribute("node", "id", "Armature");
	return skeleton.getChild("node").getAttribute("id");
}

