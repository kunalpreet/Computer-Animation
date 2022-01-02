#ifndef COLLADA_LOADER_H
#define COLLADA_LOADER_H

#include <fstream> // file reading
#include "../DataStructures/AnimatedModelData.h"
#include "../DataStructures/AnimationData.h"

class ColladaLoader {
public:
	static AnimatedModelData loadColladaModel(std::ifstream& file, int maxWeights);
	static AnimationData loadColladaAnimation(std::ifstream& file);
};

#endif