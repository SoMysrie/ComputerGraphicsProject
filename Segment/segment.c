#include <windows.h>
#include <GL/glut.h>
#include "segment.h"

// fonction du tracer du segment
void segment(int xa,int ya,int xb,int yb,Color color)
{
    int dx = xb-xa, dy = yb-ya; // initialisation de dx et dy qui sont les longueurs entre a et b selon l'axe
    int incX=1, incY=1;         // initialisation de l'incrémentation de x et y pour le tracé en pixels

    if(xb<xa)                   // si le point xb est inférieur au point xa, on décremente
        incX=-1;
    if(yb<ya)                   // si le point yb est inférieur au point ya, on décremente
        incY=-1;

    glBegin(GL_POINTS);                     // appel de la fonction de glut pour tracer le segment
    glColor3f(color.r,color.g,color.b);     // appel de la fonction de glut pour tracer les couleus
    if(absolute(dx)>=absolute(dy))
    {
        segmentOctant1(xa,ya,xb,yb,incX,incY,0);
    }
    else
    {
        segmentOctant1(ya,xa,yb,xb,incY,incX,1);
    }
    glEnd();
}

// fonction de l'octant
void segmentOctant1(int xa,int ya,int xb,int yb,int incX,int incY,int reverse)
{
    int dx = absolute(xb-xa), dy = absolute(yb-ya); // les longueurs dx et dy sont forcément de signe positif avec la présence d'absolu
    int incE = 2*dy, incNE = 2*(dy-dx);
    int di = 2*dy - dx;
    int x = 0, y = 0;

    y=ya;
    for(x = xa; x != xb; x += incX)
    {
        if(reverse)
            glVertex2f(y,x);
        else
            glVertex2f(x,y);
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
        glVertex2f(yb,xb);
    else
        glVertex2f(xb,yb);
}

// fonction de l'absolu, n toujours positif
int absolute(int n)
{
    if(n<0)
        return -n;
    return n;
}
