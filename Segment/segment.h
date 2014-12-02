
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
