#include "ColladaLoader.h"
#include <iostream>
#include <fstream> // file reading

// loaders
#include "SkinLoader.h"
#include "SkeletonLoader.h"
#include "ColladaAnimationLoader.h"
#include "GeometryLoader.h"
// data structures
#include "../XML/XmlParser.h"
#include "../DataStructures/AnimatedModelData.h"
#include "../DataStructures/AnimationData.h"
#include "../DataStructures/MeshData.h"
#include "../DataStructures/SkeletonData.h"
#include "../DataStructures/SkinningData.h"

AnimatedModelData ColladaLoader::loadColladaModel(std::ifstream& file, int maxWeights) {
	std::cout << "Loading Model" << std::endl;
	XmlNode node = XmlParser::loadFromFile(file);
    // XmlParser::printNode(node);
	std::cout << "Loaded XML nodes from file" << std::endl;

	
	std::cout << "Getting Skin Data" << std::endl;
	SkinLoader skinLoader = SkinLoader(node.getChild("library_controllers"), maxWeights);
	SkinningData skinningData = skinLoader.extractSkinData();
	std::cout << "Skin Data received" << std::endl;

	std::cout << "Getting Joints Data" << std::endl;
	SkeletonLoader jointsLoader = SkeletonLoader(node.getChild("library_visual_scenes"), skinningData.jointOrder);
	SkeletonData jointsData = jointsLoader.extractBoneData();
	std::cout << "Joints Data received" << std::endl;

	std::cout << "Getting Geometry Data" << std::endl;
	GeometryLoader g = GeometryLoader(node.getChild("library_geometries"), skinningData.verticesSkinData);
	std::cout << "Geometry loaded; extracting model data" << std::endl;
	MeshData meshData = g.extractModelData();
	std::cout << "Geometry Data received\nModel Data loaded" << std::endl;

	return AnimatedModelData(meshData, jointsData);
}

AnimationData ColladaLoader::loadColladaAnimation(std::ifstream& file) {
	std::cout << "Loading Animations" << std::endl;
	XmlNode node = XmlParser::loadFromFile(file);
    // XmlParser::printNode(node);
	std::cout << "Loaded XML nodes from file" << std::endl;

	std::cout << "Getting Animation Data" << std::endl;
	XmlNode animNode = node.getChild("library_animations");
	std::cout << "Getting Joints Data" << std::endl;
	XmlNode jointsNode = node.getChild("library_visual_scenes");
	std::cout << "Loading from animation and joints data..." << std::endl;
	ColladaAnimationLoader loader = ColladaAnimationLoader(animNode, jointsNode);
	std::cout << "Loaded data, extracting animations" << std::endl;
	AnimationData animData = loader.extractAnimation();
	std::cout << "Loaded animations from data!" << std::endl;
	return animData;
}