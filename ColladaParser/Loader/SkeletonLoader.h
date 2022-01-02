#ifndef SKELETON_LOADER_H
#define SKELETON_LOADER_H

#include "../../Libraries/Eigen/Dense"
#include <vector>
#include "../XML/XmlNode.h"
#include "../DataStructures/JointData.h"
#include "../DataStructures/SkeletonData.h"

using namespace std;

// Loads the skeleton data from a collada (.dae) file - the collada loader passes the node with the name "library_visual_scenes"
class SkeletonLoader {
private:
	XmlNode armatureData;
	vector<string> boneOrder;
	int jointCount = 0;

public:
// Constructor that takes in the Library_Visual_Scene node, and a list of bones to synchronize joint list entry
// Note: This is where you may need to change things if the library names don't really work i.e. different library names
	SkeletonLoader(XmlNode visualSceneNode, vector<string>& boneOrder);
	
    // Prompts this class to go through the given XmlNode and construct a SkeletonData object containing details parsed from the XmlNode
	SkeletonData extractBoneData();
private:
    // Prompts loading of joint data from a joint XmlNode; called recursively on all of its child nodes
	JointData loadJointData(XmlNode& jointNode, bool isRoot);
	
    // Prompts the extraction of matrix data to JointData
	JointData extractMainJointData(XmlNode& jointNode, bool isRoot);
	
    // Converting from the vector of strings read into a matrix
	Eigen::Matrix4f convertData(vector<string> rawData);
};


#endif