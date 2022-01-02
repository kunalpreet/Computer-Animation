#include <string>
#include "Uniform.h"
#include "UniformVec3.h"
#include "../../Libraries/Eigen/Dense"

UniformVec3::UniformVec3(std::string name) 
	: Uniform(name) {
}

void UniformVec3::loadVector(Eigen::Vector3f vec) {
	if (!used && this->vec != vec) {
		this->vec = vec;
		used = true;
		glUniform3f(this->getLocation(), vec(0), vec(1), vec(2));
	}
	
}

void UniformVec3::loadVector(float x, float y, float z) {
	Eigen::Vector3f vec3(x, y, z);
	loadVector(vec3);
}