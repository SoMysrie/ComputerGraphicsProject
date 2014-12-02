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

Shape shapes[100],lim;
int i=0,maxi=0;
int xa,ya,xb,yb,inc,xt,yt;
int x0,y0;
int firstRound=1,click=0,redisplay=0,type=SEGMENT,axes=0;
Color color;
HWND hwndConsole,hwndFenetre;

void display(void);
void keyboard(unsigned char touch,int x,int y);
void mouse(int button,int state,int x,int y);
void motion(int x,int y);

int main(int argc,char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 800);
	glutInitWindowPosition (100, 100);
	glutCreateWindow("Project");

	color.r=255;
    color.g=0;
    color.b=0;
    displayColor(color);
    hwndConsole=GetForegroundWindow();

    lim.xa=-401;
    lim.ya=-401;
    lim.xb=401;
    lim.yb=401;
    lim.col=color;

	gluOrtho2D(-400.0,400.0,-400.0,400.0);

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glColor3f(1.0, 0.0, 0.0);
	glPointSize(1.0);

	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutPassiveMotionFunc(motion);
	glutMotionFunc(motion);

	glutMainLoop();
	return 0;
}

void display(void)
{
    hwndFenetre=GetForegroundWindow();
    if(firstRound)
    {
        glClear(GL_COLOR_BUFFER_BIT);

        if(axes)
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
    if(redisplay)
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

            shapes[maxi].type=type;
            shapes[maxi].col=color;
            shapes[maxi].xa=xa;
            shapes[maxi].xb=xb;
            shapes[maxi].ya=ya;
            shapes[maxi].yb=yb;
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

void mouse(int button,int state,int x,int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
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
		display();
	}
}

void keyboard(unsigned char touch,int x,int y)
{
    switch(touch)
    {
    case 27:  // Code ASCII de la touche Echap
        exit(0);
        break;
    case 'r':
        maxi=0;
        click=0;
        lim.xa=-401;
        lim.ya=-401;
        lim.xb=401;
        lim.yb=401;
        firstRound=1;
        break;
    case 's':
        if(click==0)
            type=SEGMENT;
        break;
    case 'c':
        if(click==0)
            type=CIRCLE;
        break;
    case 'a':
        if(click==0)
            type=RECTANLGE;
        break;
    case 'f':
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
    case 'o':
        if(!axes)
            axes=1;
        else
            axes=0;
            firstRound=1;
            redisplay=1;
        break;
    case 'p':
        SetForegroundWindow(hwndConsole);
        changeColor(&color);
        hwndConsole=GetForegroundWindow();
        SetForegroundWindow(hwndFenetre);
        hwndFenetre=GetForegroundWindow();
        break;
    }
    display();
}

void motion(int x,int y)
{
    if(click==1)
    {
        x0 = x - 400;
		y0 = -y + 400;

        xt=x0;
        yt=y0;
        firstRound=1;
        redisplay=1;
        display();
    }
}
