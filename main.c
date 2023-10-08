#include <glut.h>
#include <stdio.h>
#include <SOIL.h>
#include <stdlib.h>
#include "image.h"
#define TEXTURA_DO_PLANO "image.rgb"

GLfloat win;
GLint movedoor = 0;
GLint direction = 1;

void mouse(int button, int state, int x, int y);
void opendoor(int passo);

static int left = 0, up = 0;
static int shoulder = 0, elbow = 0, elbow2 = 0;

int aux;

//---------------------------------------------------------------------NEW----------------------------------------------------

GLfloat teto_difusa[] = {1.0, 1.0, 1.0, 1.0};
GLfloat teto_especular[] = {1.0, 1.0, 1.0, 1.0};
GLfloat teto_brilho[] = {20.0};

GLfloat parede_difusa[] = {0.0, 0.0, 1.0, 1.0};
GLfloat parede_especular[] = {1.0, 1.0, 1.0, 1.0};
GLfloat parede_brilho[] = {50.0};

GLfloat arm_difusa[] = {1.0, 0.0, 1.0, 1.0};
GLfloat arm_especular[] = {1.0, 1.0, 1.0, 1.0};
GLfloat arm_brilho[] = {50.0};

GLfloat porta_difusa[] = {1.0, 1.0, 0.0, 1.0};
GLfloat porta_especular[] = {1.0, 1.0, 1.0, 1.0};
GLfloat porta_brilho[] = {50.0};

GLfloat macaneta_difusa[] = {1.0, 0.0, 0.0, 1.0};
GLfloat macaneta_especular[] = {1.0, 1.0, 1.0, 1.0};
GLfloat macaneta_brilho[] = {50.0};

GLfloat posicao_luz[] = {-2.0, 6.0, 4.0, 1.0};
GLfloat posicao_Bluz[] = {2.0, 6.0, 4.0, 1.0};
GLfloat cor_luz[] = {1.0, 1.0, 1.0, 1.0};
GLfloat cor_luz_amb[] = {0.0, 0.0, 0.0, 1.0};

GLint gouraud = 0;

//---------------------------------------------------------------------NEW----------------------------------------------------

GLuint textura_plano;

// GLfloat planotext[4][2]={
//   {-1,-1},
//   {+1,-1},
//   {+1,+1},
//   {-1,+1}
// };

GLfloat planotext[4][2] = {
    {0, 0},
    {+1, 0},
    {+1, +1},
    {0, +1}};

// void carregar_texturas(void)
// {
//   IMAGE *img;
//   GLenum gluerr;

//   /* textura do plano */
//   glGenTextures(1, &textura_plano);
//   glBindTexture(GL_TEXTURE_2D, textura_plano);

//   if (!(img = ImageLoad(TEXTURA_DO_PLANO)))
//   {
//     fprintf(stderr, "Error reading a texture.\n");
//     exit(-1);
//   }

//   gluerr = gluBuild2DMipmaps(GL_TEXTURE_2D, 3,
//                              img->sizeX, img->sizeY,
//                              GL_RGB, GL_UNSIGNED_BYTE,
//                              (GLvoid *)(img->data));
//   if (gluerr)
//   {
//     fprintf(stderr, "GLULib%s\n", gluErrorString(gluerr));
//     exit(-1);
//   }

//   glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//   glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//   glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
//   glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//   glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
// }

void init(void)
{

  glShadeModel(GL_FLAT);
  gouraud = 1;
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glClearColor(0.0, 0.0, 0.0, 0.0);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, cor_luz);
  glLightfv(GL_LIGHT0, GL_SPECULAR, cor_luz);
  glLightfv(GL_LIGHT0, GL_AMBIENT, cor_luz_amb);
  glLightfv(GL_LIGHT0, GL_POSITION, posicao_luz);
  glLightfv(GL_LIGHT0, GL_POSITION, posicao_Bluz);

  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);

  glEnable(GL_AUTO_NORMAL);
  glEnable(GL_NORMALIZE);

  // carregar_texturas();
  win = 1;
  //  glutPostRedisplay();
}

