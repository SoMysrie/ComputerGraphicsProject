#define CIRCLE 2

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

void circle(int xa,int ya,int xb,int yb,Color color);
int distance(int xa,int ya,int xb,int yb);
