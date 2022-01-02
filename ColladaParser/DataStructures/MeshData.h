#ifndef MESH_DATA_H
#define MESH_DATA_H

#include <vector>

/**
 * @brief contains all the mesh data for an animated model that is to be loaded into the VAO.
 *
 */
class MeshData {
private:
	static const int DIMENSIONS = 3;

	std::vector<float> vertices;
	std::vector<float> textureCoords;
	std::vector<float> normals;
	std::vector<int> indices;
	std::vector<int> jointIds;
	std::vector<float> vertexWeights;

public:
	MeshData(std::vector<float> vertices, std::vector<float> textureCoords, std::vector<float> normals, std::vector<int> indices,
			std::vector<int> jointIds, std::vector<float> vertexWeights);

	std::vector<int> getJointIds();
	
	std::vector<float> getVertexWeights();
	std::vector<float> getVertices();
	std::vector<float> getTextureCoords();
	std::vector<float> getNormals();
	std::vector<int> getIndices();

	int getVertexCount();
};

#endif