#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

int rx = 90, ry = 1, rz = 0;

void init(void) 
{
   glClearColor (0.0, 0.0, 0.0, 0.0);
   glShadeModel (GL_FLAT);
}

void display(void)
{
   GLdouble eqn[4] = {0.0, 1.0, 0.0, 0.0};
   GLdouble eqn2[4] = {1.0, 0.0, 0.0, 0.0};

   glClear(GL_COLOR_BUFFER_BIT);
   glColor3f (1.0, 1.0, 1.0);
   glPushMatrix();
   glTranslatef (0.0, 0.0, -2.0);

/*    clip lower half -- y < 0          */
   glClipPlane (GL_CLIP_PLANE0, eqn);
   glEnable (GL_CLIP_PLANE0);
/*    clip left half -- x < 0           */
   glClipPlane (GL_CLIP_PLANE1, eqn2);
     glEnable (GL_CLIP_PLANE1);
  
   glRotatef ((GLfloat) rx,(GLfloat) ry,(GLfloat) rz, 0.0);
    
   glutWireSphere(1.0, 20, 16);
//    glutWireCube(1.0);
   glPopMatrix();
   glFlush ();
}

void reshape (int w, int h)
{
   glViewport (0, 0, (GLsizei) w, (GLsizei) h); 
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   gluPerspective(60.0, (GLfloat) w/(GLfloat) h, 1.0, 20.0);
   glMatrixMode (GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y) {
    switch(key) {
      case 'q':
	rx = (rx+1)%360;
	break;
      case 'w':
	rx = (rx-1)%360;
	break;
      case 'a':
	ry = (ry+1)%360;
	break;
      case 's':
	ry = (ry-1)%360;
	break;
      case 'z':
	rz = (rz+1)%360;
	break;
      case 'x':
	rz = (rz-1)%360;
	break;
      default:
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