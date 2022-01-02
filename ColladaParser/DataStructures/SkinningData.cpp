#include "SkinningData.h"
#include "VertexSkinData.h"
#include <vector>
#include <string>

SkinningData::SkinningData(std::vector<std::string> jointOrder, std::vector<VertexSkinData> verticesSkinData){
    this->jointOrder = jointOrder;
    this->verticesSkinData = verticesSkinData;
}