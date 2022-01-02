#ifndef SKINNING_DATA_H
#define SKINNING_DATA_H

#include "VertexSkinData.h"
#include <vector>
#include <string>

class SkinningData {
public:
    std::vector<std::string> jointOrder;
    std::vector<VertexSkinData> verticesSkinData;

    SkinningData(std::vector<std::string> jointOrder, std::vector<VertexSkinData> verticesSkinData);
};

#endif