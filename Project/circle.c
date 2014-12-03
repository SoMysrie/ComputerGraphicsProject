#include "header.h"

void circle(int xa,int ya,int xb,int yb,Color color,Shape lim)
{
    int x,y,dp;

    x=0;
    y=distance(xa,ya,xb,yb);
    dp=5-4*y;

    glBegin(GL_POINTS);
    glColor3ub(color.r,color.g,color.b);

    plotPoint(x+xa,y+ya,lim);
    plotPoint(y+xa,x+ya,lim);
    plotPoint(x+xa,-y+ya,lim);
    plotPoint(-y+xa,x+ya,lim);
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

        plotPoint(x+xa,y+ya,lim);
        plotPoint(y+xa,x+ya,lim);
        plotPoint(x+xa,-y+ya,lim);
        plotPoint(-y+xa,x+ya,lim);
        plotPoint(y+xa,-x+ya,lim);
        plotPoint(-x+xa,-y+ya,lim);
        plotPoint(-y+xa,-x+ya,lim);
        plotPoint(-x+xa,y+ya,lim);
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
