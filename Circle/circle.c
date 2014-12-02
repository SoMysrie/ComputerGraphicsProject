#include <windows.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "circle.h"

void circle(int xa,int ya,int xb,int yb,Color color)
{
    int x,y,dp;

    x=0;
    y=distance(xa,ya,xb,yb);
    dp=5-4*y;

    glBegin(GL_POINTS);
    glColor3ub(color.r,color.g,color.b);

    glVertex2f(x+xa,y+ya);
    glVertex2f(y+xa,x+ya);
    glVertex2f(x+xa,-y+ya);
    glVertex2f(-y+xa,x+ya);
    while(y>x)
    {
        if(dp<=0)
        {
            dp+=8*x+12;
        }
        else
        {
            dp+=8*(x-y)+20;
            y--;
        }
        x++;

        glVertex2f(x+xa,y+ya);
        glVertex2f(y+xa,x+ya);
        glVertex2f(x+xa,-y+ya);
        glVertex2f(-y+xa,x+ya);
        glVertex2f(y+xa,-x+ya);
        glVertex2f(-x+xa,-y+ya);
        glVertex2f(-y+xa,-x+ya);
        glVertex2f(-x+xa,y+ya);
    }

    glEnd();
}

int distance(int xa,int ya,int xb,int yb)
{
    double square=(xb-xa)*(xb-xa)+(yb-ya)*(yb-ya);
    int r=0;

    r=(int)pow(square,0.5);

    return r;
}
