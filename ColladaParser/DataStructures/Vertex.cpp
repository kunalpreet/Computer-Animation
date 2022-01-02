#include <vector>
#include "Vertex.h"
#include "VertexSkinData.h"
#include "../../Libraries/Eigen/Dense"

Vertex::Vertex(int index, Eigen::Vector3f position, VertexSkinData weightsData){
    this->index = index;
    this->weightsData = weightsData;
    this->position = position;
    this->length = position.norm(); // length of the 3d vector
}

VertexSkinData Vertex::getWeightsData(){
    return weightsData;
}

void Vertex::addTangent(Eigen::Vector3f& tangent){
    tangents.push_back(tangent);
}

void Vertex::averageTangents(){
    if(tangents.empty()){
        return;
    }
    for(Eigen::Vector3f tangent : tangents){
        averagedTangent = averagedTangent + tangent;
    }
    averagedTangent.normalize();
}

Eigen::Vector3f Vertex::getAverageTangent(){
    return averagedTangent;
}

int Vertex::getIndex(){
    return index;
}

float Vertex::getLength(){
    return length;
}

bool Vertex::isSet(){
    return textureIndex!=NO_INDEX && normalIndex!=NO_INDEX;
}

bool Vertex::hasSameTextureAndNormal(int textureIndexOther,int normalIndexOther){
    return textureIndexOther==textureIndex && normalIndexOther==normalIndex;
}

void Vertex::setTextureIndex(int textureIndex){
    this->textureIndex = textureIndex;
}

void Vertex::setNormalIndex(int normalIndex){
    this->normalIndex = normalIndex;
}

Eigen::Vector3f Vertex::getPosition() {
    return position;
}

int Vertex::getTextureIndex() {
    return textureIndex;
}

int Vertex::getNormalIndex() {
    return normalIndex;
}

// returns the index that contains a duplicate of this vertex
int Vertex::getDuplicateVertex() {
    return duplicateVertexIndex;
}

void Vertex::setDuplicateVertex(int duplicateVertexIndex) {
    this->duplicateVertexIndex = duplicateVertexIndex;
}