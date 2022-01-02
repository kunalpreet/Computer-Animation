#ifndef GEOMETRY_LOADER_H
#define GEOMETRY_LOADER_H

#include <vector>
#include <string>
#include <algorithm> 
#include "../XML/XmlNode.h"
#include "../DataStructures/Vertex.h"
#include "../DataStructures/VertexSkindata.h"
#include "../DataStructures/MeshData.h"


class GeometryLoader {


private:
    XmlNode meshData;
    std::vector<VertexSkinData> vertexWeights;
    std::vector<float> verticesArray;
    std::vector<float> normalsArray;
    std::vector<float> texturesArray;
    std::vector<int> indicesArray;
    std::vector<int> jointIdsArray;
    std::vector<float> weightsArray;


public:

    std::vector<Vertex> vertices;
    std::vector<Eigen::Vector2f> textures;
    std::vector<Eigen::Vector3f> normals;
    std::vector<int> indices;

    GeometryLoader(XmlNode geometryNode, std::vector<VertexSkinData> vertexWeights);
    MeshData extractModelData();

private:
    void readRawData();
    void readPositions();
    void readNormals();
    void readTextureCoords();
    void assembleVertices();
    void processVertex(int posIndex, int normIndex, int texIndex);
    std::vector<int> convertIndicesListToArray();
    float convertDataToArrays();
    void dealWithAlreadyProcessedVertex(int previousVertexIndex, int newTextureIndex, int newNormalIndex) ;
    void initArrays();
    void removeUnusedVertices();



};

#endif