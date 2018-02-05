#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdio.h>
#include <vector>
#include <stdlib.h>
#include <time.h>

using namespace std;

#define MAX(A, B) (A > B ? A : B)
#define MIN(A, B) (A < B ? A : B)

float camX, camY, camZ;

int level = 5;
float xf = 3;
float yf = 8;

void init(void) 
{
    glEnable(GL_LIGHT0);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	glEnable(GL_LINE_SMOOTH);

    GLfloat light_position[] = { 5.0, 5.0, 5.0, 1.0 };
    GLfloat light_direction[] = { -1, -1, -1};
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glClearColor (0.0, 0.0, 0.0, 0.0);
    glShadeModel (GL_SMOOTH);

    glEnable(GL_DEPTH_TEST);

    camX = 10;
    camY = 5;
    camZ = 5;
	srand((unsigned)time(NULL));
}

/*
   * numeracao na quadtree
   * 0 | 1
   * -----
   * 3 | 2
   */
int getCell(float x, float y, float ox, float oy, float sx, float sy, int level) {
	int cell = 0;
	for(int i = 0; i < level; i++) {
		if(x < ox+sx/2 && y < oy+sy/2) cell = 0;
		else if(x < ox+sx/2) cell = 2;
		else if(y < oy+sy/2) cell = 1;
		else cell = 3;
		if(cell == 0);
		if(cell == 1) {ox += sx/2;}
		if(cell == 2) {oy += sy/2;}
		if(cell == 3) {ox += sx/2; oy += sy/2;}
		sx /= 2;
		sy /= 2;
	}
	return cell;
}

void display(void)
{
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-1, 1, -1, 1, 1.5, 1000);
    gluLookAt(camX, camY, camZ, 5, 0, 5, 0.0, 1.0, 0.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glEnable(GL_NORMALIZE);

	float f = 1;
	int r = 10;

	float s = 10.0/(1<<level);
	float yl = 0.1;
	//origem: (0,0)
	//tamanho do grid: (10,10)

	int x, y;
	x = y = 0;
	for(int i = 0; i <= level; i++) {
		x *= 2;
		y *= 2;
		int c = getCell(xf, yf, 0, 0, 10, 10, i);
		if(c == 1 || c == 3)
			x += 1;
		if(c == 2 || c == 3)
			y += 1;
	}

	glPushMatrix();
	glTranslatef(xf, 0.1, yf);
	glColor3f(0.0, 0.4, 0.4);
	glutSolidCube(0.1);
	glPopMatrix();
	for(int i = 0; i < (1<<level); i++) {
		for(int j = 0; j < (1<<level); j++) {
			glColor3f(0.0, 0.0, 0.4);
			glBegin(GL_LINE_LOOP);
			glVertex3f(i*s, yl, j*s);
			glVertex3f(i*s + s, yl, j*s);
			glVertex3f(i*s + s, yl, j*s + s);
			glVertex3f(i*s, yl, j*s + s);
			glEnd();
			if(x == i && y == j)
				glColor3f(1.0, 0, 0);
			else
				glColor3f(1.0, 1.0, 1.0);
			glBegin(GL_QUADS);
			glNormal3f(0, 1, 0);
			glVertex3f(i*s, yl, j*s);
			glNormal3f(0, 1, 0);
			glVertex3f(i*s + s, yl, j*s);
			glNormal3f(0, 1, 0);
			glVertex3f(i*s + s, yl, j*s + s);
			glNormal3f(0, 1, 0);
			glVertex3f(i*s, yl, j*s + s);
			glEnd();
		}
	}

    glFlush ();
	glutSwapBuffers();
}

void reshape (int w, int h)
{
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity();
    if (w <= h)
	glOrtho (-1.5, 1.5, -1.5*(GLfloat)h/(GLfloat)w,
		1.5*(GLfloat)h/(GLfloat)w, -10.0, 10.0);
    else
	glOrtho (-1.5*(GLfloat)w/(GLfloat)h,
		1.5*(GLfloat)w/(GLfloat)h, -1.5, 1.5, -10.0, 10.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void teclado(unsigned char key, int x, int y) {
	if(key == 'q')
		exit(0);
	float step = 0.5;
	if(key == 'w')		camZ -= step;
	if(key == 's')		camZ += step;
	if(key == 'd')		camX += step;
	if(key == 'a')		camX -= step;
	if(key == 'r')		level--;
	if(key == 't')		level++;
	if(key == 'f')		xf += 0.1;
	if(key == 'g')		xf -= 0.1;
	if(key == 'v')		yf += 0.1;
	if(key == 'b')		yf -= 0.1;
	glutPostRedisplay();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize (500, 500); 
    glutInitWindowPosition (100, 100);
    glutCreateWindow (argv[0]);
    init ();
	display();
    glutDisplayFunc(display); 
    glutReshapeFunc(reshape);
    glutKeyboardFunc(teclado);
    glutMainLoop();
    return 0;
}

