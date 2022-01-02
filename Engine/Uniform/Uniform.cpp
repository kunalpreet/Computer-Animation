#include "Uniform.h"
#include <string>
#include <iostream>

Uniform::Uniform(std::string name)
	: name(name) {
}

Uniform::~Uniform() {

}

// Finds the location of a uniform using the given name
void Uniform::storeUniformLocation(GLuint programID){
	location = glGetUniformLocation(programID, name.c_str());
	if (location == NOT_FOUND){
		std::cout << "No uniform variable called " << name << " found" << std::endl;
	}
}

GLuint Uniform::getLocation(){
	return location;
}