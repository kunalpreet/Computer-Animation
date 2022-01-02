#ifndef VERTEXTSKIN_DATA_H
#define VERTEXTSKIN_DATA_H

#include <vector>
#include <string>
#include <algorithm> 

class VertexSkinData {

public:
    std::vector<int> jointIds; 
    std::vector<float> weights; 


    void addJointEffect(int joinId, float weight);
    void limitJointNumber(int max);
private:
    void fillEmptyWeights(int max);
    float saveTopWeights(std::vector<float>& topWeightsArray, int size);
    void refillWeightList(std::vector<float>& topWeights, float total);
    void removeExcessJointIds(int max);
};

#endif