#include "MeshData.h"
#include <vector>

MeshData::MeshData(std::vector<float> vertices, std::vector<float> textureCoords, std::vector<float> normals, std::vector<int> indices,
		std::vector<int> jointIds, std::vector<float> vertexWeights) 
	: vertices(vertices)
	, textureCoords(textureCoords)
	, normals(normals)
	, indices(indices)
	, jointIds(jointIds)
	, vertexWeights(vertexWeights) {
}

std::vector<int> MeshData::getJointIds() {
	return jointIds;
}

std::vector<float> MeshData::getVertexWeights(){
	return vertexWeights;
}

std::vector<float> MeshData::getVertices() {
	return vertices;
}

std::vector<float> MeshData::getTextureCoords() {
	return textureCoords;
}

std::vector<float> MeshData::getNormals() {
	return normals;
}

std::vector<int> MeshData::getIndices() {
	return indices;
}

int MeshData::getVertexCount() {
	return (int) vertices.size() / DIMENSIONS;
}
