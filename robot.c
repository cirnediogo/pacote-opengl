#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

static int shoulder = 0, elbow = 0, finger11 = 0, finger12 = 0, finger21 = 0, finger22 = 0, finger31 = 0, finger32 = 0, finger41 = 0, finger42 = 0;

void init(void) 
{
  glClearColor (0.0, 0.0, 0.0, 0.0);
  glShadeModel (GL_FLAT);
}

void display(void)
{
   glClear (GL_COLOR_BUFFER_BIT);
   glPushMatrix();
   glTranslatef (-1.0, 0.0, 0.0);
   glRotatef ((GLfloat) shoulder, 0.0, 0.0, 1.0);
   glTranslatef (1.0, 0.0, 0.0);
   glPushMatrix();
   glScalef (2.0, 0.4, 1.0);
   glutWireCube (1.0);
   glPopMatrix();

   glTranslatef (1.0, 0.0, 0.0);
   glRotatef ((GLfloat) elbow, 0.0, 0.0, 1.0);
   glTranslatef (1.0, 0.0, 0.0);
   glPushMatrix();
   glScalef (2.0, 0.4, 1.0);
   glutWireCube (1.0);
   glPopMatrix();
   
   glTranslatef (1.0, 0.0, 0.0);
   
   glPushMatrix();
   
   glTranslatef(0.0,0.2,0.0);
   
   glPushMatrix();
   
   glRotatef ((GLfloat) finger21, 0.0, 0.0, 1.0);
   glTranslatef (0.25, -0.05, 0.0);
   glPushMatrix();
   glScalef (0.5, 0.1, 0.25);
   glutWireCube (1.0);
   glPopMatrix();
   
   glTranslatef (0.25, -0.05, 0.0);
   
   glPushMatrix();
   
   glRotatef ((GLfloat) finger22, 0.0, 0.0, 1.0);
   glTranslatef (0.25, 0.05, 0.0);
   glPushMatrix();
   glScalef (0.5, 0.1, 0.25);
   glutWireCube (1.0);
   glPopMatrix();
   
   glPopMatrix();
   glPopMatrix();
   
   glTranslatef (0.0, 0.0, 0.5);
   
   glPushMatrix();
   
   glRotatef ((GLfloat) finger11, 0.0, 0.0, 1.0);
   glTranslatef (0.25, -0.05, 0.0);
   glPushMatrix();
   glScalef (0.5, 0.1, 0.25);
   glutWireCube (1.0);
   glPopMatrix();
   
   glTranslatef (0.25, -0.05, 0.0);
   
   glPushMatrix();
   
   glRotatef ((GLfloat) finger12, 0.0, 0.0, 1.0);
   glTranslatef (0.25, 0.05, 0.0);
   glPushMatrix();
   glScalef (0.5, 0.1, 0.25);
   glutWireCube (1.0);
   glPopMatrix();

   glPopMatrix();
   glPopMatrix();

   glTranslatef (0.0, 0.0, -1.0);
   
   glPushMatrix();
   
   glRotatef ((GLfloat) finger31, 0.0, 0.0, 1.0);
   glTranslatef (0.25, -0.05, 0.0);
   glPushMatrix();
   glScalef (0.5, 0.1, 0.25);
   glutWireCube (1.0);
   glPopMatrix();
   
   glTranslatef (0.25, -0.05, 0.0);
   
   glPushMatrix();
   
   glRotatef ((GLfloat) finger32, 0.0, 0.0, 1.0);
   glTranslatef (0.25, 0.05, 0.0);
   glPushMatrix();
   glScalef (0.5, 0.1, 0.25);
   glutWireCube (1.0);
   glPopMatrix();

   glPopMatrix();
   glPopMatrix();
   
   glPopMatrix();
   
   glTranslatef(0.0,-0.2,0.5);
   
   glPushMatrix();
   
   glRotatef ((GLfloat) finger41, 0.0, 0.0, 1.0);
   glTranslatef (0.25, 0.05, 0.0);
   glPushMatrix();
   glScalef (0.5, 0.1, 0.25);
   glutWireCube (1.0);
   glPopMatrix();
   
   glTranslatef (0.25, 0.05, 0.0);
   
   glPushMatrix();
   
   glRotatef ((GLfloat) finger42, 0.0, 0.0, 1.0);
   glTranslatef (0.25, -0.05, 0.0);
   glPushMatrix();
   glScalef (0.5, 0.1, 0.25);
   glutWireCube (1.0);
   glPopMatrix();

   glPopMatrix();
   glPopMatrix();
   
   glPopMatrix();
   glutSwapBuffers();
}

void reshape (int w, int h)
{
   glViewport (0, 0, (GLsizei) w, (GLsizei) h); 
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   gluPerspective(65.0, (GLfloat) w/(GLfloat) h, 1.0, 20.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   glTranslatef (0.0, 0.0, -5.0);
}

void keyboard (unsigned char key, int x, int y)
{
   switch (key) {
      case 's':   /*  s key rotates at shoulder  */
         shoulder = (shoulder + 5) % 360;
         glutPostRedisplay();
         break;
      case 'S':
         shoulder = (shoulder - 5) % 360;
         glutPostRedisplay();
         break;
      case 'e':  /*  e key rotates at elbow  */
         elbow = (elbow + 5) % 360;
         glutPostRedisplay();
         break; 
      case 'E':
         elbow = (elbow - 5) % 360;
         glutPostRedisplay();
         break;
      case 'd':   /*  s key rotates at shoulder  */
         finger11 = (finger11 + 5) % 360;
         glutPostRedisplay();
         break;
      case 'D':
         finger11 = (finger11 - 5) % 360;
         glutPostRedisplay();
         break;
      case 'r':   /*  s key rotates at shoulder  */
         finger12 = (finger12 + 5) % 360;
         glutPostRedisplay();
         break;
      case 'R':
         finger12 = (finger12 - 5) % 360;
         glutPostRedisplay();
         break;
      case 'f':   /*  s key rotates at shoulder  */
         finger21 = (finger21 + 5) % 360;
         glutPostRedisplay();
         break;
      case 'F':
         finger21 = (finger21 - 5) % 360;
         glutPostRedisplay();
         break;
      case 't':   /*  s key rotates at shoulder  */
         finger22 = (finger22 + 5) % 360;
         glutPostRedisplay();
         break;
      case 'T':
         finger22 = (finger22 - 5) % 360;
         glutPostRedisplay();
         break;
      case 'g':   /*  s key rotates at shoulder  */
         finger31 = (finger31 + 5) % 360;
         glutPostRedisplay();
         break;
      case 'G':
         finger31 = (finger31 - 5) % 360;
         glutPostRedisplay();
         break;
      case 'y':   /*  s key rotates at shoulder  */
         finger32 = (finger32 + 5) % 360;
         glutPostRedisplay();
         break;
      case 'Y':
         finger32 = (finger32 - 5) % 360;
         glutPostRedisplay();
         break;
      case 'h':   /*  s key rotates at shoulder  */
         finger41 = (finger41 + 5) % 360;
         glutPostRedisplay();
         break;
      case 'H':
         finger41 = (finger41 - 5) % 360;
         glutPostRedisplay();
         break;
      case 'u':   /*  s key rotates at shoulder  */
         finger42 = (finger42 + 5) % 360;
         glutPostRedisplay();
         break;
      case 'U':
         finger42 = (finger42 - 5) % 360;
         glutPostRedisplay();
         break;
      default:
         break;
   }
}

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
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
