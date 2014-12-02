#include <windows.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include "circle.h"

int x0,y0;
int xa,ya,xb,yb;
int xt,yt;
int empty=1,click=0,redisplay=0;
int i=0,maxi=0;
Shape shapes[500];
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
	glutCreateWindow("Cercle");

	color.r=255;
	color.g=0;
	color.b=0;

	gluOrtho2D(-400.0,400.0,-400.0,400.0);

    glClearColor(0.0, 0.0, 0.0, 0.0);
	glColor3ub(255, 255, 255);
	glPointSize(1.0);

    glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
	glutPassiveMotionFunc(motion);

    glutMainLoop();
    return 0;
}

void display()
{
    if(empty)
    {
        glClear(GL_COLOR_BUFFER_BIT);

        glBegin(GL_LINES);
        glColor3ub(255,255,255);
        glVertex2f(-400,0);
        glVertex2f(400,0);
        glVertex2f(0,-400);
        glVertex2f(0,400);
        glVertex2f(-400,400);
        glVertex2f(400,-400);
        glVertex2f(-400,-400);
        glVertex2f(400,400);
        glEnd();

        empty=0;
    }
    if(redisplay)
    {
        for(i=0;i<maxi;i++)
        {
            if(shapes[i].type==CIRCLE)
                circle(shapes[i].xa,shapes[i].ya,shapes[i].xb,shapes[i].yb,shapes[i].col);
        }
        redisplay=0;
    }
    if(click==1)
    {
        circle(xa,ya,xt,yt,color);
    }
    else if(click==2)
    {
        circle(xa,ya,xb,yb,color);

        shapes[maxi].xa=xa;
        shapes[maxi].ya=ya;
        shapes[maxi].xb=xb;
        shapes[maxi].yb=yb;
        shapes[maxi].type=CIRCLE;
        shapes[maxi].col=color;
        maxi++;
        click=0;
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
	switch (touch)
	{
    case 27:
        exit(0);
        break;
    case 'r':
        empty=1;
        maxi=0;
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

        empty=1;
        redisplay=1;
        display();
    }
}
