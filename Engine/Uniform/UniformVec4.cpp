#include <string>
#include "Uniform.h"
#include "UniformVec4.h"
#include "../../Libraries/Eigen/Dense"

UniformVec4::UniformVec4(std::string name) 
	: Uniform(name) {
}

void UniformVec4::loadVector(Eigen::Vector4f vec) {
	if (!used && this->vec != vec) {
		this->vec = vec;
		used = true;
		glUniform4f(this->getLocation(), vec(0), vec(1), vec(2), vec(3));
	}
	
}

void UniformVec4::loadVector(float x, float y, float z, float w) {
	Eigen::Vector4f vec4(x, y, z, w);
	loadVector(vec4);
}