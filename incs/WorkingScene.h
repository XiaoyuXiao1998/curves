#if !defined(WORKINGSCENE_H)
#define WORKINGSCENE_H

#include "Scene.h"
#include<iostream>


// Working Scene refers to the Scene object.  

class WorkingScene : public Scene
{
public:
	static void drag(float x, float y);
	static void mouse(GLFWwindow* window,int button, int state, int mod);

	WorkingScene() {};
	virtual ~WorkingScene() {};

};

#endif