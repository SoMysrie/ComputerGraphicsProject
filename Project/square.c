#include "header.h"

void square(int xa,int ya,int xb,int yb,Color color,Shape lim)
{
    segment(xa,ya,xb,ya,color,lim);
    segment(xa,yb,xb,yb,color,lim);
    segment(xa,ya,xa,yb,color,lim);
    segment(xb,ya,xb,yb,color,lim);
}

int inWindow(int x,int y,Shape lim)
{
    int inter;

    if(lim.xa>lim.xb)
    {
        inter=lim.xa;
        lim.xa=lim.xb;
        lim.xb=inter;
    }
    if(lim.ya>lim.yb)
    {
        inter=lim.ya;
        lim.ya=lim.yb;
        lim.yb=inter;
    }

    if(x>=lim.xa&&x<=lim.xb&&y>=lim.ya&&y<=lim.yb)
        return 1;
    return 0;
}

void orderSquare(Shape *lim)
{
    int inter;

    if(lim->xa>lim->xb)
    {
        inter=lim->xa;
        lim->xa=lim->xb;
        lim->xb=inter;
    }
    if(lim->ya>lim->yb)
    {
        inter=lim->ya;
        lim->ya=lim->yb;
        lim->yb=inter;
    }
}

int plotPoint(int x,int y,Shape lim)
{
    if(inWindow(x,y,lim))
        glVertex2f(x,y);
}
