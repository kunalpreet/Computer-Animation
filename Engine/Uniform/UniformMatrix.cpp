#include "UniformMatrix.h"
#include "Uniform.h"
#include <string>
#include "../../Libraries/Eigen/Dense"

UniformMatrix::UniformMatrix(std::string name) 
	: Uniform(name){
}

void UniformMatrix::loadMatrix(Eigen::Matrix4f matrix) {
	// loading from matrix to array
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			data[i*4 + j] = matrix(j, i);
		}
	}
	glUniformMatrix4fv(this->getLocation(), 1, false, data); // saving float to this location
}


void UniformMatrix::loadMatrix(float loadData[16]) {
	for (int i = 0; i < 16; i++) {
		this->data[i] = loadData[i];
	}
	glUniformMatrix4fv(this->getLocation(), 1, false, data); // saving float to this location
}