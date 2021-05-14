
#include "Bspline.h"
#include<learnopengl/shader_s.h>

// The B-Spline drawing routine.  
// cubic uniform b-spline curve
void Bspline::draw(int levelOfDetail) {
	connectTheDots();

	Pvector::iterator p1, p2, p3, p4;
	int i = 1;
	for (Pvector::iterator it = points.begin(); it != points.end(); it++) {
		p1 = p2;
		p2 = p3;
		p3 = p4;
		p4 = it;
		if (i > 3) {
			drawSegment(p1, p2, p3, p4, levelOfDetail);
		}
		i++;
	}

}

void Bspline::drawSegment(Pvector::iterator p1, Pvector::iterator p2, Pvector::iterator p3, Pvector::iterator p4, int levelOfDetail) {

	vector<float> drawpoints;
	float x = 0, y = 0;
	float t;
	for (int i = 0; i <= levelOfDetail; i++) {
		t = i / float(levelOfDetail);
		//std::cout << t << " " << pow(t, 3) << std::endl;
		x = pow(t, 3) * (1.0f / 6.0f) * ((-1.0f) * p1->x + 3.0f * p2->x + (-3.0f) * p3->x + (1.0f) * p4->x) +
			pow(t, 2) * (1.0f / 6.0f) * ((3.0f) * p1->x + (-6.0f) * p2->x + (3.0f) * p3->x + (0.0f) * p4->x) +
			pow(t, 1) * (1.0f / 6.0f) * ((-3.0f) * p1->x + (0.0f) * p2->x + (3.0f) * p3->x + (0.0f) * p4->x) +
			pow(t, 0) * (1.0f / 6.0f) * ((1.0f) * p1->x + (4.0f) * p2->x + (1.0f) * p3->x + (0.0f) * p4->x);

		y = pow(t, 3) * (1.0f / 6.0f) * ((-1.0f) * p1->y + 3.0f * p2->y + (-3.0f) * p3->y + (1.0f) * p4->y) +
			pow(t, 2) * (1.0f / 6.0f) * ((3.0f) * p1->y + (-6.0f) * p2->y + (3.0f) * p3->y + (0.0f) * p4->y) +
			pow(t, 1) * (1.0f / 6.0f) * ((-3.0f) * p1->y + (0.0f) * p2->y + (3.0f) * p3->y + (0.0f) * p4->y) +
			pow(t, 0) * (1.0f / 6.0f) * ((1.0f) * p1->y + (4.0f) * p2->y + (1.0f) * p3->y + (0.0f) * p4->y);
		drawpoints.push_back(x);
		drawpoints.push_back(y);
	}
	//draw linesegment
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


	Point p(x, y);
	p.draw();
}
