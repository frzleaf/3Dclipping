using namespace std;
//static GLfloat spin = 0.0;
//static GLfloat angle = -10.0;
static GLfloat center[] = { 2.0, 0.0, 0.0 };
static GLfloat vertices[8][3];
static GLfloat core_vertices[8][3] = { { -1.0, -1.0, 1.0 }, { 1.0, -1.0, 1.0 },
		{ 1.0, 1.0, 1.0 }, { -1.0, 1.0, 1.0 }, { -1.0, 1.0, -1.0 }, { 1.0, 1.0,
				-1.0 }, { 1.0, -1.0, -1.0 }, { -1.0, -1.0, -1.0 } };

static GLchar pos[3][9] = {
	  { 0b011100, 0b011000, 0b011001,
		0b010100, 0b010000, 0b010001,
		0b010110, 0b010010, 0b010011 },

	  { 0b001100, 0b001000, 0b001001,
		0b000100, 0b000000, 0b000001,
		0b000110, 0b000010, 0b000011 },

	  { 0b101100, 0b101000, 0b101001,
		0b100100, 0b100000, 0b100001,
		0b100110, 0b100010, 0b100011 }
};

static GLfloat h = 0.5;
static GLfloat w = 0.3;

void init_vertices(GLfloat );
void dynamic_display() {

	glPushMatrix();
	glTranslatef(center[0], center[1], center[2]);
	glColor3f(0.0, 1.0, 0.0);

	// Center
	glPointSize(3.0);
	glBegin(GL_POINTS);
	glVertex3f(0.0, 0.0, 0.0);
	glEnd();
	// Code goes here

	glutWireCube(w);
	init_vertices(w);

	glPopMatrix();

	glBegin(GL_POLYGON);
		for ( int i = 0 ; i < 4 ; ++i ){
			glVertex3f(vertices[i][0], vertices[i][1], vertices[i][2]);
		}
	glEnd();
}

void init_vertices(GLfloat w) {
	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 3; ++j)
			vertices[i][j] = w/2 * core_vertices[i][j] + center[j];
	}
}

void move_shape() {
	center[0] += -0.01;
	center[1] += -0.00;
	center[2] += 0.0;
	glutPostRedisplay();
}


void dynamic_() {
	glPushMatrix();
	glTranslatef(center[0], center[1], center[2]);
	glColor3f(1.0, 0.0, 0.0);
	glPopMatrix();
}
