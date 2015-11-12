

#define PI 3.1415926535898





static GLfloat standPoint[] = {0.0, 0.0, 5.0}; // Look from here

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
	glColor3f(0.0, 0.0, 0.0);
	glLoadIdentity();
	/* clear the matrix */
	/* viewing transformation */
	gluLookAt(
			standPoint[0], standPoint[1], standPoint[2],
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


	glColor3f( 0.0, 0.0, 0.0 );
	glPointSize(3.0);
	glBegin(GL_POINTS);
		glVertex3f(0.0, 0.0, 0.0 );
	glEnd();

//	draw_axis();
}

static bool motion = 0;
static bool motion_scene = 0;


/*
 * Set the stand point follow the mouse's coordinate
 */
void mouse_motion(int x, int y){
	if ( !motion_scene )
		return;
	cout << "Mouse coordinate: " << x << "/" << y << endl;

	// With the view port 5x5
	standPoint[0] = (GLfloat) x / glutGet(GLUT_WINDOW_WIDTH) * 5;
	standPoint[1] = (GLfloat) y / glutGet(GLUT_WINDOW_HEIGHT) * 5;
	glutPostRedisplay();
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
		motion_scene = ( state == GLUT_DOWN );
		cout << "Right click: (x/y) = " << x <<"/" << y << endl;
		cout << "W/H: " << glutGet(GLUT_WINDOW_WIDTH) << "/" <<  glutGet(GLUT_WINDOW_HEIGHT) << endl;
		break;
	default:
		break;
	}
}
