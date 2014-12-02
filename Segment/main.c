#include "header.h"

Shape shapes[100];
int i=0,maxi=0;
int xa,ya,xb,yb,inc,xt,yt;
int x0,y0;
int firstRound=1,click=0,redisplay=0;
Color color;

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
	glutCreateWindow("Segments");

	color.r=255;
    color.g=0;
    color.b=0;

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
    if(firstRound)
    {
        glClear(GL_COLOR_BUFFER_BIT);

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

        firstRound=0;
    }
    if(redisplay)
    {
        for(i=0;i<maxi;i++)
        {
            if(shapes[i].type==SEGMENT)
                segment(shapes[i].xa,shapes[i].ya,shapes[i].xb,shapes[i].yb,shapes[i].color);
        }

        redisplay=0;
    }
    if(click==2)
    {
        segment(xa,ya,xb,yb,color);

        shapes[maxi].color=color;
        shapes[maxi].type=SEGMENT;
        shapes[maxi].xa=xa;
        shapes[maxi].xb=xb;
        shapes[maxi].ya=ya;
        shapes[maxi].yb=yb;
        maxi++;
        click=0;
    }
    else if(click==1)
    {
        segment(xa,ya,xt,yt,color);
    }

    glFlush();
}

void mouse(int button,int state,int x,int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		x0 = x - 400;
		y0 = -y + 400;
		if(click==0)
        {
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
        firstRound=1;
        break;
    case 'a':
        redisplay=1;
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
