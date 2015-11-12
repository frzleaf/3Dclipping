#include <iostream>
#include <GL/glut.h>
#include <stdlib.h>

#include "algorithm.h"
#include "static_display.h"

using namespace std;

static GLfloat COLOR_WHITE[] = { 1.0, 1.0, 1.0, 1.0 };
static bool motion = 0;

void main_display() {
	static_display();
	dynamic_display();
	glFlush();
	glutSwapBuffers();
}

void init() {
	glClearColor(COLOR_WHITE[0], COLOR_WHITE[1], COLOR_WHITE[2],
			COLOR_WHITE[3]);
	glShadeModel(GL_FLAT);
}

void reshape(int w, int h) {
	glViewport(0, 0, (GLsizei) w, (GLsizei) h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-2.0, 2.0, -1.0, 2.0, 4.0, 10.0);
	glMatrixMode(GL_MODELVIEW);
}

void mouse(int button, int state, int x, int y) {
	switch (button) {
	case GLUT_LEFT_BUTTON:
		if (state == GLUT_DOWN){
			if ( !motion )
				glutIdleFunc(move_shape);
			else
				glutIdleFunc(NULL);
			motion = !motion;
		}
		break;
	case GLUT_RIGHT_BUTTON:
	default:
		break;
	}
}

int main(int argc, char ** argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(300, 100);
	glutCreateWindow("Motion Example");
	init();
	glutDisplayFunc(main_display);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);
	glutMainLoop();

	return 0;
}
