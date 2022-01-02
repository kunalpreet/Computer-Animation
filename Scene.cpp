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

#include "Scene.h"
#include "AnimatedModel/AnimatedModel.h"
#include <iostream>
#include <fstream>

using namespace std;

Scene::Scene(AnimatedModel entity)
    : entity(entity)
    , shader(EntityShader::ConstructEnityShader(
                ifstream("Engine/Shaders/EntityVertex.glsl"), 
                ifstream("Engine/Shaders/EntityFragment.glsl"))
            ) 
    {
    // constructs a shader with the given files


    animate = false;
    setShowTexture(false);
}



void Scene::update(float elapsedTime) {
    // cout << "Updating model: " << endl;
    entity.update(elapsedTime);
}

// prepares the shader by starting it, loading values
void Scene::prepare() {
    shader.start();

    
	GLfloat proj[16];
	glGetFloatv(GL_PROJECTION_MATRIX, proj);
	GLfloat mv[16];
	glGetFloatv(GL_MODELVIEW_MATRIX, mv);

    shader.projectionMatrix.loadMatrix(proj);
    shader.modelViewMatrix.loadMatrix(mv);

    shader.jointTransforms.loadMatrixArray(entity.getJointTransforms());
    Eigen::Vector3f lightDir(0, 1, 0);
    shader.lightDirection.loadVector(lightDir);
}

// stops the shader after rendering
void Scene::finish() {
    shader.stop();
}

void Scene::render() {
	// 0, Vertices
	// 1, TextureCoords
	// 2, Normals
	// 3, JointIds
	// 4, VertexWeights
    vector<int> bindVec = {0, 1, 2, 3, 4};

    if (animate) 
        prepare();
    
    entity.getModel().bind(bindVec);        // binds and then enables the vertexattribarray
    // draws elements with information from shaders loaded during prepare()
    glDrawElements(GL_TRIANGLES, entity.getModel().getIndexCount(), GL_UNSIGNED_INT, 0);
    entity.getModel().unbind(bindVec);
    finish();
}


void Scene::toggleAnimate() {
    animate = !animate;
    std::cout << "Shader: " << animate << std::endl;
}

void Scene::setShowTexture(bool b) {
    showTexture = b;
    std::cout << "Textures: " << showTexture << std::endl;
    if (showTexture)
        entity.getTexture().bindToUnit(0);
    else
        entity.getTexture().unbind();
}

void Scene::toggleShowTexture() {
    setShowTexture(!showTexture);
}