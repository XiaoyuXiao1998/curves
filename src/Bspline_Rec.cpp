#include"Bspline_Rec.h"
#include<learnopengl/shader_s.h>
//use de_boor algorithm 
static float k = 3; // k is the degree of basis spline function


void Bspline_Rec::draw(int levelOfDetail) {
	connectTheDots();
	
	int size = points.size();  // number of contorl points;
	vector<float> drawpoints;
	if ( size> k) {
		int num = size - 1;
		for (float u = k ; u < num + 1; u += 0.1) { 
			int ui = int(u);           
			// ui is left knot
			//copy the affected control points;
			Pvector cp;
			for (int i = ui - k; i <= ui; i++) {
				cp.push_back(Point(points[i].x, points[i].y));
			}
			
		
				for(int i = 1; i <= k; i++) {
					for (int j = k; j > i-1; j--) {
						float ai = (u - ui-j+k) / (j + k- i+1 - j);
						cp[j].x = ai * cp[j].x + (1.0f - ai) * cp[j - 1].x;
						cp[j].y = ai * cp[j].y + (1.0f - ai) * cp[j - 1].y;
					}
			}
		
				drawpoints.push_back(cp[k].x);
				drawpoints.push_back(cp[k].y);
				if (u-ui == 0 || u-ui>0.9) {
					 Point p(cp[k].x, cp[k].y);
		            p.draw();
					
				}
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


		//Point p(x, y);
		//p.draw();
		

	}

}
