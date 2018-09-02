#include <stdio.h>
// méthode pour le rendu cmd de Windob
#include <windows.h>

// exercice différentes personnes
// Marie PIERRE 13 ans
// Jean PIERRE 46 ans
// Pierre LAURENT 50 ans
// Jean MARIE 26 ans
typedef struct strPers Personne;

struct strPers
{
    char prenom[10];
    char patronyme[10];
    int age;
    Personne* connaissances[3];
};

void main()
{
    // pour installer utf-8 dans l'invite de cmd Windob
    SetConsoleOutputCP(65001);

    Personne tab[] =
    {
        {
            "Marie", "PIERRE", 13, {tab+2, NULL, NULL}
        },
        {
            "Jean", "PIERRE", 46, {tab+2, tab+3, NULL}
        },
        {
            "Jean", "MARIE", 26, {tab, tab+1, tab+3}
        },
        {
            "PIERRE", "LAURENT", 50, {tab+2, tab+1, NULL}
        },
        // les tableaux connaissances : exemple ; Jean MARIE connaît, bah les 3 autre
        // Maie PIERRE est à l'index tab (0)
    };

    int i;

    for (i=0; i<4 ; i++)
    {
        printf("%s %s a %d ans \n et a pour amis :", tab[i].prenom, tab[i].patronyme, tab[i].age);
        int j;
        for (j=0; j<sizeof(tab[i].connaissances); j++)
        {
            if (connaissances.j != NULL)
            {
                printf("est ami avec:: %s %s",jesaispas);
            }
        }
    }


}
