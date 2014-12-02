
struct Color
{
    /// GLfloat est une variable d'OpenGL utilisée entre autre pour les couleurs
    GLfloat r;
    GLfloat g;
    GLfloat b;
};
typedef struct Color Color;
/**
Structure pour stocker une couleur à utiliser pour tracer le segment
(structure = sac de variable)
pour accéder à une sous-variable d'une structure on fait: nomvariable.nomsousvariable

Exemple avec la structure Couleur:

int main()
{
    Couleur color; //declaration d'une structure color de type Couleur, color contient donc 3 sous-variables (r,g et b)

    // modification des sous-variables de color
    color.r=0.5;
    color.g=0.6;
    color.b=0.7;
}
**/



void segment(int xa,int ya,int xb,int yb,Color color);
/**
Cette fonction prend les coordonnées des 2 extrémités du segment et fait les transformations
nécessaires (inversement de x et y,incréments ++ ou --) puis appelle segmentOctant1

Cette fonction remplace glBegin(GL_LINES), il suffit juste de l'appeller pour tracer un segment
**/

void segmentOctant1(int xa,int ya,int xb,int yb,int incX,int incY,int reverse);
/**
Trace un segment comme si on se trouvait dans le 1er Octant, le dernier paramètre permet
d'indiquer si les x et y ont été inversés, si c'est le cas il faut les reinversés pour l'affichage
**/

int absolute(int n);
/**
Renvoie la valeur absolue d'un nombre entier
**/
