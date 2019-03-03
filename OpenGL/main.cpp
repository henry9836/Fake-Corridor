#include <glew.h>
#include <freeglut.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>   
#include <time.h>   
#include "ShaderLoader.h"

float r = 1.0;
float b = 1.0;
float g = 1.0;

GLuint groundpro = NULL;
GLuint toppro = NULL;
GLuint wallpro1 = NULL;
GLuint wallpro2 = NULL;
GLfloat currentTime;

//GLOBAL Verts
GLuint Light = NULL;
GLfloat Light_vertices[] = {
	0.075f, 0.3f, 0.0f, 0.97f, 0.86f, 0.21f,
	0.6f, 0.9f, 0.0f,	0.97f, 0.86f, 0.21f,
	-0.6f, 0.9f, 0.0f,	0.97f, 0.86f, 0.21f,
	0.075f, 0.3f, 0.0f, 0.97f, 0.86f, 0.21f,
	-0.6f, 0.9f, 0.0f,	0.97f, 0.86f, 0.21f,
	-0.075f, 0.3f, 0.0f,0.97f, 0.86f, 0.21f,
};
GLuint VAO;
GLuint VBO;

GLuint Paintingpro = NULL;
GLfloat Painting_vertices[] = {
	0.9f, -0.2f, 0.0f, 0.1f, 0.0f, 0.0f,
	0.9f, 0.1f, 0.0f,	0.0f, 0.1f, 0.0f,
	0.5f, 0.0f, 0.0f,	0.0f, 0.0f, 0.1f,
	0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.1f,
	0.9f, 0.1f, 0.0f, 0.0f, 0.1f, 0.0f,
	0.5f, 0.2f, 0.0f, 0.1f, 0.0f, 0.0f,
};
GLuint VAO_Painting;
GLuint VBO_Painting;




void Render() {
	glClear(GL_COLOR_BUFFER_BIT);
	
	r = (rand() % 10 + 1)/10.0f;
	g = (rand() % 10 + 1)/10.0f;
	b = (rand() % 10 + 1)/10.0f;
	glClearColor(r, g, b, 1.0);

	//SHADERS
	glUseProgram(groundpro);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glUseProgram(0);
	glUseProgram(toppro);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glUseProgram(0);
	glUseProgram(wallpro1);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glUseProgram(0);
	glUseProgram(wallpro2);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glUseProgram(0);
	
	
	glUseProgram(Light);
	glBindVertexArray(VAO);

	GLint currentTimeLoc = glGetUniformLocation(Light, "currentTime");
	glUniform1f(currentTimeLoc, currentTime);

	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
	glUseProgram(0);
	
	glUseProgram(Paintingpro);
	glBindVertexArray(VAO_Painting);
	
	glUniform1f(currentTimeLoc, currentTime);

	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
	glUseProgram(0);

	glutSwapBuffers();
}

void Update() {
	currentTime = glutGet(GLUT_ELAPSED_TIME);
	currentTime = currentTime * 0.001f;



	glutPostRedisplay();
}

int main(int argc, char **argv) {
	srand(time(NULL));

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 50);
	glutInitWindowSize(550, 800);
	glutCreateWindow("Fake Corridor");

	if (glewInit() != GLEW_OK) {

		std::cout << "Glew INIT FAILED";
		system("pause");
	}

	glClearColor(1.0, 0.0, 0.0, 1.0);

	//INIT SHADERS
	groundpro = ShaderLoader::CreateProgram("ground.vs", "ground.fs");
	toppro = ShaderLoader::CreateProgram("top.vs", "top.fs");
	wallpro1 = ShaderLoader::CreateProgram("side1.vs", "side1.fs");
	wallpro2 = ShaderLoader::CreateProgram("side2.vs", "side2.fs");

	Light = ShaderLoader::CreateProgram("light.vs", "light.fs");
	Paintingpro = ShaderLoader::CreateProgram("light.vs", "light.fs");
	

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Light_vertices), Light_vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(
		0,
		3,
		GL_FLOAT,
		GL_FALSE,
		6 * sizeof(GLfloat),
		(GLvoid*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(
		1,
		3,
		GL_FLOAT,
		GL_FALSE,
		6 * sizeof(GLfloat),
		(GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);




	glGenVertexArrays(1, &VAO_Painting);
	glBindVertexArray(VAO_Painting);
	glGenBuffers(1, &VBO_Painting);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_Painting);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Painting_vertices), Painting_vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(
		0,
		3,
		GL_FLOAT,
		GL_FALSE,
		6 * sizeof(GLfloat),
		(GLvoid*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(
		1,
		3,
		GL_FLOAT,
		GL_FALSE,
		6 * sizeof(GLfloat),
		(GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	
	glutDisplayFunc(Render);

	glutIdleFunc(Update);

	glutMainLoop();

	return 0;
}