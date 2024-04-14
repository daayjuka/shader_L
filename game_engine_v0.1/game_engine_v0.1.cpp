#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include "Shader.h"
#include <iostream>
#include <cmath>


const unsigned int S_WIDTH = 800;
const unsigned int S_HEIGHT = 800;


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);


int main(void)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);



	GLFWwindow* window = glfwCreateWindow(S_WIDTH, S_HEIGHT, "OPENGL_LEARNING", NULL, NULL);
	if (window == NULL) {
		std::cout << "failed create window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "failed to initialize glad" << std::endl;
	}


	Shader ourShader("PATH/shader.vs", "PATH/shader.fs");





	float vertices[] = {
		// first triangle
		0.0f, 0.4f, 0.0f, 0.1f, 0.4f, 1.0f,
		0.4f, -0.4f, 0.0f, 0.3f, 1.0f, 0.2f,  
		-0.4f, -0.4f, 0.0f, 1.0f, 0.2f, 0.7f
		//0.15f, 0.6f, 0.0f	// rigth top

	};
	float vertices2[] = {
		// second triangle+bottom
		0.6f, 0.6f, 0.0f,  // right bottom
		0.6f, 0.9f, 0.0f,  // right top
		-0.6f, 0.9f, 0.0f, 
		-0.6f, 0.6f, 0.0f
	};

	unsigned int indices[] = { // start from 0 !!!!
		0, 1, 2, //first triangle
		0, 2, 3  //second triangle
	};



	unsigned int VBO, VAO;
	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[0]);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	/*
	glBindVertexArray(VAO[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices2), indices2, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	*/

	//int nrAttributes;
	//glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
	//std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl; !16!


	//glViewport(0, 0, 800, 600);


	//render loop
	while (!glfwWindowShouldClose(window)) {
		//input
		processInput(window);

		//rendering commands
		//...
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		float currentTime = glfwGetTime();
		float offset1 = sin(currentTime) / 2.0f;
		float offset2 = cos(currentTime) / 2.0f;
		float cOffSet1 = sin(currentTime) / 2.0f;
		float cOffSet2 = cos(currentTime) / 3.0f;
		float cOffSet3 = sin(currentTime) / 4.0f;
		ourShader.use();
		glBindVertexArray(VAO);
		ourShader.setFloat("xOffset", offset1);
		ourShader.setFloat("yOffset", offset2);
		ourShader.setFloat("xColorSet", cOffSet1);
		ourShader.setFloat("yColorSet", cOffSet2);
		ourShader.setFloat("zColorSet", cOffSet3);

		glDrawArrays(GL_TRIANGLES, 0, 3);

		
		/*
		float timeValue = glfwGetTime();
		float greenValue = sin(timeValue) / 2.0f + 0.5f;
		int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
		glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
		//triangle
		*/



		/*
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glUseProgram(shaderProgram2);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
		
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);  IT CHANGES MODE FOR THE SEEING LINES!
		check, call events and swap buffers
		*/
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VBO);
	glDeleteBuffers(1, &VAO);


	/*
	//glDeleteBuffers(1, &EBO);
	glDeleteProgram(shaderProgram);
	glDeleteProgram(shaderProgram2);
	*/
	glfwTerminate();
	return 0;

}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}
