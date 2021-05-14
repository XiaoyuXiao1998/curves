#include<glad/glad.h>
#include <GLFW/glfw3.h>
#include <math.h>
#include "Point.h"
#include<iostream>
#include <learnopengl/shader_s.h>


const float Point::ACTIVE_RADIUS = 0.05;


void Point::draw() {
	//std::cout << "I draw" << std::endl;
	if (active) {
		glColor3f(1, 0, 0);
		glBegin(GL_LINE_LOOP);
		float u, v;
		for (float t = 0; t < 2 * 3.14159; t += 0.1) {
			u = cos(t) * ACTIVE_RADIUS + x;
			v = sin(t) * ACTIVE_RADIUS + y;
			glVertex3f(u, v, 0);
		}
		glEnd();
	}

	float pointposition[] = {
		x + 0.01, y + 0.01, // top right
		x + 0.01, y - 0.01, //bottom right
		x - 0.01, y - 0.01, // bottom left
		x - 0.01, y + 0.01, //top left

	};

	unsigned int indices[] = {  // note that we start from 0!
	0, 1, 3,   // first triangle
	1, 2, 3    // second triangle
	};
	

	unsigned int VAO, VBO,EBO;
	glGenVertexArrays(1,&VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(pointposition),pointposition, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);	// Vertex attributes stay the same
	glEnableVertexAttribArray(0);
	Shader ourShader("shaders\\Pointshader.vs", "shaders\\Pointshader.fs");
	ourShader.use();

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

}

Point::Point(float xpos, float ypos)
{
	x = xpos;
	y = ypos;
	active = false;
}

Point::~Point()
{

}