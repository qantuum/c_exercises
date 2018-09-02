#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

typedef struct strPers Personne;

struct strPers{
    char prenom[10];
    char nom [10];
    int age;
    Personne* connaissance[3];
};

Personne* faireNaitre(char* prenom, char* nom, int age)
{
  Personne* p = (Personne*) malloc (sizeof(Personne));
    if (p){

        strcpy(p->prenom, prenom);
        strcpy(p->nom, nom);
        p->age = age;

        for (int a = 0; a < 3; a++){

            p->connaissance[a]=NULL;
        }
        return p;
    }
}

void afficher(Personne* p, int afficherAmis, char* chaineAvant){
    if (p) /*if (p != NULL)*/{

        if (!afficherAmis){

            printf("%s %s %s a %d ans \n", chaineAvant, p->prenom, p->nom, p->age);

        }else{

            printf("%s %s %s a %d ans et les amis suivants :\n", chaineAvant, p->prenom, p->nom, p->age);

            for (int a = 0; a < 3; a++){
                afficher(p->connaissance[a], NULL,"    - ");
            }
        }
    }
}

void butterPersonne(Personne** p)
{
    if (*p != NULL)
    {
        free(*p);
        *p = NULL;
    }
}

void main(){

    // pour installer utf-8 dans l'invite de cmd Windob
    SetConsoleOutputCP(65001);

    Personne* tab[4];

    tab[0] = faireNaitre("Marie", "Pierre", 13);
    tab[1] = faireNaitre("Jean", "Pierre", 46);
    tab[2] = faireNaitre("Jean", "Marie", 24);
    tab[3] = faireNaitre("Pierre", "Laurent", 50);

    for (int p = 0; p < 4; p++){

        afficher(tab[p], 1, "");
        printf("pointeur avant = %p \n", tab[p]);
        printf("%s est butté \n", tab[p]->prenom);
        butterPersonne(tab+p);
        printf("pointeur après = %p \n", tab[p]);
        afficher(tab[p], 1, "");
    }
}
