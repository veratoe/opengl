#define GLM_FORCE_RADIANS

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "shader.h"

using namespace std;

float bufferData[3000];

GLuint vbo, vao;

void setupVAO() {
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
}

void setupVBO() {
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(bufferData), bufferData, GL_DYNAMIC_DRAW);
}

void setupViewPort() {
	glViewport(0, 0, 640, 480);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// alpha blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void updateCamera() {
	glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);
	glm::mat4 trans;
	trans = glm::translate(trans, glm::vec3(1.0f, 1.0f, 0.0f));
	vec = trans * vec;
	std::cout << vec.x << vec.y << vec.z << std::endl; 
}

void createPixels() {
	int i;
	for (i = 0; i < 1000; i++) {
		bufferData[i*3] = rand()/float(RAND_MAX)* 2 - 1;
		bufferData[i*3+1] = rand()/float(RAND_MAX) * 2 -1; 
		bufferData[i*3+2] = 0.0f;
	}
	setupVBO();
}

void draw(Shader shader) {
	glClearColor(0.1f, 0.15f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(shader.Program);
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 1000);
	glBindVertexArray(0);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_A) {
		createPixels();
	}

	if (key == GLFW_KEY_Q) {
		updateCamera();
	}
	if (key == GLFW_KEY_ESCAPE) {
		glfwTerminate();
		exit(0);
	}	
}

void initGlew () {
	glewExperimental = GL_TRUE;
	GLenum error = glewInit();
	if (error != GLEW_OK) {
		printf("Error on glewInit(): %s\n", glewGetErrorString(error));
	}
	if (!GLEW_VERSION_2_1) {
		printf("Error: wrong OpenGL version < 2.1");
		exit(1);	
	}
}

int main(void) {
	GLFWwindow* 	window;
	
	if (!glfwInit()) {
		return -1; 
	}

	window = glfwCreateWindow(640, 480, "Hello world", NULL, NULL);
	if (!window) {
		glfwTerminate();
		return -1;
	}
			
	glfwMakeContextCurrent(window);
	initGlew();
	glfwSetKeyCallback(window, key_callback);
	createPixels();
	setupVBO();
	setupViewPort();
	setupVAO();

	Shader shader("basic.vs", "basic.frag");
	
	while(!glfwWindowShouldClose(window)) {
		draw(shader);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}	
	
}
