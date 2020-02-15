#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "ShaderProgram.h"

#define VERTEX_SIZE 3

int main(void) {

	if (!glfwInit()) {
		return -1;
	}

	GLFWwindow* window;

	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);

	window = glfwCreateWindow(800, 800, "Definitly Robotics", NULL, NULL);

	if (!window) {
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK) {
		glfwTerminate();
		return -1;
	}

	float verticies[VERTEX_SIZE * 4] = {
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		-1.0f, 0.0f, 0.0f,
		0.0f, -1.0f, 0.0f
	};

	unsigned int indicies[6] = {
		0,1,2,
		0,3,2
	};

	unsigned int vbo, ibo;

	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ibo);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * VERTEX_SIZE * 4, verticies, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * 6, indicies, GL_STATIC_DRAW);

	ShaderProgram* shaderPrg = new ShaderProgram("res/shaders/shader0.vsh", "res/shaders/shader0.fsh");

	glClearColor(1.0f, 0.0f, 0.0f, 1.0f);

	while (!glfwWindowShouldClose(window)) {
		
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shaderPrg->Use();
		glUniform4f(shaderPrg->GetUniformLocation("color"), 0.0f, 1.0f, 1.0f, 1.0f);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);

		glfwPollEvents();

	}

}