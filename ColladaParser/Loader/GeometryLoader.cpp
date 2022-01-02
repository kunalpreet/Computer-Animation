
#include "GeometryLoader.h"
#include <vector>
#include <string>
#include <algorithm> 
#include "../../Libraries/Eigen/Dense"
#include <vector>
#include "../XML/XmlNode.h"
#include "../DataStructures/JointData.h"
#include "../DataStructures/SkeletonData.h"
#include "../DataStructures/MeshData.h"
#include "../DataStructures/Vertex.h"
#include "../../Libraries/stringfn.h"
#include <cstddef>

using namespace std;

GeometryLoader::GeometryLoader(XmlNode geometryNode, std::vector<VertexSkinData> vertexWeights)
    : meshData(geometryNode.getChild("geometry").getChild("mesh"))
    , vertexWeights(vertexWeights){
}

MeshData GeometryLoader::extractModelData(){
    readRawData();
    assembleVertices();
    removeUnusedVertices();
	initArrays();
	convertDataToArrays();
	convertIndicesListToArray();
	MeshData mesh = MeshData(verticesArray, texturesArray, normalsArray, indicesArray, jointIdsArray, weightsArray);
    return mesh;

}

 void GeometryLoader::readRawData() {
	readPositions();
	readNormals();
	readTextureCoords();
}

void GeometryLoader::readPositions() {
	string positionsId = meshData.getChild("vertices").getChild("input").getAttribute("source").substr(1);
	XmlNode positionsData = meshData.getChildWithAttribute("source", "id", positionsId).getChild("float_array");
	int count = std::stoi(positionsData.getAttribute("count"));
	vector<string> posData = StringFn::splitString(positionsData.getData(), ' ');
	for (int i = 0; i < count/3; i++) {
		float x = std::stof(posData[i * 3]);
		float y = std::stof(posData[i * 3 + 1]);
		float z = std::stof(posData[i * 3 + 2]);
		Eigen::Vector4f position = Eigen::Vector4f(x, y, z, 1);
		// rotating
		Eigen::Matrix3f rotationAngle = Eigen::AngleAxisf(-1.5708, Eigen::Vector3f::UnitX()).toRotationMatrix();
		Eigen::Matrix4f CORRECTION = Eigen::Matrix4f::Identity();
		CORRECTION.block(0, 0, 3, 3) = rotationAngle;
		position = CORRECTION * position;
		vertices.push_back(Vertex((int)vertices.size(),  Eigen::Vector3f(position(0), position(1), position(2)), vertexWeights.at(vertices.size())));
	}
}

void GeometryLoader::readNormals() {
	string normalsId = meshData.getChild("polylist").getChildWithAttribute("input", "semantic", "NORMAL")
			.getAttribute("source").substr(1);
	XmlNode normalsData = meshData.getChildWithAttribute("source", "id", normalsId).getChild("float_array");
	int count = std::stoi(normalsData.getAttribute("count"));
	vector<string> normData = StringFn::splitString(normalsData.getData(), ' ');
	for (int i = 0; i < count/3; i++) {
		float x = std::stof(normData[i * 3]);
		float y = std::stof(normData[i * 3 + 1]);
		float z = std::stof(normData[i * 3 + 2]);
		Eigen::Vector4f norm = Eigen::Vector4f(x, y, z, 0.0f);
		// rotating
		Eigen::Matrix3f rotationAngle = Eigen::AngleAxisf(-1.5708, Eigen::Vector3f::UnitX()).toRotationMatrix();
		Eigen::Matrix4f CORRECTION = Eigen::Matrix4f::Identity();
		CORRECTION.block(0, 0, 3, 3) = rotationAngle;
		norm = CORRECTION * norm;
		normals.push_back(Eigen::Vector3f(norm(0), norm(1), norm(2)));
	}

}

void GeometryLoader::readTextureCoords() {
    string texCoordsId = meshData.getChild("polylist").getChildWithAttribute("input", "semantic", "TEXCOORD")
				.getAttribute("source").substr(1);
	XmlNode texCoordsData = meshData.getChildWithAttribute("source", "id", texCoordsId).getChild("float_array");
	int count = std::stoi(texCoordsData.getAttribute("count"));
	vector<string> texData = StringFn::splitString(texCoordsData.getData(), ' ');
	for (int i = 0; i < count/2; i++) {
		float s = std::stof(texData[i * 2]);
		float t = std::stof(texData[i * 2 + 1]);
		textures.push_back(Eigen::Vector2f(s, t));
	}
}

