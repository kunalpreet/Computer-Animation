#ifndef ENTITY_SHADER_H
#define ENTITY_SHADER_H

#include "ShaderProgram.h"

#include <fstream>
#include <string>
#include <memory> //unique_ptr

#include "../Uniform/UniformMat4Array.h"
#include "../Uniform/UniformMatrix.h"
#include "../Uniform/UniformSampler.h"
#include "../Uniform/UniformVec3.h"

class EntityShader : ShaderProgram {
private:
	static const int MAX_JOINTS = 50;// max number of joints in a skeleton
	static const int DIFFUSE_TEX_UNIT = 0;

public:
// uniform variables
	// UniformMatrix projectionViewMatrix = UniformMatrix("projectionViewMatrix");
	UniformMatrix projectionMatrix = UniformMatrix("projectionMatrix");
	UniformMatrix modelViewMatrix = UniformMatrix("modelViewMatrix");
	UniformVec3 lightDirection = UniformVec3("lightDirection");
	UniformMat4Array jointTransforms = UniformMat4Array("jointTransforms", MAX_JOINTS);
	UniformSampler diffuseMap = UniformSampler("diffuseMap");

public:
	/**
	 * Creates the shader program for the {@link AnimatedModelRenderer} by
	 * loading up the vertex and fragment shader code files. It also gets the
	 * location of all the specified uniform variables, and also indicates that
	 * the diffuse texture will be sampled from texture unit 0.
	 */
	EntityShader(std::ifstream& vertex_shader, std::ifstream& fragment_shader, std::vector<std::string> inVariables);
	static EntityShader ConstructEnityShader(std::ifstream vertex, std::ifstream fragment);

// accessors to the base class
	void start();
	void stop();
	void cleanUp();
private:
	/**
	 * Indicates which texture unit the diffuse texture should be sampled from.
	 */
	void connectTextureUnits();
};

#endif
