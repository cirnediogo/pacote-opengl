#include <stdio.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

GLfloat ratio;
static GLfloat ang = 0;

void DefineLuz(void)
{
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

void Init(void) {
	glClearColor(1.0f, 1.0f, 0.0f, 1.0f);

	glShadeModel(GL_SMOOTH);
	glColorMaterial ( GL_FRONT, GL_AMBIENT_AND_DIFFUSE );

	glEnable(GL_DEPTH_TEST);
	glEnable ( GL_CULL_FACE );
	
}

void PosicUser() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(80,ratio,0.01,200);
	gluLookAt(0, 0, 5, 0,0,0, 0.0f,1.0f,0.0f);
}

void DesenhaCubo() {
	glutSolidCube(2.0);
}

void InicializaStencil() {
    // Habilita o uso do Stencil neste programa
	glEnable(GL_STENCIL_TEST);

	// Define que "0" ser� usado para limpar o Stencil 
	glClearStencil(0);
	// limpa o Stencil
	glClear(GL_STENCIL_BUFFER_BIT);

	// *****************************
	// Inicializa��o do Stencil
	// *****************************

	// Define que o valor 1 ser� "operado"
	// com o valor do stencil
	GLint Referencia = 1;
	GLuint NovoValor = 1;

	// Define o teste a ser feito entre o valor do 
	// stencil e o valor de "Referencia". 
	// Se o teste for verdadeiro ent�o NovoValor ser�
	// usado para operar sobre o valor corrente do Stencil
	//    GL_ALWAYS = o teste � sempre verdadeiro
	//    GL_EQUAL = o teste � verdadeiro se Referencia == Stencil 
	//    GL_LEQUAL = o teste � verdadeiro se  Referencia <=  Stencil
	//    GL_NOTQUAL = o teste � verdadeiro se  Referencia !=  Stencil
	glStencilFunc(GL_ALWAYS, Referencia, NovoValor); 
	
	// Define como o NovoValor � colocado no Stencil:
	//    GL_REPLACE = define que o valor atual
	//    do stencil ser� trocado pelo NovoValor
	//    GL_KEEP = define que o valor atual
	//    do stencil ser� mantido
	glStencilOp(GL_REPLACE,GL_REPLACE,GL_REPLACE);
	
	// Define uma �rea de desenha com coordenadas
	// l�gicas (0,0)->(10,10)

	// Ativa matriz de proje��o (necess�rio para usar a gluOrtho2D)
	glMatrixMode(GL_PROJECTION); 
	glLoadIdentity ();
	gluOrtho2D(0, 10, 0, 10); // define coordenadas l�gicas de desenho

	// Volta para a matrix de transforma��es geom�tricas
	glMatrixMode(GL_MODELVIEW); 

	// Desenha um ret�ngulo
	glRectf(0,4.5, 10,5.5);

}

void reshape( int w, int h ) {
	if(h == 0)
		h = 1;
	ratio = 1.0f * w / h;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
    glViewport(0, 0, w, h);
	InicializaStencil();
}

void DesenhaNoStencil() {

	static GLfloat DeltaX = -2;
	// *****************************
	// Libera o desenho na �rea em que o 
	// Stencil tem 1
	// *****************************

	// Se o conte�do do Stencil for == 1,
	// ent�o 
	//		- desenha na tela
	//		- opera o conte�do do stencil com o 1...
	//
	glStencilFunc(GL_EQUAL, 1, 1);   
	glStencilOp(GL_KEEP,GL_KEEP, GL_KEEP);

	glMatrixMode(GL_PROJECTION); 
	glLoadIdentity ();
	gluOrtho2D(0, 10, 0, 10);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity ();

	glDisable(GL_DEPTH_TEST); // Desabilita o ZBuffer
		
	glColor3f(1,0,0);
	glRectf(2.0f, 4.7f, 8.0f, 5.3f);

	glTranslatef(DeltaX,0,1);
	glColor3f(0,1,0);
	glRectf(4.5f, 4.5f, 5.5f, 5.5f);
	DeltaX +=0.01f;
	if (DeltaX > 2.5f)
		DeltaX = -2;
	printf("DeltaX : %6.3f\n", DeltaX);
	glEnable(GL_DEPTH_TEST); // habilita  o ZBuffer

}

void DesenhaForaDoStencil() {
	// *****************************
	// Libera o desenho no Stencil
	// na �rea em que o Stencil �
	// DIFERENTE de 1
	// *****************************

	// Se o conte�do do Stencil for <> de 1,
	// ent�o 
	//		- desenha na tela
	//		- opera o conte�do do stencil com o 1...
	//
	glStencilFunc(GL_NOTEQUAL, 1, 1);   
	// ... mantendo o stencil como ele estava
	glStencilOp(GL_KEEP,GL_KEEP, GL_KEEP);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity ();
	glPushMatrix();
		glTranslatef ( 1.0f, 0.0f, 0.0f );
		glRotatef(ang,0,1,0);
		glColor3f(0.5f,0.3f,0.0f);
		DesenhaCubo();		
	glPopMatrix();

	glLoadIdentity ();
	glPushMatrix();
		glTranslatef ( -1.0f, 0.0f, -5.0f );
		glRotatef(45,0,1,0);
		glColor3f(0.5f,0.3f,0.0f);
		DesenhaCubo();		
	glPopMatrix();

	ang = ang + 2;

}

void display( void ) {
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	DefineLuz();
	PosicUser();
	DesenhaForaDoStencil();
	DesenhaNoStencil();
	glutSwapBuffers();
}

void keyboard ( unsigned char key, int x, int y ) {
	switch ( key ) 
	{
    case 27:        // Termina o programa qdo
      exit ( 0 );   // a tecla ESC for pressionada
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
	glutCreateWindow    ( "T�picos em Computa��o Gr�fica - Teste com STENCIL Buffer." ); 
		
	Init ();

	glutDisplayFunc ( display );  
	glutReshapeFunc ( reshape );
	glutKeyboardFunc ( keyboard );
	glutIdleFunc ( display );

	glutMainLoop ( );          
}





