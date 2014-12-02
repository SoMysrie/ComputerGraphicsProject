#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdarg.h>

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
/*
#include "ModuleCouleurs.h"
#include "ModuleMenus.h"
#include "ModuleFont.h"
#include "ModuleFleche.h"
#include "ModuleReshape.h"
*/
static int aff;
static int yy;
static int f1;
static int f2;
static char buffer[2000];
static int pos;
static float r = 20.0F;

void dessineQuadrillage(void) {
  float i;
  glColor4fv(couleurGrisMoyen()) ;
  glBegin(GL_LINES);
  for ( i = -1.0 ; i < 24 ; i++ ) {
    glVertex2d(-1.0,i);
    glVertex2d(17.0,i); }
  for ( i = -1.0 ; i < 18 ; i++ ) {
    glVertex2d(i,-1.0);
    glVertex2d(i,23.0); }
  glEnd() ;
  glPushMatrix();
  glTranslatef(-0.5F,0.5F,0.0F);
  flecheEnVolume(17.2F,0.0F,0.0F,0.35F,1.4F,0.1F);
  glPopMatrix();
  glPushMatrix();
  glTranslatef(0.5F,-0.5F,0.0F);
  flecheEnVolume(0.0F,23.2F,0.0F,0.35F,1.4F,0.1F);
  glPopMatrix();
}

void arc(float r) {
  glLineWidth(3.0);
  glColor4fv(couleurBleu()) ;
  glBegin(GL_LINE_STRIP) ;
  for ( int i = 0 ; i <= 45 ; i++ ) {
    float angle = i * 3.14159F / 180 ;
    float x = (float) (r*cos(angle)+0.5F) ;
    float y = (float) (r*sin(angle)+0.5F) ;
    glVertex2f(y,x) ; }
  glEnd() ;
  glLineWidth(1.0);
}

void pixel(int x,int y,float *c) {
  glColor4fv(c) ;
  glBegin(GL_QUADS) ;
  glVertex2f(x,y) ;
  glVertex2f(x,y+1) ;
  glVertex2f(x+1,y+1) ;
  glVertex2f(x+1,y) ;
  glEnd() ;
}

void arcDiscret(float *c,float r) {
  int x,y,d ;
  x = 0 ;
  y =(int) r ;
  d =(int) (1 - r) ;
  pixel(x,y,c) ;
  while ( y > x ) {
    if ( d < 0 )
      d += 2 * x + 3 ;
      else {
      d += 2 * (x - y) + 5 ;
      y-- ; }
    x++ ;
    pixel(x,y,c) ; }
}

void arcIncomplet(float *c,float r,int max) {
  int x,y,d ;
  x = 0 ;
  y =(int) r ;
  d =(int) (1 - r) ;
  pixel(x,y,c) ;
  int cpt = 0;
  while ( ( y > x ) && ( cpt < max ) ) {
    cpt++;
    if ( d < 0 )
      d += 2 * x + 3 ;
      else {
      d += 2 * (x - y) + 5 ;
      y-- ; }
    x++ ;
    pixel(x,y,c) ; }
}

void output(float x,char *format,...) {
  va_list args;
  va_start(args,format);
  vsprintf(buffer,format,args);
  va_end(args);
  placeFontCursor(x,-pos*20.0F+10,0.0F) ;
  simpleBitmapOutput(1,REGULAR8x13,buffer) ;
}

void newLine() {
  pos += 1;
}

void arcIncompletTexte(float r,int max) {
  pos = 1;
  glColor4fv(couleurGrisMoyen());
  glBegin(GL_LINES);
  glVertex2f(205.0F,-5.0F);
  glVertex2f(205.0F,-320.0F);
  glVertex2f(245.0F,-5.0F);
  glVertex2f(245.0F,-320.0F);
  glVertex2f(5.0F,-22.0F);
  glVertex2f(345.0F,-22.0F);
  glEnd();
  glColor4fv(couleurBlanc());
  int x,y,d ;
  x = 0 ;
  y =(int) r ;
  d =(int) (1 - r) ;
  output(105.0F,"d") ;
  output(225.0F,"x") ;
  output(295.0F,"y") ;
  newLine();
  output(105.0F,"%d",d) ;
  output(225.0F,"%d",x) ;
  output(295.0F,"%d",y) ;
  newLine();
  int cpt = 0;
  while ( ( y > x ) && ( cpt < max ) ) {
    cpt++;
    int old = d;
    if ( d < 0 ) {
      d += 2 * x + 3 ;
      output(105.0F,"%d+2*%d+3 -> %d",old,x,d) ;
      output(295.0F,"%d",y) ; }
      else {
      d += 2 * (x - y) + 5 ;
      output(105.0F,"%d+2*(%d-%d)+5 -> %d",old,x,y,d) ;
      y-- ;
      output(295.0F,"%d -> %2d",y+1,y) ; }
    x++ ;
    output(225.0F,"%d",x) ;
    newLine(); }
}

void display() {
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
  glPushMatrix();
  dessineQuadrillage();
  glColor4fv(couleurGrisMoyen());
  glLineWidth(3.0);
  glBegin(GL_LINES);
  glVertex2f(0.5F,0.5F);
  glVertex2f(16.5F,16.5F);
  glEnd();
  glLineWidth(1.0);
  switch (aff) {
    case 0 : arc(r) ;
             break ;
    case 1 : arcDiscret(couleurRouge(0.5F),r) ;
             arc(r) ;
             break ;
    case 2 : arcIncomplet(couleurRouge(0.5F),r,yy) ;
             arc(r) ; }
  glutPostWindowRedisplay(f2);
  glPopMatrix();
  glFlush();
  glutSwapBuffers() ;
}

void myinit() {
  glEnable(GL_ALPHA_TEST);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
  glClearColor(0.8F,0.8F,0.8F,1.0F);
  setAlignement(CENTER);
}

void key(unsigned char key,int x,int y) {
  switch ( key ) {
    case 32   : yy = (yy+1)%15 ;
                glutPostWindowRedisplay(f1);
                break;
    case 0x0D : yy = 0 ;
                aff = (aff+1)%3 ;
                glutPostWindowRedisplay(f1);
                break;
    case 0x1B : exit(0) ;
                break; }
}

void display2(void) {
  glClearColor(0.0F,0.0F,0.0F,1.0F) ;
  glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
  glPushMatrix();
  switch (aff) {
    case 2 : arcIncompletTexte(r,yy) ; }
  glPopMatrix();
  glFlush();
  glutSwapBuffers();
}

void reshape2(int w,int h) {
  glViewport(0,0,w,h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0,w,-h,0,-1.0,1.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

int main(int argc,char **argv) {
  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_RGBA|GLUT_DEPTH|GLUT_DOUBLE);
  glutInitWindowSize(270,360);
  glutInitWindowPosition(50,10);
  f1 = glutCreateWindow("Cercle par l'algorithme de Bresenham");
  myinit();
  creationMenuBasique();
  setParametresOrthoBasique(-1.5,17.5,-1.2,17.8,-40.0,40.0);
  glutReshapeFunc(reshapeOrthoBasique);
  glutKeyboardFunc(key);
  glutDisplayFunc(display);
  glutInitWindowSize(350,325);
  glutInitWindowPosition(350,10);
  glutInitDisplayMode(GLUT_RGBA|GLUT_DEPTH|GLUT_DOUBLE);
  f2 = glutCreateWindow("Valeurs");
  creationMenuBasique();
  glutDisplayFunc(display2);
  glutReshapeFunc(reshape2);
  glutKeyboardFunc(key);
  glutMainLoop();
  return(0);
}
