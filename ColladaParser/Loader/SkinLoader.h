#ifndef SKIN_LOADER_H
#define SKIN_LOADER_H

#include <vector>
#include <string>
#include <algorithm> 
#include <iostream>
#include "../XML/XmlNode.h"
#include "../DataStructures/SkinningData.h"

using namespace std;

class SkinLoader {

private:
    XmlNode skinningData;
    int maxWeights;

    vector<string> loadJointsList();
    vector<float> loadWeights();
    vector<int> getEffectiveJointsCounts(XmlNode& weightsDataNode);
    vector<VertexSkinData> getSkinData(XmlNode& weightsDataNode, vector<int>& counts, vector<float>& weights);

public:
    SkinLoader(XmlNode controllersNode, int maxWeights);
    SkinningData extractSkinData();


};

#endif