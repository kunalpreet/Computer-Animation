#ifdef __APPLE__
#  include <OpenGL/gl3.h>
#  include <OpenGL/glu.h>
#  include <GLUT/glut.h>
#else
#  include <GL/glew.h>
#  include <GL/gl.h>
#  include <GL/glu.h>
#  include <GL/freeglut.h>
#endif

#include "ShaderProgram.h"
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <memory>       // unique_ptr
#include "../Uniform/Uniform.h"
#include "../Uniform/UniformMat4Array.h"

// Constructs a vertex and fragment shader, along with the names of the uniform variables
ShaderProgram::ShaderProgram(std::ifstream& vertexFile, std::ifstream& fragmentFile, std::vector<std::string> inVariables) {
    // Create shaders from a given file
    std::cout << "Loading Vertex Shader" << std::endl;
    int vertexShaderID = loadShader(vertexFile, GL_VERTEX_SHADER);
    std::cout << "Loaded Vertex; Loading Fragment Shader" << std::endl;
    int fragmentShaderID = loadShader(fragmentFile, GL_FRAGMENT_SHADER);

    // Generate program, and attach shaders
    std::cout << "Loaded Fragment; Attaching Shaders" << std::endl;
    programID = glCreateProgram();
    glAttachShader(programID, vertexShaderID);
    glAttachShader(programID, fragmentShaderID);
    // binding attributes, then linking to program
    std::cout << "Binding Shaders" << std::endl;
    bindAttributes(inVariables);
    glLinkProgram(programID);
    std::cout << "Shaders Linked!" << std::endl;

    // detaching and deleting shaders after program is linked
    glDetachShader(programID, vertexShaderID);
    glDetachShader(programID, fragmentShaderID);
    glDeleteShader(vertexShaderID);
    glDeleteShader(fragmentShaderID);
}

void ShaderProgram::storeAllUniformLocations(std::vector<Uniform*> uniforms){
    for (int i = 0; i < (int) uniforms.size(); i++) {
        uniforms[i]->storeUniformLocation(programID);
    }
    glValidateProgram(programID);
}

void ShaderProgram::start() {
    glUseProgram(programID);
}

void ShaderProgram::stop() {
    glUseProgram(0);
}

void ShaderProgram::cleanUp() {
    stop();
    glDeleteProgram(programID);
}

void ShaderProgram::bindAttributes(std::vector<std::string> inVariables){
    for(int i = 0; i < (int) inVariables.size();i++){
        std::cout << "Binding << " << inVariables[i].c_str() << " to " << i << std::endl;
        glBindAttribLocation(programID, i, inVariables[i].c_str());
    }
}

int ShaderProgram::loadShader(std::ifstream& file, int type) {
    // reading from file into shaderSource
    std::string content = "";
    std::string line = "";
    if (file.fail()){
        std::cout << "Failed to read from file" << std::endl;
        exit(0);
    }

    while (!file.eof()) {
        std::getline(file, line);
        content.append(line + "\n");
    }

    const char *shaderSource = content.c_str();
    int shaderID = glCreateShader(type);
    glShaderSource(shaderID, 1, &shaderSource, NULL);
    glCompileShader(shaderID);

    int success;
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(shaderID, 512, NULL, infoLog);
        std::cout << "\n\nError: Shader Loading Failed:\n" << infoLog << std::endl;
    }
    return shaderID;
}