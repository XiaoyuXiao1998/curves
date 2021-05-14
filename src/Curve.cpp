#include "Curve.h"
#include"LineRender.h"
#include<learnopengl/shader_s.h>


void Curve::connectTheDots() {
	Pvector::iterator it, next;
	vector<float> drawpoints;
	if (points.size() > 1) {
		for (it = points.begin(); it != points.end(); it++) {
			drawpoints.push_back(it->x);
			drawpoints.push_back(it->y);
		}

		Shader ourShader("shaders\\Lineshader.vs", "shaders\\Lineshader_straight.fs");
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
	for (it = points.begin(); it != points.end(); it++) {
		it->draw();
	}
}


void Curve::draw(int lod) {
	//std::cout << points.size() << std::endl;
	if (!points.empty()) {
		connectTheDots();
	}
}


void Curve::addPoint(float x, float y) {
	if (!isactive) {
		//std::cout << "normx " << x << " " << y << std::endl;
		points.push_back(Point(x, y));
	}
}


void Curve::deleteActivePoint() {
	if (isactive) {
		points.erase(activePoint);
		isactive = false;
	}
}

// Moves the active point if non-null.
void Curve::moveActivePoint(float dx, float dy) {
	if (isactive) {
		activePoint->x += dx;
		activePoint->y += dy;
	}
}

// Update the active point, when you click on a new one.  
// The first part checks to make sure the click is outside a given 

void Curve::updateActivePoint(float x, float y) {
	float dx, dy, dist2;
	float radius = Point::ACTIVE_RADIUS * Point::ACTIVE_RADIUS;
	dist2 = 1;
	if (isactive) {
		dx = activePoint->x - x;
		dy = activePoint->y - y;
		dist2 = dx * dx + dy * dy;
	}
	if (dist2 > radius) {
		if (isactive) activePoint->active = false;
		isactive = false;
		for (Pvector::iterator it = points.begin(); it != points.end(); it++) {
			dx = it->x - x;
			dy = it->y - y;
			dist2 = dx * dx + dy * dy;
			if (dist2 < radius) {
				activePoint = it;
				it->active = true;
				isactive = true;
				break;
			}
		}
	}
}


void Curve::drawLine(float x1, float y1, float x2, float y2) {
	glColor3f(0, 0, 1);
	glBegin(GL_LINES);
	glVertex2f(x1, y1);
	glVertex2f(x2, y2);
	glEnd();
}

Curve::Curve()
{
	isactive = false;
}

Curve::~Curve()
{

}
