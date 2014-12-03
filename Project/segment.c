#include "header.h"

void segment(int xa,int ya,int xb,int yb,Color color,Shape lim)
{
    int dx=xb-xa,dy=yb-ya;
    int incX=1,incY=1;

    if(xb<xa)
        incX=-1;
    if(yb<ya)
        incY=-1;

    glBegin(GL_POINTS);
    glColor3ub(color.r,color.g,color.b);
    if(absolute(dx)>=absolute(dy))
    {
        segmentOctant1(xa,ya,xb,yb,incX,incY,0,lim);
    }
    else
    {
        segmentOctant1(ya,xa,yb,xb,incY,incX,1,lim);
    }
    glEnd();
}

void segmentOctant1(int xa,int ya,int xb,int yb,int incX,int incY,int reverse,Shape lim)
{
    int dx=absolute(xb-xa),dy=absolute(yb-ya);
    int incE=2*dy,incNE=2*(dy-dx);
    int di=2*dy-dx;
    int x=0,y=0;

    y=ya;
    for(x=xa;x!=xb;x+=incX)
    {
        if(reverse)
            plotPoint(y,x,lim);
        else
            plotPoint(x,y,lim);
        if(di<=0)
        {
            di+=incE;
        }
        else
        {
            di+=incNE;
            y+=incY;
        }
    }
    if(reverse)
        plotPoint(yb,xb,lim);
    else
        plotPoint(xb,yb,lim);
}

int absolute(int n)
{
    if(n<0)
        return -n;
    return n;
}