void display(void)
{

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glClear(GL_COLOR_BUFFER_BIT);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_LIGHTING);

  glDepthMask(GL_TRUE);

  if (gouraud)
  {
    glShadeModel(GL_SMOOTH);
  }
  else
  {
    glShadeModel(GL_FLAT);
  }

  glPushMatrix();
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
  glBindTexture(GL_TEXTURE_2D, textura_plano);

  /* origem posicionada da Sala*/
  glTranslatef(0.0, 0.0, 0.0);
  glRotatef((GLfloat)left, 0.0, 1.0, 0.0);
  glRotatef((GLfloat)up, 1.0, 0.0, 0.0);

  /* origem posicionada no centro da Comodo */
  glColor3f(1.0, 0.0, 0.0);
  glPushMatrix();
  glTranslatef(0.0, 0.0, 0.0);
  glutWireCube(5.0);
  // glutSolidCube (5.0);
  glPopMatrix();

  //-------------------------------teto do quarto

  /* propriedades do material do chao */
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, teto_difusa);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, teto_especular);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, teto_brilho);

  glColor3f(6.0, 6.0, 6.0);
  glPushMatrix();
  glRotatef(180.0, 1.0, 0.0, 0.0);
  glTranslatef(0.0, -2.4, 0.0);
  glScalef(5.0, 0.0, 5.0);
  glutSolidCube(1.0);
  // glutWireCube (1.0);
  glPopMatrix();

  /*/---------------------------------ch�o
  glColor3f(1.0, 1.0, 1.0);
  glPushMatrix ();
  glTranslatef (0.0, -2.4, 0.0);
  glScalef(5.0, 0.0, 5.0);
  glutSolidCube (1.0);
  //glutWireCube (1.0);
  glPopMatrix ();
  */
  //-------------------------------------Paredes do quarto

  /* propriedades do material do chao */
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, parede_difusa);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, parede_especular);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, parede_brilho);

  glColor3f(7.0, 0.0, 0.0);
  glColor3f(0.0, 101.0, 0.0);
  glColor3f(0.0, 0.0, 168.0);
  glPushMatrix();
  glRotatef(90.0, 1.0, 0.0, 0.0);
  glTranslatef(0.0, -2.4, 0.0);
  glScalef(5.0, 0.0, 5.0);
  glutSolidCube(1.0);
  // glutWireCube (5.0);
  glPopMatrix();

  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, parede_difusa);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, parede_especular);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, parede_brilho);

  glColor3f(7.0, 0.0, 0.0);
  glColor3f(0.0, 101.0, 0.0);
  glColor3f(0.0, 0.0, 168.0);
  glPushMatrix();
  glRotatef(90.0, 0.0, 1.0, 0.0);
  glTranslatef(1.5, 0.0, 2.5);
  glScalef(1.9, 5.0, 0.0);
  glutSolidCube(1.0);
  // glutWireCube (5.0);
  glPopMatrix();

  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, parede_difusa);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, parede_especular);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, parede_brilho);

  glColor3f(7.0, 0.0, 0.0);
  glColor3f(0.0, 101.0, 0.0);
  glColor3f(0.0, 0.0, 168.0);
  glPushMatrix();
  glRotatef(90.0, 0.0, 1.0, 0.0);
  glTranslatef(-1.8, 0.0, 2.5);
  glScalef(1.4, 5.0, 0.0);
  glutSolidCube(1.0);
  // glutWireCube (1.0);
  glPopMatrix();

  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, parede_difusa);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, parede_especular);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, parede_brilho);

  glColor3f(7.0, 0.0, 0.0);
  glColor3f(0.0, 101.0, 0.0);
  glColor3f(0.0, 0.0, 168.0);
  glPushMatrix();
  glRotatef(90.0, 0.0, 1.0, 0.0);
  glTranslatef(-0.3, 1.5, 2.5);
  glScalef(1.7, 2.0, 0.0);
  glutSolidCube(1.0);
  // glutWireCube (1.0);
  glPopMatrix();

  //-------------------------------

  /* propriedades do material do chao */
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, parede_difusa);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, parede_especular);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, parede_brilho);

  glColor3f(7.0, 0.0, 0.0);
  glColor3f(0.0, 101.0, 0.0);
  glColor3f(0.0, 0.0, 168.0);
  glPushMatrix();
  glRotatef(-90.0, 0.0, 0.0, 1.0);
  glTranslatef(1.6, -2.4, 0.0);
  glScalef(1.9, 0.0, 5.0);
  glutSolidCube(1.0);
  // glutWireCube (1.0);
  glPopMatrix();

  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, parede_difusa);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, parede_especular);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, parede_brilho);

  glColor3f(7.0, 0.0, 0.0);
  glColor3f(0.0, 101.0, 0.0);
  glColor3f(0.0, 0.0, 168.0);
  glPushMatrix();
  glRotatef(90.0, 0.0, 0.0, 1.0);
  glTranslatef(1.6, 2.4, 0.0);
  glScalef(1.9, 0.0, 5.0);
  glutSolidCube(1.0);
  // glutWireCube (1.0);
  glPopMatrix();

  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, parede_difusa);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, parede_especular);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, parede_brilho);

  glColor3f(7.0, 0.0, 0.0);
  glColor3f(0.0, 101.0, 0.0);
  glColor3f(0.0, 0.0, 168.0);
  glPushMatrix();
  glRotatef(-90.0, 0.0, 0.0, 1.0);
  glRotatef(-90.0, 0.0, 1.0, 0.0);
  glTranslatef(1.6, -2.4, 0.0);
  glScalef(1.9, 0.0, 5.0);
  glutSolidCube(1.0);
  // glutWireCube (1.0);
  glPopMatrix();

  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, parede_difusa);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, parede_especular);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, parede_brilho);

  glColor3f(7.0, 0.0, 0.0);
  glColor3f(0.0, 101.0, 0.0);
  glColor3f(0.0, 0.0, 168.0);
  glPushMatrix();
  glRotatef(-90.0, 0.0, 0.0, 1.0);
  glRotatef(90.0, 0.0, 1.0, .0);
  glTranslatef(1.6, -2.4, 0.0);
  glScalef(1.9, 0.0, 5.0);
  glutSolidCube(1.0);
  // glutWireCube (1.0);
  glPopMatrix();

  //-------------------------------Guarda-Roupa

  /* propriedades do material do armario */
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, arm_difusa);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, arm_especular);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, arm_brilho);

  glColor3f(0.0, 1.0, 0.0);
  glPushMatrix();
  glRotatef(90.0, 0.0, 1.0, 0.0);
  glTranslatef(2.21, -0.7, 0.0);
  glScalef(1.0, 5.9, 4.7);
  glutSolidCube(0.5);
  glPopMatrix();

  //-------------------------------P�s do guarda-roupa

  glColor3f(1.0, 0.0, 0.0);
  glPushMatrix();
  glRotatef(90.0, 1.0, 0.0, 0.0);
  glTranslatef(1.1, -2.1, 2.2);
  gluCylinder(gluNewQuadric(), 0.1, 0.1, 0.3, 16, 1);
  glPopMatrix();

  glColor3f(1.0, 0.0, 0.0);
  glPushMatrix();
  glRotatef(90.0, 1.0, 0.0, 0.0);
  glTranslatef(1.1, -2.4, 2.2);
  gluCylinder(gluNewQuadric(), 0.1, 0.1, 0.3, 16, 1);
  glPopMatrix();

  glColor3f(1.0, 0.0, 0.0);
  glPushMatrix();
  glRotatef(90.0, 1.0, 0.0, 0.0);
  glTranslatef(-1.1, -2.1, 2.2);
  gluCylinder(gluNewQuadric(), 0.1, 0.1, 0.3, 16, 1);
  glPopMatrix();

  glColor3f(1.0, 0.0, 0.0);
  glPushMatrix();
  glRotatef(90.0, 1.0, 0.0, 0.0);
  glTranslatef(-1.1, -2.4, 2.2);
  gluCylinder(gluNewQuadric(), 0.1, 0.1, 0.3, 16, 1);
  glPopMatrix();

  //-------------------------------Gaveta
  glColor3f(1.0, 1.0, .0);
  glPushMatrix();
  glRotatef(90.0, 0.0, 1.0, 0.0);
  glTranslatef(2.21, -1.9, 0.0);
  glScalef(1.0, 1.2, 4.7);
  glutSolidCube(0.5);
  glPopMatrix();
  //-------------------------------Porta do Garda-Roupa Direita

  /* propriedades do material do porta */
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, porta_difusa);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, porta_especular);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, porta_brilho);

  glColor3f(1.0, 0.0, 1.0);
  glPushMatrix();
  glRotatef(90.0, 0.0, 1.0, 0.0);
  glTranslatef(2.0, 0.0, 1.1);
  glRotatef((GLfloat)shoulder, 0.0, 1.0, 0.0);
  glTranslatef(2.0, -0.4, -0.6);
  glTranslatef(-2.0, 0.0, 0.1);
  glScalef(0.2, 4.7, 2.35);
  glutSolidCube(0.5);
  //-----------------------MA�ANETA---------
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, macaneta_difusa);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, macaneta_especular);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, macaneta_brilho);

  glColor3f(1.0, 0.0, 0.0);
  glPushMatrix();
  glTranslatef(-0.2, 0.0, -0.2);
  glScalef(8.0, 0.3, 0.5);
  glutSolidSphere(0.1, 32, 32);
  glPopMatrix();
  glPopMatrix();

  //-------------------------------Porta do Garda-Roupa Esquerda

  /* propriedades do material do porta */
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, porta_difusa);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, porta_especular);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, porta_brilho);

  glColor3f(0.0, 1.0, 1.0);
  glPushMatrix();
  glRotatef(90.0, 0.0, 1.0, 0.0);
  glTranslatef(2.0, 0.0, -1.1);
  glRotatef((GLfloat)elbow, 0.0, -1.0, 0.0);
  glTranslatef(2.0, -0.4, 0.6);
  glTranslatef(-2.0, 0.0, -0.1);
  glScalef(0.2, 4.7, 2.35);
  glutSolidCube(0.5);

  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, macaneta_difusa);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, macaneta_especular);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, macaneta_brilho);

  // Ma�aneta da Esquerda
  glColor3f(1.0, 0.0, 0.0);
  glPushMatrix();
  glTranslatef(-0.2, 0.0, 0.2);
  glScalef(8.0, 0.3, 0.5);
  glutSolidSphere(0.1, 16, 16);
  glPopMatrix();
  glPopMatrix();

  //-----------------------------------------Ma�aneta do gaurda Roupa

  /* propriedades do material da macaneta */

  glColor3f(1.0, 0.0, 0.0);
  glPushMatrix();
  glTranslatef(-0.0, -1.9, -1.9);
  // glRotatef (30.0, 1.0, 0.0, 0.0);
  glutSolidSphere(0.1, 16, 16);
  glPopMatrix();

  /* -----------------------------------------------------textura------------------------------ */

  glEnable(GL_TEXTURE_2D);
  glBegin(GL_QUADS);
  glTexCoord2fv(planotext[0]);
  glVertex3f(2.5f, /*altura-->*/ -2.5f, -2.5f);
  glTexCoord2fv(planotext[1]);
  glVertex3f(2.5f, /*alturaa-->*/ -2.5f, 2.5f);
  glTexCoord2fv(planotext[2]);
  glVertex3f(-2.5f, /*altura-->*/ -2.5f, 2.5f);
  glTexCoord2fv(planotext[3]);
  glVertex3f(-2.5f, /*altura-->*/ -2.5f, -2.5f);

  // glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, fbo_width, fbo_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
  // glVertex2i(movedoor+5,210);
  glEnd();
  glRotatef(90.0, 0.0, 1.0, 0.0);
  glTranslatef(-2, -5, 4);
  glDisable(GL_TEXTURE_2D);

  /* origem volta para o sistema de coordenadas original */
  glPopMatrix();
  glutSwapBuffers();
}

