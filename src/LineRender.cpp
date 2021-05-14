#include"LineRender.h"
//static GLuint VAO;
//static GLuint VBO;
//static GLuint EBO;
void RenderLine(std::vector<float>& points) {
	GLuint VAO;
    GLuint VBO;
	GLuint EBO;
	glLineWidth(3.0);
	std::vector<unsigned int> indecies;

	int n = points.size() / 3;
	for (unsigned int i = 0; i < n ;i++)
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

		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * points.size(), points.data(), GL_STATIC_DRAW);
	//	//std::cout << points.size() << "=======================" << std::endl;
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indecies.size(), indecies.data(), GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
		//glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(position.x, position.y, 0.0f));

		glDrawElements(GL_LINES, indecies.size(), GL_UNSIGNED_INT, (void*)0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
		glDeleteBuffers(1, &EBO);
		glDeleteBuffers(1, &VBO);
		glDeleteVertexArrays(1, &VAO);
	}

	
