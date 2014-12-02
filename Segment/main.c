#include <windows.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include "segment.h"

int xa,ya,xb,yb,inc;        // declaration des entiers
int firstRound=1,click=0;   // initialisation de l'octant et du clic
Color color;              // declaration de la couleur

void display(void);                               // declaration de la fonction affichage
void keyboard(unsigned char touch,int x,int y);     // declaration de la fonction clavier (détecter ce que tape l'utilisateur au clavier)
void mouse(int button,int state,int x,int y);        // declaration de la fonction souris (détecter où pointe la souris

int main(int argc,char **argv)
{
    glutInit(&argc, argv);                                      // fonction glut
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);   // mode d'affichage
    glutInitWindowSize(800, 800);                               // taille de la fenêtre (largeur, hauteur)
	glutInitWindowPosition (100, 100);                          // position de la fenêtre sur l'écran (côté gauche, côté haut)
	glutCreateWindow("Segments");                               // titre**/

	gluOrtho2D(-400.0,400.0,-400.0,400.0);  // repère à deux dimensions (-x, x, -y, y)

	glClearColor(0.0, 0.0, 0.0, 0.0);       // couleur du fond d'écran (noir)
	glColor3f(1.0, 0.0, 0.0);               // couleur du tracé (rouge)
	glPointSize(1.0);                       // taille du point

	glutDisplayFunc(display); // appel de la fonction affichage
	glutKeyboardFunc(keyboard);  // appel de la fonction clavier
	glutMouseFunc(mouse);       // appel de la fonction souris

	glutMainLoop();             // fonction de glut pour boucler
	return 0;
}

/** fonction de l'affichage**/
void display(void)
{
    if(firstRound)                     // detection pour initialisation les 8 octants
    {
        glClear(GL_COLOR_BUFFER_BIT);   // appel de la fonction de glut pour les couleurs

        glBegin(GL_LINES);              // appel de la fonction de glut pour le tracé des lignes
            glColor3f(1.0, 1.0, 1.0);   // couleur blanche
            glVertex2f(-400,0);         // vecteur du tracé -x, 0
            glVertex2f(400,0);          // vecteur du tracé 0, x
            glVertex2f(0,-400);         // vecteur du tracé -y, 0
            glVertex2f(0,400);          // vecteur du tracé 0, y
            glVertex2f(-400,400);       // vecteur du tracé -x, x => diagonale
            glVertex2f(400,-400);       // vecteur du tracé x, -x => diagonnale
            glVertex2f(-400,-400);      // vecteur du tracé -y, y => diagonale
            glVertex2f(400,400);        // vecteur du tracé y, -y => diagonale
        glEnd();         // fin de Begin

        firstRound=0;   // initialisation du premier tour
    }
    else if(click==2)     // détection de deux clics de la souris poour tracer le segment
    {
        color.r=1.0;    // rouge
        color.g=0;      // vert
        color.b=0;      // bleu

        segment(xa,ya,xb,yb,color);     // appel de la fonction segment
        click=0;
    }
    glFlush();      // fonction de l'affichage de glut, très important!!
}

// fonction de la souris
void mouse(int button,int state,int x,int y)
{
    int x0,y0;  // initialisation de x et y

    // appuie sur le bouton gauche ou non
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{// la souris ne peut se déplacer que dans la fenêtre et un octant
		x0 = x - 400;
		y0 = -y + 400;
		if(click==0)
        {// position du curseur toujours en attente sur le premier point
            xa=x0;
            ya=y0;
            click++;
        }
        else if(click==1)
        {// position du cuseur en attente du deuxieme point
            xb=x0;
            yb=y0;
            click++;
        }
        display();    // appel de la fonction affichage
	}
}

// fonction du clavier
void keyboard(unsigned char touch,int x,int y)
{
    switch(touch)
    {
    case 27:  // Code ASCII de la touche Echap
        exit(0);
        break;
    case 'r':
        firstRound=1;
    default:
        display();
        break;
    }
}
