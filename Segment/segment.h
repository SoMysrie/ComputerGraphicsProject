
void segment(int xa,int ya,int xb,int yb,Color color);
/**
Cette fonction prend les coordonn�es des 2 extr�mit�s du segment et fait les transformations
n�cessaires (inversement de x et y,incr�ments ++ ou --) puis appelle segmentOctant1

Cette fonction remplace glBegin(GL_LINES), il suffit juste de l'appeller pour tracer un segment
**/

void segmentOctant1(int xa,int ya,int xb,int yb,int incX,int incY,int reverse);
/**
Trace un segment comme si on se trouvait dans le 1er Octant, le dernier param�tre permet
d'indiquer si les x et y ont �t� invers�s, si c'est le cas il faut les reinvers�s pour l'affichage
**/

int absolute(int n);
/**
Renvoie la valeur absolue d'un nombre entier
**/
