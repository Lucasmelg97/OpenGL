/*
 LUCAS SANTIAGO VIEIRA MELGAÇO - TRABALHO PRÁTICO DE PDI
 */
#include <iostream>
#include <glut.h>
#include <stdio.h>
#include <stdlib.h>
#ifdef _WIN32
#	include <windows.h>
#else
#	include <sys/time.h>
#endif

#define VIEWING_DISTANCE_MIN  3.0
#define TEXTURE_ID_CUBE 1

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>

GLfloat ratio;

GLfloat roll =0, pitch=0,yaw=0, rotacaox=0, rotacaoy=0;


#define AMBIENTE 0
#define DIFUSA 1
#define ESPECULAR 2

using namespace std;
static int slices = 16;
static int stacks = 16;
static double size_element = 0.5;
double rotate_y=0;
double rotate_x=0;
int ModoDeIluminacao = AMBIENTE;

int LuzAmbEhMax = 0;
// **********************************************************************
//  void DefineLuz(void)
//
//
// **********************************************************************
void DefineLuzESPECULAR(void)
{
    // Define cores para um objeto dourado
    GLfloat LuzAmbiente[]   = {0.24725f, 0.1995f, 0.07f } ;
    GLfloat LuzAmbienteMAX[]   = {1,1,1 } ;

    GLfloat LuzDifusa[]   = {0.75164f, 0.60648f, 0.22648f, 1.0f };
    GLfloat LuzEspecular[] = {0.626281f, 0.555802f, 0.366065f, 1.0f };
    //GLfloat LuzEspecular[] = {1,0,0, 1.0f };
    GLfloat PosicaoLuz0[]  = {3.0f, 3.0f, 0.0f, 1.0f };
    GLfloat PosicaoLuz1[]  = {-3.0f, -3.0f, 0.0f, 1.0f };
    GLfloat Especularidade[] = {1.0f, 1.0f, 1.0f, 1.0f };

    // ****************  Fonte de Luz 0

    glEnable ( GL_COLOR_MATERIAL );


    // Habilita o uso de iluminação
    glEnable(GL_LIGHTING);

    // Ativa o uso da luz ambiente
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, LuzAmbiente);
    // Define os parametros da Luz número Zero
    if (LuzAmbEhMax)
        glLightfv(GL_LIGHT0, GL_AMBIENT, LuzAmbienteMAX);
    else
        glLightfv(GL_LIGHT0, GL_AMBIENT, LuzAmbiente);

    glLightfv(GL_LIGHT0, GL_DIFFUSE, LuzDifusa);
    glLightfv(GL_LIGHT0, GL_SPECULAR, LuzEspecular);
    glLightfv(GL_LIGHT0, GL_POSITION, PosicaoLuz0);
    glEnable(GL_LIGHT0);

    // Ativa o "Color Tracking"
    glEnable(GL_COLOR_MATERIAL);

    // Define a reflectancia do material
    glMaterialfv(GL_FRONT,GL_SPECULAR, Especularidade);

    // Define a concentração do brilho.
    // Quanto maior o valor do Segundo parametro, mais
    // concentrado será o brilho. (Valores válidos: de 0 a 128)
    glMateriali(GL_FRONT,GL_SHININESS,112);

    // ****************  Fonte de Luz 1

    // Ativa o uso da luz ambiente
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, LuzAmbiente);
    // Define os parametros da Luz número Zero
    if (LuzAmbEhMax)
        glLightfv(GL_LIGHT1, GL_AMBIENT, LuzAmbienteMAX);
    else
        glLightfv(GL_LIGHT1, GL_AMBIENT, LuzAmbiente);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, LuzDifusa  );
    glLightfv(GL_LIGHT1, GL_SPECULAR, LuzEspecular  );
    glLightfv(GL_LIGHT1, GL_POSITION, PosicaoLuz1 );
    glEnable(GL_LIGHT1);

    // Ativa o "Color Tracking"
    glEnable(GL_COLOR_MATERIAL);

    // Define a reflectancia do material
    glMaterialfv(GL_FRONT,GL_SPECULAR, Especularidade);

    // Define a concentração do brilho.
    // Quanto maior o valor do Segundo parametro, mais
    // concentrado será o brilho. (Valores válidos: de 0 a 128)
    glMateriali(GL_FRONT,GL_SHININESS,11);
