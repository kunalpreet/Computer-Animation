#include "UniformMat4Array.h"
#include "UniformMatrix.h"
#include "Uniform.h"
#include <string>
#include "../../Libraries/Eigen/Dense"

UniformMat4Array::UniformMat4Array(std::string name, int size) 
	: Uniform(name){
        // populate array
    for (int i = 0; i < size; i++) {
        uniformMatrices.push_back(UniformMatrix(name + "[" + std::to_string(i) + "]"));
    }
}

void UniformMat4Array::storeUniformLocation(GLuint programID) {
    for (auto it = uniformMatrices.begin(); it != uniformMatrices.end(); ++it) {
        it->storeUniformLocation(programID);
    }
}

void UniformMat4Array::loadMatrixArray(std::vector<Eigen::Matrix4f> matrices) {
    assert (uniformMatrices.size() >= matrices.size());
    int i = 0;
    for (auto it = uniformMatrices.begin(); it != uniformMatrices.end() && i < (int) matrices.size(); ++it) {
        it->loadMatrix(matrices[i]);
        i++;
    }
}