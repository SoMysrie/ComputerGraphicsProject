#include "header.h"

void changeColor(Color *color)
{
    printf("Nouvelle couleur:\n");
    inputInt("R: ",&(color->r),0,255);
    inputInt("G: ",&(color->g),0,255);
    inputInt("B: ",&(color->b),0,255);

    system("cls");
    printf("La couleur a ete modifie\n\n");
    displayColor(*color);
}

void inputInt(char text[],int *n,int lb,int lh)
{
    printf("%s",text);
    while(scanf("%d",n)!=1 || *n<lb||*n>lh)
    {
        printf("La valeur doit etre entiere et comprise entre %d et %d inclus\n\n",lb,lh);
        printf("%s",text);
        fflush(stdin);
    }
    fflush(stdin);
}

void displayColor(Color color)
{
    printf("Couleur actuelle:\nR: %d\nG: %d\nB: %d\n\n",color.r,color.g,color.b);
}