//  glMateriali(GL_FRONT,GL_SHININESS,20);

}
// **********************************************************************
//  void DefineLuz(void)
//
//
// **********************************************************************
void DefineLuzAMBIENTE(void)
{
    glDisable(GL_LIGHTING);
    return;
}

// **********************************************************************
//  void DefineLuz(void)
//
//
// **********************************************************************
void DefineLuzDIFUSA(void)
{
    // Define cores para um objeto dourado
    GLfloat LuzAmbiente[]   = {0.24725f, 0.1995f, 0.07f } ;
    //GLfloat LuzAmbiente[]   = {0,0,0} ;
    GLfloat LuzAmbienteMAX[]   = {1,1,1 } ;
    GLfloat LuzDifusa[]   = {0.75164f, 0.60648f, 0.22648f, 1.0f };
    GLfloat LuzEspecular[] = {0,0,0, 1.0f };
    GLfloat PosicaoLuz0[]  = {3.0f, 3.0f, 0.0f, 1.0f };
    GLfloat PosicaoLuz1[]  = {-3.0f, -3.0f, 0.0f, 1.0f };
    GLfloat Especularidade[] = {0,0,0,1 };

    // ****************  Fonte de Luz 0

    glEnable ( GL_COLOR_MATERIAL );


    // Habilita o uso de iluminação
    glEnable(GL_LIGHTING);

    // Ativa o uso da luz ambiente
    if (LuzAmbEhMax)
        glLightfv(GL_LIGHT0, GL_AMBIENT, LuzAmbienteMAX);
    else
        glLightfv(GL_LIGHT0, GL_AMBIENT, LuzAmbiente);
    // Define os parametros da Luz número Zero
    glLightfv(GL_LIGHT0, GL_DIFFUSE, LuzDifusa  );
    glLightfv(GL_LIGHT0, GL_SPECULAR, LuzEspecular  );
    glLightfv(GL_LIGHT0, GL_POSITION, PosicaoLuz0 );
    glEnable(GL_LIGHT0);

    // Ativa o "Color Tracking"
    glEnable(GL_COLOR_MATERIAL);

    // Define a reflectancia do material
    //glMaterialfv(GL_FRONT,GL_SPECULAR, Especularidade);

    // Define a concentração do brilho.
    // Quanto maior o valor do Segundo parametro, mais
    // concentrado será o brilho. (Valores válidos: de 0 a 128)
    glMateriali(GL_FRONT,GL_SHININESS,51);

    // ****************  Fonte de Luz 1

    // Ativa o uso da luz ambiente
    if (LuzAmbEhMax)
        glLightfv(GL_LIGHT1, GL_AMBIENT, LuzAmbienteMAX);
    else
        glLightfv(GL_LIGHT1, GL_AMBIENT, LuzAmbiente);
    // Define os parametros da Luz número Zero
    glLightfv(GL_LIGHT1, GL_DIFFUSE, LuzDifusa  );
    glLightfv(GL_LIGHT1, GL_SPECULAR, LuzEspecular  );
    glLightfv(GL_LIGHT1, GL_POSITION, PosicaoLuz1 );
    glEnable(GL_LIGHT1);

    // Ativa o "Color Tracking"
    glEnable(GL_COLOR_MATERIAL);

    // Define a reflectancia do material
    //glMaterialfv(GL_FRONT,GL_SPECULAR, Especularidade);

    // Define a concentração do brilho.
    // Quanto maior o valor do Segundo parametro, mais
    // concentrado será o brilho. (Valores válidos: de 0 a 128)
    //glMateriali(GL_FRONT,GL_SHININESS,20);

}




