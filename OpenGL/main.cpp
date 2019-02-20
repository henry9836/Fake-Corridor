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

	glutSwapBuffers();
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

	glutDisplayFunc(Render);

	glutMainLoop();

	return 0;
}