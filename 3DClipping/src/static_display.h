

#define PI 3.1415926535898
void draw_axis(){
	// draw our axes
	glBegin(GL_LINES);
	// draw line for x axis
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(-99.0, 0.0, 0.0);
	glVertex3f(99.0, 0.0, 0.0);
	// draw line for y axis
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(0.0, -99.0, 0.0);
	glVertex3f(0.0, 99.0, 0.0);
	// draw line for Z axis
	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(0.0, 0.0, -99.0);
	glVertex3f(0.0, 0.0, 99.0);
	glEnd();
	// load the previous matrix
	glPopMatrix();
}


void static_display(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 0.0);
	glLoadIdentity();
	/* clear the matrix */
	/* viewing transformation */
	gluLookAt(
			3.0, 4.0, 5.0,
			0.0, 0.0, 0.0,
			0.0, 1.0, 0.0
			);
//	glScalef(1.0, 1.0, 1.0);
	/* modeling transformation */
//	glRotatef(90.0, 1.0, 0.0, 0.0);
	GLfloat vertices[] = {
			-1.0, -1.0, -1.0,
			 1.0, -1.0,	-1.0,
			 1.0,  1.0,	-1.0,
			-1.0,  1.0, -1.0,

			-1.0, -1.0, 1.0,
			 1.0, -1.0,	1.0,
			 1.0,  1.0,	1.0,
			-1.0,  1.0, 1.0,
	};

	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, vertices);

	glutWireCube(2.0);
//	glBegin(GL_LINE_STRIP);
//		for ( int i = 0; i < 8; ++i ){
//			glArrayElement(i);
//		}
//	glEnd();


	glColor3f( 1.0, 1.0, 1.0 );
	glPointSize(2.0);
	glBegin(GL_POINTS);
		glVertex3f(0.0, 0.0, 0.0 );
	glEnd();

//	draw_axis();

}
