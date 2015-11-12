#include <queue>
using namespace std;

static GLfloat center[] = { 2.0, 0.0, 0.0 };
static GLfloat O[] = {0.0, 0.0, 0.0};
static GLfloat W = 2.0;
static GLfloat vertices[8][3];
static GLfloat h = 0.5;
static GLfloat w = 0.5;
static GLfloat core_vertices[8][3] = {
		{ -1.0, -1.0, 1.0 },
		{ -1.0, -1.0, -1.0 },
		{ -1.0, 1.0, -1.0 },
		{ -1.0, 1.0, 1.0 },
		{ 1.0, -1.0, 1.0 },
		{ 1.0, -1.0, -1.0 },
		{ 1.0, 1.0, -1.0 },
		{ 1.0, 1.0, 1.0 }
};

/*
 * Enumeration of relative positions to the main cube
 */
static GLbyte pos[3][3][3] = {
	  {
	    { 0b010110, 0b010010, 0b010011 },
		{ 0b010100, 0b010000, 0b010001 },
		{ 0b011100, 0b011000, 0b011001 }
	  },

	  {
		{ 0b000110, 0b000010, 0b000011 },
		{ 0b000100, 0b000000, 0b000001 },
		{ 0b001100, 0b001000, 0b001001 }
	  },

	  { { 0b100110, 0b100010, 0b100011 },
		{ 0b100100, 0b100000, 0b100001 },
		{ 0b101100, 0b101000, 0b101001 }
	  }
};

/*
 * Initialize relative position of given point to the main cube
 */
GLbyte init_pos(const GLfloat* point, GLbyte &res){
	GLint i, j, k;
	GLfloat x = point[0];
	GLfloat y = point[1];
	GLfloat z = point[2];
	if ( x > W/2 + O[0] ){
		k = 2; // Right
	} else if ( x < -W/2 - O[0] ){
		k = 0; // Left
	} else
		k = 1; // Inside the box

	if ( y > W/2 + O[0] ){
			j = 0; // Top
		} else if ( y < -W/2 - O[0] ){
			j = 2; // Bottom
		} else
			j = 1; // Inside the box

	if ( z > W/2 + O[0] ){
			i = 0; // Front
		} else if ( z < -W/2 - O[0] ){
			i = 2; // Back
		} else
		i = 1; // Inside the box

	res = pos[i][j][k];
	return pos[i][j][k];
}

/*
 * Generate the absolute coordinates of all points
 */
void init_vertices(GLfloat w) {
	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 3; ++j)
			vertices[i][j] = w/2 * core_vertices[i][j] + center[j];
	}
}

/*
 * Compare 2 points and return their relative position
 * 0 : inside the main cube
 * 1 : cross
 * 2 : outside
 */
GLbyte compare2p(const GLfloat* v1, const GLfloat* v2 ){

	GLbyte b1, b2, res;
	init_pos(v1, b1);
	init_pos(v2, b2);

	if ( (b1 | b2) == 0 )
		res = 0;
	else if ( (b1 & b2) != 0 )
		res = 2;
	else
		res = 1;
	return res;
}

/*
 * Get the cross point of line ( head - tail ) with the plane ( r,l,u,o,f,a);
 */
void get_cross_point(GLfloat* res, GLfloat* head, GLfloat* tail, GLchar plane = 'r'){

	GLfloat dx = head[0] - tail[0];
	GLfloat dy = head[1] - tail[1];
	GLfloat dz = head[2] - tail[2];


	// The line crosses the RIGHT plane of the main cube
	if ( plane == 'r' ){
		res[0] = 1;
		if ( dx == 0 )
			return;
		res[1] = dy/dx*(res[0] - tail[0]) + tail[1];
		res[2] = dz/dx*(res[0] - tail[0]) + tail[2];
	}
	cout << "Crossing point: ";
	for ( int i = 0 ; i < 3 ; ++i)
			cout << res[i] << "   ";
	cout << endl;
}


/*
 * Move the dynamic shape into the main cube
 */
void move_shape() {
	center[0] += -0.01;
	center[1] += 0.0;
	center[2] += 0.0;
	glutPostRedisplay();
}

/*
 * Draw the main shape!!!
 */
void dynamic_display() {
	init_vertices(w);
	glPushMatrix();
	glColor3d(0.0, 0.0, 1.0 );
	glTranslatef(center[0], center[1], center[2]);
	glutWireCube(w);

	glPopMatrix();

	vector<GLfloat*> q;
	for (int i = 0; i < 4; ++i) {
		GLfloat crosspnt[4][3];
		if (compare2p(vertices[i], vertices[i + 4]) == 1) {
			get_cross_point(crosspnt[i], vertices[i], vertices[i + 4], 'r');
			q.push_back(crosspnt[i]);
		}
	}
	glBegin(GL_POLYGON);
		for ( int i = 0; i < q.size() ; ++i ){
			GLfloat* x = q[i];
			glVertex3f(x[0], x[1], x[2]);
			cout << "POLYGON: " << x[0] << " " << x[1] << " " << x[2] << endl;
		}
	glEnd();
}
