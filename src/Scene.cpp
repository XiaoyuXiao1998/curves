#include "Scene.h"
#include "Bezier.h"
#include "Bspline.h"
#include "Bezier2.h"
#include<iostream>


int Scene::height = 800;
int Scene::width = 800;
float Scene::oldx = 0;
float Scene::oldy = 0;
int Scene::levelOfDetail = 5;


 
Curve* Scene::theOnlyCurve = NULL;


void Scene::keyboard(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action != GLFW_PRESS) return;


	switch (key) {
	case GLFW_KEY_KP_0:
		if (theOnlyCurve) delete theOnlyCurve;

		theOnlyCurve = new Curve();
		printf("Straight Line.\n");
		break;
	case GLFW_KEY_KP_1:
		if (theOnlyCurve) delete theOnlyCurve;
		theOnlyCurve = new Bezier();
		printf("Bezier Curve.\n");
		break;
	case GLFW_KEY_KP_2:
		if (theOnlyCurve) delete theOnlyCurve;
		theOnlyCurve = new Bspline();
		printf("Bspline Curve.\n");
		break;
	case GLFW_KEY_KP_3:
		if (theOnlyCurve) delete theOnlyCurve;
		theOnlyCurve = new Bezier2();
		printf("Bezier 2 Curve.\n");
		break;
	case GLFW_KEY_KP_ADD:
		levelOfDetail++;
		break;
	case GLFW_KEY_KP_SUBTRACT:
		levelOfDetail--;
		break;
	case GLFW_KEY_Q:
		exit(0);
		break;
	}
	if (levelOfDetail < 1) {
		levelOfDetail = 1;
	}
	printf("Level of Detail: %d.\n", levelOfDetail);

}

// Standard reshape functions to change width and height as needed.  
void Scene::reshape(int w, int h) {
	width = w;
	height = h;
	glViewport(0, 0, w, h);
}


void Scene::drag(float x, float y) {}


void Scene::passiveMotion(int x, int y) {
	if (theOnlyCurve != NULL) {
		theOnlyCurve->updateActivePoint(x / (float)width, (height - y) / (float)height);
	
	}

}


void Scene::mouse(int button, int state, int x, int y) {}


Scene::Scene() {
}

Scene::~Scene() {

}

