#include <stdio.h>
// méthode pour le rendu cmd de Windob
#include <windows.h>

void main()
{
    // pour installer utf-8 dans l'invite de cmd Windob
    SetConsoleOutputCP(65001);

    // dans un tableau, le pointeur alloue des adresses mémoires successives qui s'incrémentent selon le typage de la variable
    // tableau de char : adresse+1 (1o)
    // tableau de int : adresse+4 (4o)
    // ...
    int tab[] = {10, 20, 30, 40};
    int i;

    for (i=0; i<4; i++)
    {
        printf("tab[%d] = %d à l'adresse %p \n", i, tab[i], &(tab[i]));

    }
    // mise en évidence que l'adresse d'un tableau est directement liée à son nom
    // pour une variable, l'adresse est &nomDeLaVar
    // pour une tableau, l'adresse est nomDuTableau
    // pour une fonction, l'adresse est nomDeLaFonction
    printf ("&tab=%p et tab=%p \n", &tab, tab);

    // démonstation que *(tab+i) est la même chose que tab[i]
    // en effet *(tab+i) est l'adresse mémoire de tab[i]
    for (i=0; i<4; i++)
    {
        printf("*(tab+%d)=%d à l'adresse %p \n", i, *(tab+i), (tab+i));
    }
}
