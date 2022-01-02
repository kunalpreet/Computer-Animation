#ifndef VERTEX_H
#define VERTEX_H

#include <vector>
#include "VertexSkinData.h"
#include "../../Libraries/Eigen/Dense"

class Vertex {
private:
	static const int NO_INDEX = -1;
	
	Eigen::Vector3f position;
	int textureIndex = NO_INDEX;
	int normalIndex = NO_INDEX;
	int duplicateVertexIndex = NO_INDEX; // passing initial null value
	int index;
	float length;
	std::vector<Eigen::Vector3f> tangents;
	Eigen::Vector3f averagedTangent;
	
	
	VertexSkinData weightsData;

public:
	Vertex(int index, Eigen::Vector3f position, VertexSkinData weightsData);
	VertexSkinData getWeightsData();

	void addTangent(Eigen::Vector3f& tangent);
	void averageTangents();
	Eigen::Vector3f getAverageTangent();

	int getIndex();
	float getLength();

	bool isSet();
	bool hasSameTextureAndNormal(int textureIndexOther,int normalIndexOther);

	void setTextureIndex(int textureIndex);
	void setNormalIndex(int normalIndex);

	Eigen::Vector3f getPosition();
	int getTextureIndex();
	int getNormalIndex();
	int getDuplicateVertex();
	void setDuplicateVertex(int duplicateVertexIndex);

};
#endif