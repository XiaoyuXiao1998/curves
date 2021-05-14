#if !defined(CLASS_SCENE)
#define CLASS_SCENE

#include "Curve.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>



class Scene {
public:
	static int height;
	static int width;
	static float oldx;
	static float oldy;

	static int levelOfDetail;

	static Curve * theOnlyCurve;
	Scene();
	virtual ~Scene();
	static void keyboard(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void reshape(int w, int h);
	static void passiveMotion(int x, int y);
	static void drag(float x, float y);
	static void mouse(int button, int state, int x, int y);


};

#endif // !defined(CLASS_SCENE)

