#include "UniformBoolean.h"
#include "Uniform.h"
#include <string>

UniformBoolean::UniformBoolean(std::string name) 
	: Uniform(name){
}

void UniformBoolean::loadBoolean(bool b){
	if(!used || currentBool != b){
		glUniform1f(this->getLocation(), b ? 1.0f : 0.0f); // saving true=1, false=0 into location
		currentBool = b;									// updating value
		used = true;										// this lcoation has been used
	}
}