void GeometryLoader::assembleVertices(){
	XmlNode poly = meshData.getChild("polylist");
	int typeCount = poly.getChildren("input").size();
	vector<string> indexData = StringFn::splitString(poly.getChild("p").getData(), ' ');
	for(int i=0;i < (int)indexData.size()/typeCount;i++){
		int positionIndex = std::stoi(indexData[i * typeCount]);
		int normalIndex = std::stoi(indexData[i * typeCount + 1]);
		int texCoordIndex = std::stoi(indexData[i * typeCount + 2]);
		processVertex(positionIndex, normalIndex, texCoordIndex);
	}
}

void GeometryLoader::processVertex(int posIndex, int normIndex, int texIndex){
	Vertex& currentVertex = vertices.at(posIndex);
	if (!currentVertex.isSet()) {
		currentVertex.setTextureIndex(texIndex);
		currentVertex.setNormalIndex(normIndex);
		indices.push_back(posIndex);
	} else {
		dealWithAlreadyProcessedVertex(currentVertex.getIndex(), texIndex, normIndex);
	}
}

std::vector<int> GeometryLoader::convertIndicesListToArray(){
    this->indicesArray = std::vector<int>(indices.size());
	for (int i = 0; i < (int)indicesArray.size(); i++) {
		indicesArray[i] = indices.at(i);
	}
	return indicesArray;
}

float GeometryLoader::convertDataToArrays(){
	float furthestPoint = 0;
	for (int i = 0; i < (int)vertices.size(); i++) {
		Vertex currentVertex = vertices.at(i);
		if (currentVertex.getLength() > furthestPoint) {
			furthestPoint = currentVertex.getLength();
		}
		Eigen::Vector3f position = currentVertex.getPosition();
		Eigen::Vector2f textureCoord = textures.at(currentVertex.getTextureIndex());
		Eigen::Vector3f normalVector = normals.at(currentVertex.getNormalIndex());
		verticesArray[i * 3] = position(0);
		verticesArray[i * 3 + 1] = position(1);
		verticesArray[i * 3 + 2] = position(2);
		texturesArray[i * 2] = textureCoord(0);
		texturesArray[i * 2 + 1] = 1 - textureCoord(1);
		normalsArray[i * 3] = normalVector(0);
		normalsArray[i * 3 + 1] = normalVector(1);
		normalsArray[i * 3 + 2] = normalVector(2);
		VertexSkinData weights = currentVertex.getWeightsData();
		jointIdsArray[i * 3] = weights.jointIds.at(0);
		jointIdsArray[i * 3 + 1] = weights.jointIds.at(1);
		jointIdsArray[i * 3 + 2] = weights.jointIds.at(2);
		weightsArray[i * 3] = weights.weights.at(0);
		weightsArray[i * 3 + 1] = weights.weights.at(1);
		weightsArray[i * 3 + 2] = weights.weights.at(2);

	}
	return furthestPoint;
}


void GeometryLoader::dealWithAlreadyProcessedVertex(int previousVertexIndex, int newTextureIndex, int newNormalIndex) {
	Vertex &previousVertex = vertices.at(previousVertexIndex);
	if (previousVertex.hasSameTextureAndNormal(newTextureIndex, newNormalIndex)) {
		indices.push_back(previousVertex.getIndex());
	} else {
		if (previousVertex.getDuplicateVertex() != -1) {
			dealWithAlreadyProcessedVertex(previousVertex.getDuplicateVertex(), newTextureIndex, newNormalIndex);
		} else {
			Vertex duplicateVertex = Vertex(vertices.size(), previousVertex.getPosition(), previousVertex.getWeightsData());
			previousVertex.setDuplicateVertex(duplicateVertex.getIndex());	// add index of new location
			duplicateVertex.setTextureIndex(newTextureIndex);
			duplicateVertex.setNormalIndex(newNormalIndex);
			vertices.push_back(duplicateVertex);					// add new duplicate vertex
			indices.push_back(duplicateVertex.getIndex());
		}
	}
}

void GeometryLoader::initArrays(){
        this->verticesArray = std::vector<float>(vertices.size() * 3);
		this->texturesArray = std::vector<float>(vertices.size() * 2);
		this->normalsArray = std::vector<float>(vertices.size() * 3);
		this->jointIdsArray = std::vector<int>(vertices.size() * 3);
		this->weightsArray = std::vector<float>(vertices.size() * 3);
	}

void GeometryLoader::removeUnusedVertices(){
	for (Vertex vertex : vertices) {
		vertex.averageTangents();
		if (!vertex.isSet()) {
			vertex.setTextureIndex(0);
			vertex.setNormalIndex(0);
		}
	}
}