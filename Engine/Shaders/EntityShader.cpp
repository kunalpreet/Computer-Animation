#include "EntityShader.h"
#include "ShaderProgram.h"

#include <fstream>
#include <iostream>
#include <string>
#include <memory> //unique_ptr

#include "../Uniform/UniformMat4Array.h"
#include "../Uniform/UniformMatrix.h"
#include "../Uniform/UniformSampler.h"
#include "../Uniform/UniformVec3.h"

/**
 * Creates the shader program with the given vertex/fragment files and the list of uniform variables
 * It then stores the list of uniform variables in a vector of pointers, which will then call them to be stored
 * in the respective function in the parent function
 */
EntityShader::EntityShader(std::ifstream& vertex_shader, std::ifstream& fragment_shader, std::vector<std::string> inVariables) :
    ShaderProgram(vertex_shader, fragment_shader, inVariables)
        {
    // inVariables = "in_position", "in_textureCoords", "in_normal", "in_jointIndices",	"in_weights"
    //passing child class uniformtypes to a vector of type parent class
    std::cout << "ShaderProgram initialized, adding uniforms" << std::endl;
    std::vector<Uniform*> uniforms;
    uniforms.emplace_back(&projectionMatrix);
    uniforms.emplace_back(&modelViewMatrix);
    uniforms.emplace_back(&diffuseMap);
    uniforms.emplace_back(&lightDirection);
    uniforms.emplace_back(&jointTransforms);
    this->storeAllUniformLocations(uniforms);
    connectTextureUnits();
    std::cout << "Entity Shader constructed" << std::endl;
}

void EntityShader::start() {
    ShaderProgram::start();
}
void EntityShader::stop() {
    ShaderProgram::stop();
}
void EntityShader::cleanUp() {
    ShaderProgram::cleanUp();
}

/**
 * Indicates which texture unit the diffuse texture should be sampled from.
 */
void EntityShader::connectTextureUnits() {
    this->start();
    diffuseMap.loadTexUnit(DIFFUSE_TEX_UNIT);
    this->stop();
}

EntityShader EntityShader::ConstructEnityShader(std::ifstream vertex, std::ifstream fragment) {
    std::vector<std::string> inVariables = {"in_position", "in_textureCoords", "in_normal", "in_jointIndices", "in_weights"};
    return EntityShader(vertex, fragment, inVariables); 
}