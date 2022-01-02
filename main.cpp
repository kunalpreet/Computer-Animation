#ifdef __APPLE__
#  define GL_SILENCE_DEPRECATION
#  include <OpenGL/gl3.h>
#  include <OpenGL/glu.h>
#  include <GLUT/glut.h>
#else
#  include <GL/glew.h>
#  include <GL/gl.h>
#  include <GL/glu.h>
#  include <GL/freeglut.h>
#endif

#include <stdio.h>
#include <stdlib.h>

#include "Scene.h"
#include "SceneLoader.h"

#include <string>
#include <iostream>
#include <fstream>

using namespace std;

/*
Group number: 3
Kenneth Mak, makk4, 001318946
Kunalpreet Matharu, mathak1, 400258512
*/

int const fps = 30; //30;
int const winW = 600;
int const winH = 600;

Eigen::Vector3f camPos(2, 5, 5);
Eigen::Vector3f targetPos(0, 0, 0);
Eigen::Vector3f camUp(0, 1, 0);

// for camera control
bool anglingCamera = false;         // using mouse to change directino of camera
const float cameraPanSpeed = 0.1f;  // constant speed (sensitivity)
const float cameraMoveSpeed = 0.5f;
float mousePos[2] = {0.0, 0.0};

// Storing scenes - intended to have multiple scenes for each model
vector<Scene> sceneControl;

void printText();

// this should move the camera along the x, y, z axis of the normal it is looking at; bool determines if only angle movement, or also strafing
void moveCamera(float x, float y, float z, bool strafe) {
	// modifier vector
	Eigen::Vector3f mod(x, y, z);
	// move camera based on x,y,z with respect to the normal
	Eigen::Vector3f cameraNorm = (targetPos - camPos).normalized();
	// cross product w/ arbitrary 'up' vector to get left/right 
	Eigen::Vector3f cameraRight = cameraNorm.cross(camUp.normalized());
	// cross product of two vectors gives 90 degree to both; in this case, up or down
	Eigen::Vector3f cameraUp = cameraRight.cross(cameraNorm).normalized();

	targetPos += (cameraRight * mod(0)); 
	targetPos += (cameraUp * mod(1)); 
	targetPos += (cameraNorm * mod(2)); 

    if (strafe) {
        camPos += (cameraRight * mod(0)); 
        camPos += (cameraUp * mod(1)); 
        camPos += (cameraNorm * mod(2)); 
    }
}
// for mouse angling; taking in delta mouse movement since last motion
void updateCamera(int deltaX, int deltaY) {
	// take in mouse movement
	// apply change
	float x = deltaX * cameraPanSpeed;
	float y = deltaY * cameraPanSpeed;
	float z = 0;

	// move camera only in regards to angle
	moveCamera(x, y, z, false);
}


void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	// camera
	glLoadIdentity();
    
    // lookat camera function to set viewpoint
	gluLookAt(  camPos[0], camPos[1], camPos[2], 
                targetPos[0], targetPos[1], targetPos[2],  
                camUp[0], camUp[1], camUp[2]);

    // drawing generic cube for reference to world
    glPushMatrix();
        glColor3f(0.5, 1.0, 0.5);
        glTranslatef(0, 0, 0);
        glutSolidCube(1);
    glPopMatrix();

    for (Scene &scene : sceneControl) {
        scene.render();
    }   
	glutSwapBuffers();
}

void loadFiles() {

    // testing loading .DAE file into XmlFile
    string path = "assets/model.DAE";
    string texturePath = "assets/diffuse.png";
    cout << "Reading file from " << path << endl << endl;
    ifstream myEntity = ifstream(path);
    ifstream myTexture = ifstream(texturePath);
    ifstream myAnimation = ifstream(path);
    
    // Generate new scene with given model and animation files
    Scene newScene = SceneLoader::loadScene(myEntity, myTexture, myAnimation);
    sceneControl.push_back(newScene);

    myEntity.close();
    myTexture.close();
    myAnimation.close();
    cout << "Loaded model from file!" << endl << endl;
}

