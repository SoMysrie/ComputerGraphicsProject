#ifndef HEADER
#define HEADER

#include <windows.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>

#define EMPTY 0
#define SEGMENT 1

/**
Structure pour stocker une couleur à utiliser pour tracer le segment
(structure = sac de variable)
pour accéder à une sous-variable d'une structure on fait: nomvariable.nomsousvariable

Exemple avec la structure Couleur:

int main()
{
    Couleur color; //declaration d'une structure color de type Couleur, color contient donc 3 sous-variables (r,g et b)

    // modification des sous-variables de color
    color.r=120;
    color.g=121;
    color.b=122;
}
**/

struct Color
{
    /// GLubyte est une variable d'OpenGL utilisée entre autre pour les couleurs (c'est un int allant de 0 à 255
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
    Color color;
};
typedef struct Shape Shape;

#include "segment.h"

#endif // HEADER
