#include <stdio.h>

typedef struct strPers Personne;
struct strPers
{
    char prenom [10];
    char patronyme [10];
    int age;
    Personne* connaissances[3];

};



void main ()

{
    Personne tab [] =
    {
    {"Marie", "PIERRE", 13,{tab+2, NULL, NULL}},
    {"Jean", "PIERRE", 46,{tab+2, tab+3, NULL}},
    {"Jean", "MARIE", 26,{tab, tab+1, tab+3}},
    {"Pierre", "LAURENT", 50,{tab+1, tab+2, NULL}}};
    int i;

        for(i=0; i<4; i++)
            afficher( tab+1, 1, "");
        //    printf("%s %s a %d ans \n", tab[i].prenom,
        //                                    tab[i].patronyme,
        //                                    tab[i].age);
}

void afficher (Personne* p
                int afficher Amis;
                char* chaineAvant);

    {
        if(p) /* if (p!=NULL) */
        {

        if (!afficher Amis) /* if (afficher Amis != 0) */
        {
            printf("%s %s %s a %d an(s) \n", chaineAvant,
                                            p -> prenom,
                                            p -> patronyme,
                                            p -> age);
        }

        else {
            printf ("%s %s %s a %d an(s) et a les amis suivants: \n", chaineAvant,
                                                                    p -> prenom,
                                                                    p -> patronyme,)
                                                                    p -> age);

                for(int a=0; a<3; a++)
                    afficher (p -> amis [a], 0, "-");

            }
        }

    }