// void gluttimerfunc; updates
void update(int val) {
    // cout << "Updating: " << endl;
    float elapsedTime = (1000.0f/fps)/1000.0f; // update time is in ms; divide to return seconds
    for (Scene &scene : sceneControl) {
        scene.update(elapsedTime);
    }   

	glutPostRedisplay(); 		// request update

	glutTimerFunc(1000 / fps, update, 0); // setting timer for next fps update
}

void keyboard(unsigned char key, int x, int y) {
    switch(key) {
        case 'w':
			moveCamera(0, 0, cameraMoveSpeed, true);
            break;
        case 's':
			moveCamera(0, 0, -cameraMoveSpeed, true);
            break;
        case 'a':
			moveCamera(-cameraMoveSpeed, 0, 0, true);
            break;
        case 'd':
			moveCamera(cameraMoveSpeed, 0, 0, true);
            break;
        case 'r':
			moveCamera(0, cameraMoveSpeed, 0, true);
            break;
        case 'f':
			moveCamera(0, -cameraMoveSpeed, 0, true);
            break;
        case 32:
            sceneControl.front().toggleAnimate();
            break;
        case 't':
            sceneControl.front().toggleShowTexture();
            break;
        case 'p':
            printText();
            break;
        case 'q':
            exit(0);
            break;
        default: break;
    }
}
/* Input - Mouse Callback */
void mouse(int button, int state, int x, int y){
	mousePos[0] = x; 
	mousePos[1] = winH - y;
	if (state == GLUT_DOWN) {
        anglingCamera = true;
	} else if (state == GLUT_UP) {
		anglingCamera = false;
	}
}
// Callback for active and passive mouse movement 
void motion(int x, int y){
    if (anglingCamera) {
        updateCamera(x - mousePos[0], (winH - y) - mousePos[1]);
    }
	mousePos[0] = x;
	mousePos[1] = winH - y;
}

void init(void) {
    // background colour
	glClearColor(0.2, 0.2, 0.2, 0);
	glColor3f(1, 1, 1);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
//	glOrtho(-5, 5, -5, 5, -5, 80);
	gluPerspective(70, 1, 1, 100);

    loadFiles();

    cout << "Init finished" << endl;
    printText();
}

/* main function - program entry point */
int main(int argc, char** argv)
{
	glutInit(&argc, argv);		//starts up GLUT
	
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(winW, winH);
	glutInitWindowPosition(100, 100);

	glutCreateWindow("FinalAssignment");	//creates the window
	
    #ifndef __APPLE__
        // need this to prevent segmentation fault in VAO
        glewExperimental = GL_TRUE; 
        GLenum err = glewInit();
        if (GLEW_OK != err)    {
            /* Problem: glewInit failed, something is seriously wrong. */
            fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
        }
        fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));
    #endif


	glutDisplayFunc(display);	//registers "display" as the display callback function
	
	glutTimerFunc(1000 / fps, update, 0);
    glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	
	// both motions call same callback
	glutMotionFunc(motion);
	glutPassiveMotionFunc(motion);


	// Enable Textures
	glEnable(GL_TEXTURE_2D);

	glEnable(GL_DEPTH_TEST);
    
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);

    init();

	glutMainLoop();				//starts the event loop

    return 0;
}


void printText() {
	cout << "\n===Commands List===\n"
		<< "W S - Moves camera forward and back" << endl 
		<< "A D - Moves camera right and left" << endl 
		<< "R F - Moves camera up and down" << endl 
		<< "LMB/RMB - Clicking and dragging will pan the camera" << endl 
		<< "Spacebar - Toggles the shader program to change model vertices and textures" << endl
		<< "t - Toggles whether textures should be rendered" << endl
		// Selected Object Interaction 
		<< "Q - Quits and exits the program" << endl
		<< "Press 'p' at any time to view the commands again." << endl
		<< endl;
}