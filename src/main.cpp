#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include<iostream>
#include"WorkingScene.h"
#include <learnopengl/shader_s.h>


WorkingScene scene;
void cursorpos(GLFWwindow* window, double x, double y);


int main() {

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    //---------------------------------------------------
    GLFWwindow* window = glfwCreateWindow(scene.width, scene.height, "draw_curves", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, scene.keyboard);
    glfwSetCursorPosCallback(window, cursorpos);
  
    glfwSetMouseButtonCallback(window, scene.mouse);
    
    


     // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }


    // render loop
// -----------
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
    
       

        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        //glOrtho(0, scene.width, 0, scene.height, 100, -100);

        if (scene.theOnlyCurve) {
           
         
            scene.theOnlyCurve->draw(scene.levelOfDetail);
        }

   
        

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

void cursorpos(GLFWwindow *window, double x, double y) {
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
    {
        scene.passiveMotion(x, y);
    }
    else {
        scene.drag(x, y);
    }


}
