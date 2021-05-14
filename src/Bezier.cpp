#include "Bezier.h"
#include<learnopengl/shader_s.h>


// Bezier drawing function.  This is by deCasteljau or equivalent algorithm. 

void Bezier::draw(int levelOfDetail) {


	connectTheDots();

	Pvector::iterator p;

	int numpoints = points.size();
	//std::cout << numpoints << std::endl;
	if (numpoints <= 1) return;
	float steps = 2000;
	vector<float> drawpoints;

	for (int k = 0; k <= steps; k++) {
		float t = float(k) / steps;
		Pvector cp;
		for (int i = 0; i < numpoints; i++) {
			cp.push_back(points[i]);
		}

		for (int i = 1; i < numpoints; i++) {
			for (int j = 0; j < numpoints - i; j++) {
				cp[j].x = t * cp[j + 1].x + (1 - t) * cp[j].x;
				cp[j].y = t * cp[j + 1].y + (1 - t) * cp[j].y;
			}
		}
		drawpoints.push_back(cp[0].x);
		drawpoints.push_back(cp[0].y);
	}
	Shader ourShader("shaders\\Lineshader.vs", "shaders\\Lineshader.fs");
	ourShader.use();
	unsigned int VAO, VBO, EBO;
	glLineWidth(3.0);
	vector<unsigned int> indecies;

	int n = drawpoints.size() / 2;
	for (unsigned int i = 0; i < n; i++)
	{
		if (i != n - 1) {
			indecies.push_back(i);
			if (i < n)
				indecies.push_back(i + 1);
		}
	}
	//std::cout << indecies.size() << std::endl;
		// Configure VAO/VBO for texture quads
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * drawpoints.size(), drawpoints.data(), GL_STATIC_DRAW);
	//	//std::cout << points.size() << "=======================" << std::endl;
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indecies.size(), indecies.data(), GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (void*)0);
	//glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(position.x, position.y, 0.0f));

	glDrawElements(GL_LINES, indecies.size(), GL_UNSIGNED_INT, (void*)0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glDeleteBuffers(1, &EBO);
	glDeleteBuffers(1, &VBO);
}
