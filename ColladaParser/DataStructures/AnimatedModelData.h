#ifndef ANIMATEDMODEL_DATA_H
#define ANIMATEDMODEL_DATA_H

#include "MeshData.h"
#include "SkeletonData.h"
/**
 * @brief Contains the extracted data for an animated model, which includes the mesh data, and skeleton (joints heirarchy) data.
 *
 */
class AnimatedModelData {
private: 
	const SkeletonData joints;
	const MeshData mesh;

public:
	AnimatedModelData(MeshData& mesh, SkeletonData& joints);
	SkeletonData getJointsData();
	MeshData getMeshData();
};

#endif