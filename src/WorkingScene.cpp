#include "WorkingScene.h"

void WorkingScene::drag(float x, float y) {
	int diffx = x - oldx;
	int diffy = oldy - y;
	//std::cout << x<<"  s"<<y<<" "<<oldx<<" "<<oldy<< std::endl;
	float normx = diffx / (float)width, normy = diffy / (float)height;
	theOnlyCurve->moveActivePoint(normx, normy);
	oldx = x;
	oldy = y;


}

// Mouse motion. 
void WorkingScene::mouse(GLFWwindow* window,int button, int state, int mod) {
	double x, y;
	glfwGetCursorPos(window, &x, &y);



	if (theOnlyCurve &&state == GLFW_PRESS) {
		float normx = x / (float)width, normy = (height - y) / (float)height;
		if (button == GLFW_MOUSE_BUTTON_LEFT) {
			
	
				theOnlyCurve->addPoint(normx, normy);
	
		}
		if (button == GLFW_MOUSE_BUTTON_RIGHT) {
			theOnlyCurve->updateActivePoint(normx, normy);
			theOnlyCurve->deleteActivePoint();
		}
	}
	oldx = x;
	oldy = y;
}
