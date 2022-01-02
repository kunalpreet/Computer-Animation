#include "VertexSkinData.h"

#include <list>
#include <string>
#include <algorithm> 

void VertexSkinData::addJointEffect(int joinId, float weight) {
    for(int i = 0; i < (int) weights.size(); i++){
        if(weight > weights.at(i)){
            jointIds.insert(jointIds.begin() + i, joinId);
            weights.insert(weights.begin() + i, weight);
            return;
        }
    }
    jointIds.push_back(joinId);
    weights.push_back(weight);
}

// changing the weights vector to fit the limit
void VertexSkinData::limitJointNumber(int max){
    if((int) jointIds.size() > max){
        std::vector<float> topWeights;
        float total = saveTopWeights(topWeights, max);
        refillWeightList(topWeights, total);
        removeExcessJointIds(max);
    }
    else if ((int) jointIds.size() < max){
        fillEmptyWeights(max);
    }

    // else if size == max, then no need to do anything
}

void VertexSkinData::fillEmptyWeights(int max){
    while(jointIds.size() < (size_t) max){
        jointIds.push_back(0);
        weights.push_back(0.0f);
    }
}

/**
 * @brief populates the vector with the size of the parameter given from the weights vector
 * 
 * @param topWeightsArray 
 * @param size 
 * @return float Returns the total weight value inside of the returned vector
 */
float VertexSkinData::saveTopWeights(std::vector<float>& topWeightsArray, int size){
    float total = 0;
    for(int i = 0; i < size; i++){
        // topWeightsArray[i] = weights.at(i); // don't think we can do this before element already exists
        topWeightsArray.push_back(weights.at(i)); // adding in order of i
        total = total + weights.at(i);
    }
    return total;
}


/**
 * @brief Overwrites the weights vector with the given parameter vector
 * 
 * @param topWeights The values to use to overwrite the previous weight vector
 * @param total The sum of the values in the topWeights vector
 */
void VertexSkinData::refillWeightList(std::vector<float>& topWeights, float total){
    weights.clear();
    for(int i = 0; i < (int) topWeights.size(); i++){
        int min;
        if (topWeights[i]/total < 1){
            min = topWeights[i]/total;
        } else {
            min = 1;
        }
        weights.push_back(min);
    }
}

void VertexSkinData::removeExcessJointIds(int max){
    while((int) jointIds.size() >  max){
        jointIds.erase(jointIds.begin() + (jointIds.size()-1));
    }
}

