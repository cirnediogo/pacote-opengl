#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdio.h>

#define MAX(A, B) (A > B ? A : B)
#define MIN(A, B) (A < B ? A : B)

float camX, camY, camZ;

void init(void) 
{
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    GLfloat light_position[] = { 5.0, 5.0, 5.0, 1.0 };
    GLfloat light_direction[] = { -1, -1, -1};
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, light_direction);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightf ( GL_LIGHT0, GL_SPOT_EXPONENT , 1.0);
    glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 15.f); 

    glClearColor (0.0, 0.0, 0.0, 0.0);
    glShadeModel (GL_SMOOTH);

    glEnable(GL_DEPTH_TEST);

    camX = 5;
    camY = 5;
    camZ = 5;
}

void display(void)
{
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-1, 1, -1, 1, 1.5, 1000);
    gluLookAt(camX, camY, camZ, 1.0, 0, 0.0, 0.0, 1.0, 0.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glEnable(GL_NORMALIZE);

	float f = 0.1;
	int r = 10;
	float i, j;
    for(i = -r; i < r; i += f)
		for(j = -r; j < r; j += f) {
			glBegin(GL_QUADS);
			glNormal3f(0, 1, 0); glVertex3f(i, 0, j);
			glNormal3f(0, 1, 0); glVertex3f(i+f, 0, j);
			glNormal3f(0, 1, 0); glVertex3f(i+f, 0, j+f);
			glNormal3f(0, 1, 0); glVertex3f(i, 0, j+f);
			glEnd();
		}

    glutSolidSphere (1.0, 40, 46);


//gcc spotlight.c -o spotlight -lX11 -lXi -lXmu -lglut -lGL -lGLU -lm 
    glTranslatef(2, 0, 0);
    glutSolidCube(1.0);
    glTranslatef(0, 0, 2);
    glutSolidCube(1.0);
    glTranslatef(0, 0, 2);
    glutSolidCube(3.0);

    glFlush ();
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
	if(key == 'r')		camY -= step;
	if(key == 'f')		camY += step;
	glutPostRedisplay();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize (500, 500); 
    glutInitWindowPosition (100, 100);
    glutCreateWindow (argv[0]);
    init ();
    glutDisplayFunc(display); 
    glutReshapeFunc(reshape);
    glutKeyboardFunc(teclado);
    glutMainLoop();
    return 0;
}


