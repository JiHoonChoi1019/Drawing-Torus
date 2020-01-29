#include <Windows.h>

#include "glSetup.h"
//#include "glSetup.cpp"

#include "include/GLFW/glfw3.h"
#include "include/GL/gl.h"
#include "include/GL/glut.h"

#include "include/glm/glm.hpp" //OpenGl Mathematics
#include "include/glm/gtc/type_ptr.hpp" //glm::value_ptr()
#include "include/glm/gtc/matrix_transform.hpp"

#pragma comment(lib, "lib/glfw3.lib")
#pragma comment(lib, "lib/opengl32.lib")
#pragma comment(lib, "lib/glut32.lib")

using namespace glm;

#include <iostream>
using namespace std;

//Camera configuration
vec3 eye(3, 3, 3);
vec3 center(0, 0, 0);
vec3 up(0, 1, 0);

//Global coordinate frame
float AXIS_LENGTH = 2;
float AXIS_LINE_WIDTH = 2;

//Colors
GLfloat bgColor[4] = { 1, 1, 1, 1 };

//Selected example
int selection = 0;

vec4 p[36][18];

int keyA = 1;
int keyJ = 18;

void
torusFunc()
{
	for (int i = 0; i < keyA; i++)
	{
		for (int j = 0; j < keyJ; j++)
		{
			if (i == 35)
			{
				glVertex3f(p[i][j].x, p[i][j].y, p[i][j].z);
				glVertex3f(p[0][j].x, p[0][j].y, p[0][j].z);
				if (j == 17)
				{
					glVertex3f(p[0][0].x, p[0][0].y, p[0][0].z);
					glVertex3f(p[i][0].x, p[i][0].y, p[i][0].z);
				}
				else
				{
					glVertex3f(p[0][j + 1].x, p[0][j + 1].y, p[0][j + 1].z);
					glVertex3f(p[i][j + 1].x, p[i][j + 1].y, p[i][j + 1].z);
				}
			}
			else
			{
				glVertex3f(p[i][j].x, p[i][j].y, p[i][j].z);
				glVertex3f(p[i + 1][j].x, p[i + 1][j].y, p[i + 1][j].z);
				if (j == 17)
				{
					glVertex3f(p[i + 1][0].x, p[i + 1][0].y, p[i + 1][0].z);
					glVertex3f(p[i][0].x, p[i][0].y, p[i][0].z);
				}
				else
				{
					glVertex3f(p[i + 1][j + 1].x, p[i + 1][j + 1].y, p[i + 1][j + 1].z);
					glVertex3f(p[i][j + 1].x, p[i][j + 1].y, p[i][j + 1].z);
				}
			}
			glEnd();
			glBegin(GL_QUADS);
		}
	}
}

void
setTorusPoints()
{
	vec3 cenP(1.2, 1.2, 0.0);
	vec3 sP(0.5, 0, 0);
	vec3 yAxis(0, 1, 0);
	vec3 zAxis(0, 0, 1);

	float rTheta = 0.0f;
	float yrTheta = 0.0f;

	vec4 rV;
	mat4 tM = translate(mat4(1.0), cenP);

	for (int i = 0; i < 18; i++)
	{
		vec4 sP4(0.4, 0.0, 0.0, 1.0);

		mat4 R = rotate(mat4(1.0), radians(20.0f*i), zAxis);

		vec4 rotatedSP = R * sP4;

		rV = tM * rotatedSP;
		p[0][i] = rV;

	}

	for (int j = 0; j < 36; j++)
	{
		for (int i = 0; i < 18; i++)
		{
			mat4 R2 = rotate(mat4(1.0), radians(10.f*j), yAxis);
			vec4 rotateP(p[0][i].x, p[0][i].y, p[0][i].z, 1.0);
			vec4 rotatedCircle = R2 * rotateP;
			p[j][i] = rotatedCircle;
			glVertex3f(p[j][i].x, p[j][i].y, p[j][i].z);

		}
	}
}

void
drawTorusPoints()
{
	vec3 cenP(1.2, 1.2, 0.0);
	vec3 sP(0.5, 0, 0);
	vec3 yAxis(0, 1, 0);
	vec3 zAxis(0, 0, 1);

	glPointSize(2 * dpiScaling);
	glBegin(GL_POINTS);

	float rTheta = 0.0;
	float yrTheta = 0.0;

	vec4 rV;
	mat4 tM = translate(mat4(1.0), cenP);

	glColor3f(0, 0, 0);

	for (int i = 0; i < 18; i++)
	{
		vec4 sP4(0.4, 0.0, 0.0, 1.0);

		mat4 R = rotate(mat4(1.0), radians(20.0f*i), zAxis);

		vec4 rotatedSP = R * sP4;

		rV = tM * rotatedSP;
		p[0][i] = rV;
	}

	for (int j = 0; j < keyA; j++)
	{
		for (int i = 0; i < keyJ; i++)
		{
			mat4 R2 = rotate(mat4(1.0), radians(10.0f*j), yAxis);
			vec4 rotateP(p[0][i].x, p[0][i].y, p[0][i].z, 1.0);
			vec4 rotatedCircle = R2 * rotateP;
			p[j][i] = rotatedCircle;
			glVertex3f(p[j][i].x, p[j][i].y, p[j][i].z);
		}
	}
	glEnd();
}

