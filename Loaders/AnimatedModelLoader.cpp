
#include "AnimatedModelLoader.h"

#include <fstream>
#include "../AnimatedModel/AnimatedModel.h"
#include "../AnimatedModel/Joint.h"
#include "../ColladaParser/Loader/ColladaLoader.h"

#include "../ColladaParser/DataStructures/AnimatedModelData.h"
#include "../ColladaParser/DataStructures/JointData.h"
#include "../ColladaParser/DataStructures/MeshData.h"
#include "../ColladaParser/DataStructures/SkeletonData.h"
#include "../Engine/Textures/Texture.h"
#include "../Engine/Textures/TextureSettings.h"

#include "../Libraries/Vao.h"
#include <iostream>

// import main.GeneralSettings;
// import textures.Texture;

/**
 * Creates an AnimatedEntity from the data in an entity file. It loads up
 * the collada model data, stores the extracted data in a VAO, sets up the
 * joint heirarchy, and loads up the entity's texture.
 * 
 * @param entityFile
 *            - the file containing the data for the entity.
 * @return The animated entity (no animation applied though)
 */
AnimatedModel AnimatedModelLoader::loadEntity(std::ifstream& modelFile, std::ifstream& textureFile) {
	std::cout << "Loading Animated Model" << std::endl;
	AnimatedModelData entityData = ColladaLoader::loadColladaModel(modelFile, 160);

	std::cout << "Loading VAO" << std::endl;
	Vao model = Vao();
	loadVAO(model, entityData.getMeshData());

	std::cout << "Loading Textures" << std::endl;
	Texture texture = Texture(textureFile);
	std::cout << "\tCreated Texture; checking " <<std::endl;
    std::cout << "\tLoaded: " << texture.textureId << " - " << texture.textureId[0] << std::endl;
    std::cout << "\tw/ sizes: " << texture.size << ", " << texture.type << ", texture @ " << &texture << std::endl;

	std::cout << "Loading Skeleton" << std::endl;
	SkeletonData skeletonData = entityData.getJointsData();
	std::cout << "Loading Joints" << std::endl;
	Joint headJoint = createJoints(skeletonData.headJoint);

	std::cout << "Data loaded into classes - returning" << std::endl;
	return AnimatedModel(model, texture, headJoint, skeletonData.jointCount);
}

/**
 * Constructs the joint-hierarchy skeleton from the data extracted from the
 * collada file. Returns the root.
 * 
 * @param data
 *            - the joints data from the collada file for the head joint.
 * @return The created joint, with all its descendants added.
 */
Joint AnimatedModelLoader::createJoints(JointData data) {
	Joint root = Joint(data.index, data.nameId, data.bindLocalTransform, Eigen::Matrix4f::Identity());
	for (JointData child : data.children) {
		root.addChild(createJoints(child, root.calcBindTransform(Eigen::Matrix4f::Identity())));
	}
	return root;
}

// child node version; passing parentBindTransform onwards to the next child to continuously find the inverseBindTransform from origin to the joint
Joint AnimatedModelLoader::createJoints(JointData data, Eigen::Matrix4f parentBindTransform) {
	Joint joint = Joint(data.index, data.nameId, data.bindLocalTransform, parentBindTransform);
	for (JointData child : data.children) {
		joint.addChild(createJoints(child, joint.calcBindTransform(parentBindTransform)));
	}
	return joint;
}

/**
 * Stores the mesh data in a VAO.
 * Note: If encountering a segmentation error here - this means that create() didn't work
 * Remember to enable glew! https://stackoverflow.com/questions/8302625/segmentation-fault-at-glgenvertexarrays-1-vao
 * @param vao
 *            - the vao to store the object into
 * @param data
 *            - all the data about the mesh that needs to be stored in the
 *            VAO.
 * @return The VAO containing all the mesh data for the model.
 */

void AnimatedModelLoader::loadVAO(Vao& vao, MeshData data) {
	vao.bind();
	vao.createIndexBuffer(data.getIndices());
	vao.createAttribute(0, data.getVertices(), 3);	// 3 points per vertex
	vao.createAttribute(1, data.getTextureCoords(), 2);	// 2 points per texture
	vao.createAttribute(2, data.getNormals(), 3);
	vao.createIntAttribute(3, data.getJointIds(), 3);
	vao.createAttribute(4, data.getVertexWeights(), 3);
	vao.unbind();
}