// **********************************************************************
//  void init(void)
//		Inicializa os parâmetros globais de OpenGL
//
// **********************************************************************

/* GLUT callback Handlers */

static void resize(int largura, int altura)
{
    const float ar = (float) largura / (float) altura;

    glViewport(0, 0, largura, altura);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-ar, ar, -1.0, 1.0, 2.0, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity() ;
}


static void display(void)
{
    const double t = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
    const double a = t*90.0;
    char opcao;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3d(0,0,1);
    /*Descomente para escolher os modos de luz*/

    //DefineLuzESPECULAR();
    //DefineLuzAMBIENTE();
    //DefineLuzDIFUSA();
       glRotatef( rotate_x, 1.0, 0.0, 0.0 );
       glRotatef( rotate_y, 0.0, 1.0, 0.0 );

    glPushMatrix();
    glTranslated(-2.4,1.2,-6);
    glRotated(60,1,0,0);
    glRotated(a,0,0,1);
    glutSolidSphere(1,slices,stacks);
    glPopMatrix();

    glPushMatrix();
    glTranslated(0,1.2,-6);
    glRotated(60,1,0,0);
    glRotated(a,0,0,1);
    glutSolidCone(1,1,slices,stacks);
    glPopMatrix();

    glPushMatrix();

    glTranslated(2.4,1.2,-6);
    glRotated(60,1,0,0);
    glRotated(a,0,0,1);
    glutSolidTorus(0.2,0.8,slices,stacks);
    glPopMatrix();

    glPushMatrix();
    glTranslated(-2.4,-1.2,-6);
    glRotated(60,1,0,0);
    glRotated(a,0,0,1);
    glutSolidCone(1,1,slices,stacks);
    glPopMatrix();

    glPushMatrix();
    glTranslated(0,-1.2,-6);
    glRotated(60,1,0,0);
    glRotated(a,0,0,1);
    glutSolidTeapot(size_element);
    glPopMatrix();



    glPushMatrix();
    glTranslated(2.4,-1.2,-6);
    glRotated(60,1,0,0);
    glRotated(a,0,0,1);
    glutSolidCube(size_element);
    glPopMatrix();

    glutSwapBuffers();

}

static void key(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 27:
    case 'q':
        exit(0);
        break;

    case 'a':
        slices++;
        stacks++;
        if(size_element<1)
        {
            size_element=size_element+0.1;
        }
        break;

    case 'd':
        if (slices>3 && stacks>3)
        {
            slices--;
            stacks--;
            if(size_element>0.2)
            {

                size_element=size_element-0.1;
            }
        }
        break;

    case '1':
        DefineLuzDIFUSA();
        break;
     case '2':
        DefineLuzAMBIENTE();
         break;
    case '3':
        DefineLuzESPECULAR();
        break;



    }

    glutPostRedisplay();
}
/*MUDANÇA DE POSIÇÃO DE OBJETOS*/
void specialKeys( int key, int x, int y ) {
    //  Right arrow - increase rotation by 5 degree
  if (key == GLUT_KEY_RIGHT)
    rotate_y += 0.01;

  //  Left arrow - decrease rotation by 5 degree
  else if (key == GLUT_KEY_LEFT)
    rotate_y -= 0.01;


  else if (key == GLUT_KEY_UP)
    rotate_x += 0.01;

  else if (key == GLUT_KEY_DOWN)
    rotate_x -= 0.01;

    glutPostRedisplay();
}
static void idle(void)
{
    glutPostRedisplay();
}

const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };

const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };

/* Program entry point */

int main(int argc, char *argv[])
{

    glutInit(&argc, argv);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("Pressione 'a' p/ aumentar a resolucao e 'd' p/ diminuir, 1 - LUZ Difusa, 2 - LUZ Ambiente, 3 - LUZ Especular, use as setas para desclocar as objetos");

    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutSpecialFunc(specialKeys);
    glutIdleFunc(idle);

    glClearColor(0.2,0.2,0.2,0.2);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);

    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);

    glutMainLoop();

    return EXIT_SUCCESS;
}
