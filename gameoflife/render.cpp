#include "stdafx.h"

#include "render.h"
#include "gridwrapper.h"

#define RGBA 00000001b

extern GridWrapper grid_wrapper;

const int window_width = 800;
const int window_height = 800;

bool play = false;

void render_init(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitWindowSize(window_width, window_height);
	glutInitWindowPosition(-1, -1);
	glutInitDisplayMode(GLUT_LUMINANCE | GLUT_DOUBLE);
	glutCreateWindow("Game of Life");
	glutDisplayFunc(render);
	glutIdleFunc(idle);
	glutMouseFunc(mouse);
	glutKeyboardFunc(keyboard);
	gluOrtho2D(0.0, window_width, 0.0, window_height);
}

void render() {
	// Draw grid
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(0.3f, 0.3f, 0.3f);
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
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_QUADS);
	for (size_t y = 0; y < grid_height; ++y){
		for (size_t x = 0; x < grid_width; ++x) {
			if (!grid_wrapper.cell(x,y)) continue;
			glVertex2f(x * window_width / grid_width, y * window_height / grid_height);
			glVertex2f((x+1) * window_width / grid_width, y * window_height / grid_height);
			glVertex2f((x+1) * window_width / grid_width, (y+1) * window_height / grid_height);
			glVertex2f(x * window_width / grid_width, (y+1) * window_height / grid_height);
		}
	}
	glEnd();
	glutSwapBuffers();
}

void idle() {
	if (play) {
		grid_wrapper.turn();
		glutPostRedisplay();
	}
}

void mouse(int button, int state, int x, int y) {
	if (button==GLUT_LEFT_BUTTON && state==GLUT_DOWN) {
		grid_wrapper.cell((int)(x*grid_width)/window_width, grid_height-1 - (y*grid_height)/window_height).flip();
		glutPostRedisplay();
	}
}

void keyboard(unsigned char key, int x, int y) {
	if (key == ' ') {
		play = !play;
	}
}