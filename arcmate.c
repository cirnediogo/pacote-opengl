#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

static int base = 0, juncao1 = 30, braco1 = 20, braco2 = 50;

void init(void) 
{
  glClearColor (0.0, 0.0, 0.0, 0.0);
  glShadeModel (GL_FLAT);
}

void display(void)
{
   glClear (GL_COLOR_BUFFER_BIT);
   
   glPushMatrix();
   
   
   
   glTranslatef (0.0, -2.0, 0.0);
   
//    glBegin(GL_LINES);
//    glVertex2f(-3.0,-0.3);
//    glVertex2f(3.0,-0.3);
//    glEnd();
   
   glPushMatrix();
   glScalef (0.6, 0.6, 0.6);
   glutWireCube (1.0);
   glPopMatrix();
   
   glTranslatef(0.0,0.5,0.0);
   glRotatef ((GLfloat) juncao1, 0.0, 1.0, 0.0);
   glPushMatrix();
   glTranslatef(0.0,0.0,-0.1);
   glScalef (0.4, 0.4, 0.2);
   glutWireCube (1.0);
   glPopMatrix();

   glRotatef ((GLfloat) braco1, 0.0, 0.0, 1.0);
   glTranslatef (0.0, 0.8, 0.0);
   glPushMatrix();
   glTranslatef(0.0,0.0,0.1);
   glScalef (0.4, 2.0, 0.2);
   glutWireCube (1.0);
   glPopMatrix();
   
   glTranslatef(0.0,0.8,0.0);
   glRotatef ((GLfloat) braco2, 0.0, 0.0, 1.0);
   glPushMatrix();
   glTranslatef(0.0,0.6,-0.1);
   glScalef (0.3, 1.6, 0.2);
   glutWireCube (1.0);
   glPopMatrix();
//    
//    
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

void mouse(int button, int state, int x, int y) 
{
   GLint viewport[4];
   GLdouble mvmatrix[16], projmatrix[16];
   GLint realy;  /*  OpenGL y coordinate position  */
   GLdouble wx, wy, wz;  /*  returned world x, y, z coords  */

   switch (button) {
      case GLUT_LEFT_BUTTON:
         if (state == GLUT_DOWN) {
            glGetIntegerv (GL_VIEWPORT, viewport);
            glGetDoublev (GL_MODELVIEW_MATRIX, mvmatrix);
            glGetDoublev (GL_PROJECTION_MATRIX, projmatrix);
/*  note viewport[3] is height of window in pixels  */
            realy = viewport[3] - (GLint) y - 1;
            printf ("Coordinates at cursor are (%d, %d)\n", x, realy);
//             gluUnProject ((GLdouble) x, (GLdouble) realy, 0.0, mvmatrix, projmatrix, viewport, &wx, &wy, &wz);
//             printf ("World coords at z=0.0 are (%f, %f, %f)\n", wx, wy, wz);
//             gluUnProject ((GLdouble) x, (GLdouble) realy, 1.0, mvmatrix, projmatrix, viewport, &wx, &wy, &wz);
//             printf ("World coords at z=1.0 are (%f, %f, %f)\n", wx, wy, wz);
         }
         break;
      case GLUT_RIGHT_BUTTON:
         if (state == GLUT_DOWN)
            exit(0);
         break;
      default:
         break;
   }
}

void keyboard (unsigned char key, int x, int y)
{
   switch (key) {
     case 27:
       exit(0);
       break;
      case 's':
         juncao1 = (juncao1 + 5) % 360;
         glutPostRedisplay();
         break;
      case 'S':
         juncao1 = (juncao1 - 5) % 360;
         glutPostRedisplay();
         break;
      case 'e':
	 if (braco1 < 100) {
	  braco1 = (braco1 + 5) % 360;
	  glutPostRedisplay();
	 }
         break; 
      case 'E':
         if (braco1 > -20) {
	  braco1 = (braco1 - 5) % 360;
	  glutPostRedisplay();
	 }
         break;
      case 'd':
         if (braco2 < 150) {
	  braco2 = (braco2 + 5) % 360;
	  glutPostRedisplay();
	 }
	 break;
      case 'D':
         if (braco2 > -20) {
	  braco2 = (braco2 - 5) % 360;
	  glutPostRedisplay();
	 }
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
   glutMouseFunc(mouse);
   glutMainLoop();
   return 0;
}