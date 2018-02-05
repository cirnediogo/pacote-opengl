#include <stdio.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

GLfloat ratio;
static GLfloat ang = 0;

void DefineLuz(void) {
    GLfloat LuzAmbiente[]   = {0.24725f, 0.1995f, 0.07f } ;
    GLfloat LuzDifusa[]   = {0.75164f, 0.60648f, 0.22648f, 1.0f };
    GLfloat LuzEspecular[] = {0.626281f, 0.555802f, 0.366065f, 1.0f };
    GLfloat PosicaoLuz0[]  = {3.0f, 3.0f, 0.0f, 1.0f };
    GLfloat PosicaoLuz1[]  = {-3.0f, -3.0f, 0.0f, 1.0f };
    GLfloat Especularidade[] = {1.0f, 1.0f, 1.0f, 1.0f };
    glEnable ( GL_COLOR_MATERIAL );
    glEnable(GL_LIGHTING);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, LuzAmbiente);
    glLightfv(GL_LIGHT0, GL_AMBIENT, LuzAmbiente);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, LuzDifusa  );
    glLightfv(GL_LIGHT0, GL_SPECULAR, LuzEspecular  );
    glLightfv(GL_LIGHT0, GL_POSITION, PosicaoLuz0 );
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glMaterialfv(GL_FRONT,GL_SPECULAR, Especularidade);
    glMateriali(GL_FRONT,GL_SHININESS,51.2);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, LuzAmbiente);
    glLightfv(GL_LIGHT1, GL_AMBIENT, LuzAmbiente);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, LuzDifusa  );
    glLightfv(GL_LIGHT1, GL_SPECULAR, LuzEspecular  );
    glLightfv(GL_LIGHT1, GL_POSITION, PosicaoLuz1 );
    glEnable(GL_LIGHT1);
    glEnable(GL_COLOR_MATERIAL);
    glMaterialfv(GL_FRONT,GL_SPECULAR, Especularidade);
    glMateriali(GL_FRONT,GL_SHININESS,20);
}

void InicializaStencil() {
    glEnable(GL_STENCIL_TEST);
    glClearStencil(0);
    glClear(GL_STENCIL_BUFFER_BIT);
}

void Init(void) {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Fundo de tela preto
    glShadeModel(GL_SMOOTH); 
    glColorMaterial ( GL_FRONT, GL_AMBIENT_AND_DIFFUSE );
    glEnable(GL_DEPTH_TEST);
    glEnable ( GL_CULL_FACE );
    InicializaStencil();
}

void reshape( int w, int h ) {
    if(h == 0)	h = 1;
    ratio = 1.0f * w / h;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, w, h);
    InicializaStencil();
}

void desenharCena() {
    glMatrixMode(GL_MODELVIEW); 
    glLoadIdentity();
    glRotatef(ang, 0, 1, 0);
    float sizes[] = {3.1, 2.7, 2.3, 1.3, 0.7, 0.2};
int i;
    for(i = 0; i < 4; i++) {
        glutSolidCube(sizes[i]);
	glTranslatef(sizes[i], 0, 0);
    }
}

void visao1() {
    glStencilFunc(GL_EQUAL, 1, 1);   
    glStencilOp(GL_KEEP,GL_KEEP, GL_KEEP);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(80,ratio,0.01,200);
    gluLookAt(0, 19, -4, 0, 0, 0, 0.0f, 1.0f, 0.0f);

    desenharCena();
}

void visao2() {
    glStencilFunc(GL_EQUAL, 1, 1);   
    glStencilOp(GL_KEEP,GL_KEEP, GL_KEEP);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(80,ratio,0.01,200);
    gluLookAt(-4, 5, 5, 0, 0, 0, 0.0f, 1.0f, 0.0f);

    desenharCena();
}

void desenhaMascara1() {
    glClearStencil(0);
    glClear(GL_STENCIL_BUFFER_BIT);

    glStencilFunc(GL_ALWAYS, 1, 1);   
    glStencilOp(GL_REPLACE, GL_REPLACE, GL_REPLACE);

    glMatrixMode(GL_PROJECTION); 
    glLoadIdentity ();

    gluOrtho2D(0, 10, 0, 10); 

    glDisable(GL_DEPTH_TEST); // Desabilita o ZBuffer
    glDisable(GL_LIGHTING);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glColorMask(GL_TRUE, GL_FALSE, GL_FALSE, GL_FALSE);
    glRectf(1, 1, 5, 8);
    glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST); // habilita  o ZBuffer
}

void desenhaMascara2() {
    glClearStencil(0);
    glClear(GL_STENCIL_BUFFER_BIT);

    glStencilFunc(GL_ALWAYS, 1, 1);   
    glStencilOp(GL_REPLACE,GL_REPLACE, GL_REPLACE);

    glMatrixMode(GL_PROJECTION); 
    glLoadIdentity ();

    gluOrtho2D(0, 10, 0, 10); 

    glDisable(GL_DEPTH_TEST); // Desabilita o ZBuffer
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glColorMask(GL_TRUE, GL_FALSE, GL_FALSE, GL_FALSE);
    glRectf(5.3, 1, 9.7, 8);
    glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
    glEnable(GL_DEPTH_TEST); // habilita  o ZBuffer
}

void display( void )
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    ang += 0.09;
    DefineLuz();
    desenhaMascara1();
    visao1();
    desenhaMascara2();
    visao2();
    glutSwapBuffers();
}

void keyboard ( unsigned char key, int x, int y )  
{
    switch ( key )  {
	case 27:
	    exit(0);
	    break;        
	default:        
	    break;
    }
}


int main ( int argc, char** argv )   
{
    glutInit            ( &argc, argv ); 
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_STENCIL); 
    glutInitWindowPosition (0,0);
    glutInitWindowSize  ( 500, 500 ); 
    glutCreateWindow    ( "Stencil buffer" ); 

    Init ();

    glutDisplayFunc ( display );  
    glutReshapeFunc ( reshape );
    glutKeyboardFunc ( keyboard );
    glutIdleFunc ( display );

    glutMainLoop ( );          
}





