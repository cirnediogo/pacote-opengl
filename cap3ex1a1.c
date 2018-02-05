#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

float camx, camy, camz;
float rot;

void init(void) 
{
    glClearColor (0.0, 0.0, 0.0, 0.0);
    glShadeModel (GL_FLAT);
    camx = 0;
    camy = 0;
    camz = 5;
    rot = 0;
}

void display(void)
{
    glClear (GL_COLOR_BUFFER_BIT);
    glColor3f (1.0, 1.0, 1.0);
    glLoadIdentity ();             /* clear the matrix */
    /* viewing transformation  */
    gluLookAt (camx, camy, camz, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    glScalef (1.0, 2.0, 1.0);      /* modeling transformation */ 
    glPushMatrix();
    glRotatef(rot, 1, 0, 0);
    glutWireCube (1.0);
    glPopMatrix();
    glTranslatef(3, 0, 0);
    glutWireCube(1.0);
    glFlush ();
}

void reshape (int w, int h)
{
    glViewport (0, 0, (GLsizei) w, (GLsizei) h); 
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    glFrustum (-1.0, 1.0, -1.0, 1.0, 1.5, 20.0);
    glMatrixMode (GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y) {
    switch(key) {
	case 'q':
	    camx--;
	    break;
	case 'w':
	    camx++;
	    break;
	case 'a':
	    camy++;
	    break;
	case 's':
	    camy--;
	    break;
	case 'z':
	    camz++;
	    break;
	case 'x':
	    camz--;
	    break;
	case 'f':
	    rot--;
	    break;
	case 'h':
	    rot++;
	    break;
    }
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
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}