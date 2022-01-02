#include "UniformFloat.h"
#include "Uniform.h"
#include <string>

UniformFloat::UniformFloat(std::string name) 
	: Uniform(name){
}

void UniformFloat::loadFloat(float value){
	if(!used || currentValue != value){
		glUniform1f(this->getLocation(), value); // saving float to this location
		currentValue = value;						// updating value
		used = true;							// this location has been used
	}
}