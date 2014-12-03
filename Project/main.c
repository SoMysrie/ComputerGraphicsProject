#include "header.h"

/**

Notice:

Mode de traçage:
S : Tracer des segments (2 clics)
C : Tracer des cercles (2 clics)
A : Tracer des rectangles (2 clics)

Fenetrage:
F : Mode de création de fenetre (2 clics), appuyer une fois sur F enleve le fenetrage en cours

Autres:
O : Afficher/Cacher les axes
P : Changer de couleur (dans la console)
R : Reinitialiser le programme
Echap : Quitter le programme

**/

Shape shapes[100],lim;                                          //declaration du tableau de la structure forme et de la limite du fenetrage
int i=0,j=0,maxi=0;                                                 //declaration des variables
int xa,ya,xb,yb,inc,xt,yt;
int x0,y0;
int firstRound=1,click=0,redisplay=0,type=SEGMENT,axes=0;
Color color;                                                    //declaration de la structure couleur
HWND hwndConsole,hwndFenetre;

void display(void);                                             //declaration de la fonction affichage
void keyboard(unsigned char touch,int x,int y);                 //declaration de la fonction clavier
void mouse(int button,int state,int x,int y);                   //declaration de la fonction souris
void motion(int x,int y);                                       //declaration de la fonction motion, suivi du tracé en fonction de la souris
void menu(int n);                                               //declaration de la fonction menu déroulant

int main(int argc,char **argv)                                  //fonction principale
{
    glutInit(&argc, argv);                                      //initialisation
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);   //initialisation du mode d'affichage
    glutInitWindowSize(800, 800);                               //taille de la fenêtre
	glutInitWindowPosition (100, 100);                          //position de la fenêtre
	glutCreateWindow("Project");                                //titre de la fenetre

	color.r=255;                                                //choix du couleur par défaut pour tracer
    color.g=0;
    color.b=0;
    displayColor(color);                                        //affichage de la couleur
    hwndConsole=GetForegroundWindow();

    lim.xa=-401;                                                //401 car c'est 800/800
    lim.ya=-401;                                                //la souris n'est plus détectée
    lim.xb=401;                                                 //plus par precaution
    lim.yb=401;
    lim.col=color;                                              //couleur du contour de la fenetre

	gluOrtho2D(-400.0,400.0,-400.0,400.0);                      //centre du repere

	glClearColor(0.0, 0.0, 0.0, 0.0);                           //couleur du fond d'écran
	glColor3f(1.0, 0.0, 0.0);
	glPointSize(1.0);                                           //1 pixel

	glutDisplayFunc(display);                                   //appel de la fonction affichage avec celle de glut
	glutKeyboardFunc(keyboard);                                 //appel de la fonction clavier avec celle de glut
	glutMouseFunc(mouse);                                       //appel de la fonction affichage avec celle de glut
	glutPassiveMotionFunc(motion);                              //appel de la fonction du mouvement de la souris mais sans clic
	glutMotionFunc(motion);                                     //appel de la fonction du mouvement de la souris avec clic

    glutCreateMenu(menu);                                       //creation du menu deroulant
	glutAddMenuEntry("Segment",SEGMENT);
	glutAddMenuEntry("Cercle",CIRCLE);
	glutAddMenuEntry("Rectangle",RECTANLGE);
	glutAddMenuEntry("Fenetrage",WINDOW);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutMainLoop();
	return 0;
}