void
drawTorusLine()
{
	glEnable(GL_POLYGON_OFFSET_FILL);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glPolygonOffset(1.0f, 1.0f);

	glBegin(GL_QUADS);
	glColor3f(0, 0, 0);

	torusFunc();

	glEnd();
}

void
drawTorus()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glBegin(GL_QUADS);
	glColor3f(0, 0, 1);

	torusFunc();

	glEnd();
}

void
drawTorusWithLine()
{
	glPolygonOffset(1.0f, 1.0f);
	glEnable(GL_POLYGON_OFFSET_FILL);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	drawTorus();

	glPolygonOffset(0.0f, 0.0f);
	glDisable(GL_POLYGON_OFFSET_FILL);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	drawTorusLine();
}

void
init()
{
	//Keyboard
	cout << "Keyboard input: space for play/pause" << endl;
	cout << "Keyboard input: up for increasing period" << endl;
	cout << "Keyboard input: down for decreasing period" << endl;
	cout << "Keyboard input: 1 for draw Points" << endl;
	cout << "Keyboard input: 2 for wireframe only" << endl;
	cout << "Keyboard input: 3 for quads only" << endl;
	cout << "Keyboard input: 4 for quads and wireframe" << endl;
	cout << "Keyboard input: 5 for draw normal vectors of the polygons" << endl;
	cout << "Keyboard input: 6 for Two-sided constant shading with the wireframe" << endl;
	cout << "Keyboard input: a,s for increase/decrease sweep angle by 10 around the y-axis" << endl;
	cout << "Keyboard input: j,k for increase/decrease sweep angle by 10 around the z-axis" << endl;
}

void
render(GLFWwindow* window)
{
	//Background color
	glClearColor(bgColor[0], bgColor[1], bgColor[2], bgColor[3]);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Modelview matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(eye[0], eye[1], eye[2], center[0], center[1], center[2], up[0], up[1], up[2]);

	//Axes
	glDisable(GL_LIGHTING);
	drawAxes(AXIS_LENGTH, AXIS_LINE_WIDTH*dpiScaling);

	setTorusPoints();

	switch (selection)
	{
	case 1: drawTorusPoints(); break;
	case 2: drawTorusLine(); break;
	case 3: drawTorus(); break;
	case 4: drawTorusWithLine(); break;
	case 5:; break;
	case 6:; break;
	}
}

void
keyboard(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS || action == GLFW_REPEAT)
	{
		switch (key)
		{
			//Quit
		case GLFW_KEY_Q:
		case GLFW_KEY_ESCAPE: glfwSetWindowShouldClose(window, GL_TRUE); break;

			//Example selection
		case GLFW_KEY_1: selection = 1; break;
		case GLFW_KEY_2: selection = 2; break;
		case GLFW_KEY_3: selection = 3; break;
		case GLFW_KEY_4: selection = 4; break;
		case GLFW_KEY_5: selection = 5; break;
		case GLFW_KEY_6: selection = 6; break;
		case GLFW_KEY_A:
			if (keyA > 35)
				keyA = 36;
			else keyA += 1;
			break;
		case GLFW_KEY_S:
			if (keyA <= 0)
				keyA = 0;
			else keyA -= 1;
			break;
		case GLFW_KEY_J:
			if (keyJ > 17)
				keyJ = 18;
			else keyJ += 1;
			break;
		case GLFW_KEY_K:
			if (keyJ <= 0)
				keyJ = 0;
			else keyJ -= 1;

			break;
		}
	}
}

int
main(int argc, char* argv[])
{
	//Initialize the OpenGL system
	GLFWwindow* window = initializeOpenGL(argc, argv, bgColor);
	if (window == NULL) return -1;

	//Callbacks
	glfwSetKeyCallback(window, keyboard);

	//Depth test
	glEnable(GL_DEPTH_TEST);

	//Normal vectors are normalized after transformation.
	glEnable(GL_NORMALIZE);

	//Viewport and perspective setting
	reshape(window, windowW, windowH);

	//Initializeation - Main loop - Finalization
	init();

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents(); //Events

		render(window); //Draw one frame
		glfwSwapBuffers(window); //Swap buffers
	}

	//Terminate the glfw system
	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}