#include <GL/gl.h>
#include <GL/glut.h>

void display(void)
{
/*  clear all pixels  */
    glClear (GL_COLOR_BUFFER_BIT); //limpa a tela com a cor definida em glClearColor

/*  draw white polygon (rectangle) with corners at
 *  (0.25, 0.25, 0.0) and (0.75, 0.75, 0.0)
 */
    glColor4f (1.0, 1.0, 1.0, 0.0); //define a cor q sera usada para desenhar objetos a partir desse ponto
    glBegin(GL_POLYGON);
        glVertex3f (0.1, 0.1, 0.2);
        glVertex3f (0.1, 0.5, 0.6);
        glVertex3f (0.5, 0.5, 0.0);
        glVertex3f (0.5, 0.1, 0.0);
    glEnd();
    
    //glColor4f (0.0, 0.0, 1.0, 1.0);
    //glBegin(GL_POLYGON);
    //    glVertex3f (0.1, 0.1, 0.0);
    //    glVertex3f (0.2, 0.6, 0.0);
    //    glVertex3f (0.4, 0.8, 0.0);
    //    glVertex3f (0.5, 0.5, 0.0);
    //glEnd();
    
//    glRotatef(90.0, 0.0,1.0,0.0);
/*  don't wait!  
 *  start processing buffered OpenGL routines 
 */
    glFlush (); //força os comandos de desenho a executarem ao inves de ficarem no buffer
}

void init (void) 
{
/*  select clearing (background) color       */
    glClearColor (0.0, 0.0, 0.0, 0.0); //seta cor q ira limpar a tela quando glClear for chamado

/*  initialize viewing values  */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0); //define o sistema de coordenadas de referencia para desenhar objetos
}

/* 
 *  Declare initial window size, position, and display mode
 *  (single buffer and RGBA).  Open window with "hello"
 *  in its title bar.  Call initialization routines.
 *  Register callback function to display graphics.
 *  Enter main loop and process events.
 */
int main(int argc, char** argv)
{
    glutInit(&argc, argv); //inicia o GLUT
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB); //especifica opçoes
    glutInitWindowSize (250, 250); 
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("hello"); //cria a janela apenas quando chama glutMainLoop
    init ();
    glutDisplayFunc(display); //chama função com coteudo da tela, se conteudo for mudar, deve chamar  glutPostRedisplay
    glutMainLoop(); //executa tudo q foi definido
    return 0;   /* ISO C requires main to return int. */
}