void display(void)                                              //fonction affichage
{
    hwndFenetre=GetForegroundWindow();
    if(firstRound)
    {
        glClear(GL_COLOR_BUFFER_BIT);

        if(axes)                                                //si l'utilisateur demande les axes, tracé les 8 octants
        {
            glBegin(GL_LINES);
            glColor3f(1.0, 1.0, 1.0);
            glVertex2f(-400,0);
            glVertex2f(400,0);
            glVertex2f(0,-400);
            glVertex2f(0,400);
            glVertex2f(-400,400);
            glVertex2f(400,-400);
            glVertex2f(-400,-400);
            glVertex2f(400,400);
            glEnd();
        }

        firstRound=0;
    }
    if(redisplay)                                               //permet d'afficher toutes les formes qui ont ete enregistrées dans le tableau
    {
        square(lim.xa,lim.ya,lim.xb,lim.yb,lim.col,lim);
        for(i=0;i<maxi;i++)
        {
            if(shapes[i].type==SEGMENT)
                segment(shapes[i].xa,shapes[i].ya,shapes[i].xb,shapes[i].yb,shapes[i].col,lim);
            else if(shapes[i].type==CIRCLE)
                circle(shapes[i].xa,shapes[i].ya,shapes[i].xb,shapes[i].yb,shapes[i].col,lim);
            else if(shapes[i].type==RECTANLGE)
                square(shapes[i].xa,shapes[i].ya,shapes[i].xb,shapes[i].yb,shapes[i].col,lim);
        }

        redisplay=0;
    }
    if(click==2)
    {
        if(type==WINDOW)
        {
            square(xa,ya,xb,yb,color,lim);
            lim.xa=xa;
            lim.ya=ya;
            lim.xb=xb;
            lim.yb=yb;
            lim.col=color;
            orderSquare(&lim);
            firstRound=1;
            redisplay=1;
        }
        else
        {
            if(type==SEGMENT)
                segment(xa,ya,xb,yb,color,lim);
            else if(type==CIRCLE)
                circle(xa,ya,xb,yb,color,lim);
            else if(type==RECTANLGE)
                square(xa,ya,xb,yb,color,lim);

            shapes[j].type=type;
            shapes[j].col=color;
            shapes[j].xa=xa;
            shapes[j].xb=xb;
            shapes[j].ya=ya;
            shapes[j].yb=yb;
            if(j==99)
                j=0;
            else
                j++;

            if(maxi<100)
                maxi++;
        }
        click=0;
    }
    else if(click==1)
    {
        if(type==SEGMENT)
            segment(xa,ya,xt,yt,color,lim);
        else if(type==CIRCLE)
            circle(xa,ya,xt,yt,color,lim);
        else if(type==RECTANLGE||type==WINDOW)
            square(xa,ya,xt,yt,color,lim);
    }

    glFlush();

    if(firstRound||redisplay)
        display();
}

void mouse(int button,int state,int x,int y)                                //fonction de la souris
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)                   //detecter si boutton gauche est appuyé et l'état appelle la fonction du glut bas
	{
		x0 = x - 400;
		y0 = -y + 400;
		if(click==0)
        {
            if(type==WINDOW)
            {
                lim.xa=-401;
                lim.ya=-401;
                lim.xb=401;
                lim.yb=401;
                firstRound=1;
                redisplay=1;
            }
            xa=x0;
            ya=y0;
            xt=xa;
            yt=ya;
            click++;
        }
        else if(click==1)
        {
            xb=x0;
            yb=y0;
            click++;
        }
		display();                                                      //appel de la fonction affichage
	}
}

void keyboard(unsigned char touch,int x,int y)                          //fonction clavier
{
    switch(touch)                                                       //choix des touches
    {
    case 27:  // Code ASCII de la touche Echap                          //quitter
        exit(0);
        break;
    case 'r':                                                           //nettoyer l'écran
        j=0;
        maxi=0;
        click=0;
        lim.xa=-401;
        lim.ya=-401;
        lim.xb=401;
        lim.yb=401;
        firstRound=1;
        break;
    case 's':                                                           //tracer un segment
        if(click==0)
            type=SEGMENT;
        break;
    case 'c':                                                           //tracer un cercle
        if(click==0)
            type=CIRCLE;
        break;
    case 'a':                                                           //tracer un rectangle
        if(click==0)
            type=RECTANLGE;
        break;
    case 'f':                                                           //tracer un fenetrage
        if(click==0)
        {
            type=WINDOW;
            lim.xa=-401;
            lim.ya=-401;
            lim.xb=401;
            lim.yb=401;
            redisplay=1;
            firstRound=1;
        }
        break;
    case 'o':                                                           //afficher les axes
        if(!axes)
            axes=1;
        else
            axes=0;
            firstRound=1;
            redisplay=1;
        break;
    case 'p':                                                           //afficher la console pour rentrer la nouvelle couleur
        SetForegroundWindow(hwndConsole);
        changeColor(&color);
        hwndConsole=GetForegroundWindow();
        SetForegroundWindow(hwndFenetre);
        hwndFenetre=GetForegroundWindow();
        break;
    }
    display();                                                          //appel de la focntion affichage
}

void motion(int x,int y)                                                //fonction mouvement
{
    if(click==1)
    {
        x0 = x - 400;                                                   //transformer les coordonnees de la souris en coordonnes du centre
		y0 = -y + 400;

        xt=x0;
        yt=y0;
        firstRound=1;                                                   //booleen, 1=true
        redisplay=1;                                                    //booleen, 1=true
        display();                                                      //appel de la fonction affichage
    }
}

void menu(int n)                                                        //fonction menu
{
    if(click==0)
        type=n;
}
