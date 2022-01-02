#include "SkinLoader.h"
#include <vector>
#include <string>
#include <algorithm> 
#include "../XML/XmlNode.h"
#include "../DataStructures/SkinningData.h"
#include "../../Libraries/stringfn.h"

using namespace std;

SkinLoader::SkinLoader(XmlNode controllersNode, int maxWeights)
    : skinningData(controllersNode.getChild("controller").getChild("skin"))
    , maxWeights(maxWeights){
}

SkinningData SkinLoader::extractSkinData(){
    vector<string> jointList = loadJointsList();
    vector<float> weights = loadWeights();
    XmlNode weightsDataNode = skinningData.getChild("vertex_weights");
    vector<int> effectorJointCounts = getEffectiveJointsCounts(weightsDataNode);
    vector<VertexSkinData> vertexWeights = getSkinData(weightsDataNode, effectorJointCounts, weights);
    return SkinningData(jointList, vertexWeights);
}

vector<string> SkinLoader::loadJointsList(){
    XmlNode inputNode = skinningData.getChild("vertex_weights");
    // removing hashtag# from start of value to get actual name of the sources
    string jointDataId = inputNode.getChildWithAttribute("input", "semantic", "JOINT").getAttribute("source").substr(1);
    // using jointDataId to find the joint-names node 
    XmlNode jointsNode = skinningData.getChildWithAttribute("source", "id", jointDataId).getChild("Name_array");
    // data; contains the names of all the joints in this model
    vector<string> names = StringFn::splitString(jointsNode.getData(), ' ');
    vector<string> jointsList;
    for (string name : names){
        jointsList.push_back(name);
    }
    return names;
}

vector<float> SkinLoader::loadWeights(){
    XmlNode inputNode = skinningData.getChild("vertex_weights");
    string weightsDataId = inputNode.getChildWithAttribute("input", "semantic", "WEIGHT").getAttribute("source")
				.substr(1);
    XmlNode weightsNode = skinningData.getChildWithAttribute("source", "id", weightsDataId).getChild("float_array");
    vector<string> rawData = StringFn::splitString(weightsNode.getData(), ' ');
	vector<float> weights(rawData.size());
    for (int i = 0; i < (int) weights.size(); i++){
        weights[i] = stof(rawData[i]);
    }
    return weights;

}

vector<int> SkinLoader::getEffectiveJointsCounts(XmlNode& weightsDataNode) {
    vector<string> rawData = StringFn::splitString(weightsDataNode.getChild("vcount").getData(), ' ');
    vector<int> counts(rawData.size());
    for (int i = 0; i < (int) rawData.size(); i++) {
        counts[i] = stoi( rawData[i] );
    }
    return counts;
}


vector<VertexSkinData> SkinLoader:: getSkinData(XmlNode& weightsDataNode, vector<int>& counts, vector<float>& weights) {
    vector<string> rawData = StringFn::splitString(weightsDataNode.getChild("v").getData(), ' ');
    vector<VertexSkinData> skinningData;
    int pointer = 0;
    for (int count : counts) {
        VertexSkinData skinData;
        for (int i = 0; i < count; i++) {
            int jointId = stoi(rawData[pointer++]);
            int weightId = stoi(rawData[pointer++]);
            skinData.addJointEffect(jointId, weights[weightId]);
        }
        skinData.limitJointNumber(maxWeights);
        skinningData.push_back(skinData);
    }
    return skinningData;
}