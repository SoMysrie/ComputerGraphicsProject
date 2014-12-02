#ifndef HEADER
#define HEADER

#define SEGMENT 1
#define CIRCLE 2
#define RECTANLGE 3
#define WINDOW 4

#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <GL/glut.h>

struct Color
{
    GLubyte r;
    GLubyte g;
    GLubyte b;
};
typedef struct Color Color;

struct Shape
{
    int xa;
    int ya;
    int xb;
    int yb;
    int type;
    Color col;
};
typedef struct Shape Shape;

#include "segment.h"
#include "circle.h"
#include "square.h"
#include "color.h"


#endif // HEADER
