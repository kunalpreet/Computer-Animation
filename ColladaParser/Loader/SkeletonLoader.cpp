#include "SkeletonLoader.h"

#include "../../Libraries/Eigen/Dense"
#include "../../Libraries/stringfn.h"
#include <vector>
#include "../XML/XmlNode.h"
#include "../DataStructures/JointData.h"
#include "../DataStructures/SkeletonData.h"
#include <iostream>

using namespace std;

SkeletonLoader::SkeletonLoader(XmlNode visualSceneNode, vector<string>& boneOrder)
    : armatureData(visualSceneNode.getChild("visual_scene").getChildWithAttribute("node", "id", "Armature"))
    , boneOrder(boneOrder) {
    if (armatureData.getName() == "")
    {
        std::cout << "Error finding node - exiting in SkeletonLoader constructor" << std::endl;
        exit(0);
    }
}

SkeletonData SkeletonLoader::extractBoneData() {
    XmlNode headNode = armatureData.getChild("node");
    JointData headJoint = loadJointData(headNode, true);
    return SkeletonData(jointCount, headJoint);
}

JointData SkeletonLoader::loadJointData(XmlNode& jointNode, bool isRoot){
    JointData joint = extractMainJointData(jointNode, isRoot);

    // for each XmlNode labelled "node" (contains transform data bout the joint)
    for(XmlNode childNode : jointNode.getChildren("node")){
        JointData child = loadJointData(childNode, false);
        joint.addChild(child);
    }
    return joint;
}
#include <iostream>
JointData SkeletonLoader::extractMainJointData(XmlNode& jointNode, bool isRoot){
    string nameId = jointNode.getAttribute("sid");

    // get the index of this joint from the boneOrder we got from constructor
    int index;
    auto findIterator = find(boneOrder.begin(), boneOrder.end(), nameId);
    if (findIterator != boneOrder.end()) {
        index = findIterator - boneOrder.begin();
    } else {
        cout << "Index = -1 when extracting main joint data; looking for " << nameId << endl;
        index = -1;
    }

    // getting the string of data for the joint
    string data = jointNode.getChild("matrix").getData();
    vector<string> matrixData = StringFn::splitString(data, ' ');
    Eigen::Matrix4f matrix = convertData(matrixData);
    
    if(isRoot) {
        //because in Blender z is up, but in our game y is up.
		Eigen::Matrix3f rotationAngle = Eigen::AngleAxisf(-1.5708, Eigen::Vector3f::UnitX()).toRotationMatrix();
		Eigen::Matrix4f CORRECTION = Eigen::Matrix4f::Identity();
		CORRECTION.block(0, 0, 3, 3) = rotationAngle;
        matrix = matrix * CORRECTION;
    }
    jointCount++;
    return JointData(index, nameId, matrix);
}

// Converting from the vector of strings read into a matrix
Eigen::Matrix4f SkeletonLoader::convertData(vector<string> rawData){
    assert(rawData.size() == 16);
    // length should be 16, 4x4
    // we populate from left to right, top to down, row by row
    Eigen::Matrix4f mat;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            float num = stof(rawData[(i * 4 + j)]);
            mat(i,j) = num;
        }
    }
    return mat;
}