void reshape(int w, int h)
{

  glViewport(0, 0, (GLsizei)w, (GLsizei)h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(65.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glTranslatef(0.0, 0.0, -5.0);
}
void mouse(int button, int state, int x, int y)
{
  switch (button)
  {
  case GLUT_LEFT_BUTTON:
    if (state == GLUT_DOWN)
    {
      win -= 0.1;
      glTranslatef(0, 0, win);
      glutPostRedisplay();
    }
    break;

  case GLUT_RIGHT_BUTTON:
    if (state == GLUT_DOWN)
    {
      win += 0.1;
      glTranslatef(0, 0, -win);
      glutPostRedisplay();
    }
    break;
  }
}

void keyboard(unsigned char key, int x, int y)
{
  switch (key)
  {

  case 'a':
    left = (left + 5) % 360;
    glutPostRedisplay();
    break;

  case 'd':
    left = (left - 5) % 360;
    glutPostRedisplay();
    break;

  case 'w':
    up = (up + 5) % 360;
    glutPostRedisplay();
    break;

  case 's':
    up = (up - 5) % 360;
    glutPostRedisplay();
    break;

    /*case 'g':
      elbow = (elbow - 5) % 360;
      glutPostRedisplay();
    break;

     case 'f':
      elbow = (elbow + 5) % 360;
    glutPostRedisplay();
    break;

     case 'r':
      shoulder = (shoulder + 5) % 360;
      glutPostRedisplay();
      break;

     case 't':
      shoulder = (shoulder - 5) % 360;
      glutPostRedisplay();
      break;*/

  case 'k':

    glTranslatef(0.0, 0.0, 0.0);
    glRotatef((GLfloat)left, 0.0, 1.0, 0.0);
    glRotatef((GLfloat)up, 1.0, 0.0, 0.0);
    aux = win;
    win = 6.5;
    glTranslatef(0, 0, -win);
    win = aux;

    glutPostRedisplay();
    break;
  case 'l':
    glLoadIdentity();
    gluLookAt(0.0f, 0.0f, 0.0f,
              0.2f, -0.5f, -1.9f,
              0.01f, 1.0f, 0.0f);
    glutPostRedisplay();
    break;
  case 27:
    exit(0);
    break;
  default:
    break;
  }
}

void opendoor(int passo)
{
  if (direction == 1)
  {
    elbow = (elbow + 1) % 360;
    shoulder = (shoulder + 1) % 360;
    if (elbow == 150)
      direction = 0;
  }
  else
  {
    elbow = (elbow - 1) % 360;
    shoulder = (shoulder - 1) % 360;
    if (elbow == 0)
      direction = 1;
  }
  glutPostRedisplay();
  glutTimerFunc(10, opendoor, 1);
}

int main(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(500, 500);
  glutInitWindowPosition(100, 100);
  glutCreateWindow(argv[0]);
  init();
  glutDisplayFunc(display);
  glutTimerFunc(10, opendoor, 1);
  glutReshapeFunc(reshape);
  glutMouseFunc(mouse);
  glutKeyboardFunc(keyboard);
  glutMainLoop();
  return 0;
}
