#include "AnimatedModelData.h"
#include "MeshData.h"
#include "SkeletonData.h"

AnimatedModelData::AnimatedModelData(MeshData& mesh, SkeletonData& joints)
	: joints(joints)
	, mesh(mesh) {
}

SkeletonData AnimatedModelData::getJointsData(){
	return joints;
}

MeshData AnimatedModelData::getMeshData(){
	return mesh;
}

