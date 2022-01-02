#include <string>
#include "Uniform.h"
#include "UniformVec2.h"
#include "../../Libraries/Eigen/Dense"

UniformVec2::UniformVec2(std::string name) 
	: Uniform(name) {
}

void UniformVec2::loadVector(Eigen::Vector2f vec) {
	if (!used && this->vec != vec) {
		this->vec = vec;
		used = true;
		glUniform2f(this->getLocation(), vec(0), vec(1));
	}
	
}

void UniformVec2::loadVector(float x, float y) {
	Eigen::Vector2f vec2(x, y);
	loadVector(vec2);
}