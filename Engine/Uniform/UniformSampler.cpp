#include "UniformSampler.h"
#include "Uniform.h"
#include <string>

UniformSampler::UniformSampler(std::string name) 
	: Uniform(name){
}

void UniformSampler::loadTexUnit(int texUnit){
	if(!used || currentValue != texUnit){
		glUniform1f(this->getLocation(), texUnit); // saving float to this location
		currentValue = texUnit;						// updating value
		used = true;							// this location has been used
	}
}