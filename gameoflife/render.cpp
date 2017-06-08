#include "stdafx.h"

#include "render.h"
#include "gridwrapper.h"

#define RGBA 00000001b

extern GridWrapper grid_wrapper;

const int window_width = 800;
const int window_height = 800;

void render_init(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitWindowSize(window_width, window_height);
	glutInitWindowPosition(-1, -1);
	glutCreateWindow("Game of Life");
	glutDisplayFunc(render);
	glutIdleFunc(idle);
	gluOrtho2D(0.0, window_width, 0.0, window_height);
	glutInitDisplayMode(GLUT_LUMINANCE | GLUT_DOUBLE);
}

void render() {
	// Draw grid
	glBegin(GL_LINES);
	for (float x = window_width / grid_width; x < window_width; x += window_width / grid_width) {
		glVertex2f(x, 0.0f);
		glVertex2f(x, window_height);
	}
	for (float y = window_height / grid_height; y < window_height; y += window_height / grid_height) {
		glVertex2f(0.0f, y);
		glVertex2f(window_width, y);
	}
	glEnd();

	// Draw cells

	glutSwapBuffers();
}

void idle() {
	glutPostRedisplay();
}