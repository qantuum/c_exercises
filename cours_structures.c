#include <stdio.h>
// méthode pour le rendu cmd de Windob
#include <windows.h>

// une structure peut intégrer des données de typages variés (c'est comme un array multi-typage o0)
struct strTest
    {
        char a;
        int b;
        double c;
    };

void main()
{
    // pour installer utf-8 dans l'invite de cmd Windob
    SetConsoleOutputCP(65001);


       struct strTest x = {'A', 10, 30.4};
       struct strTest* y = &x;
        // même concept que pour les arrays. élément [0] de la structure est à la même adresse que le nom de ma structure
        // imprévisible sur certaines architectures
        // en effet parfois un "padding" de bourrage est ajouté, exemple passage de char à int donne 3o vides
        // sur ORDI MAISON (windows 10 et code::blocks) ce n'est pas le cas, char reste sur 1o
       printf("X est à l'adresse %p et occuppe %u octets \n", &x, sizeof(x));
       printf("X.a vaut %c et est à l'adresse %p et occuppe %u octets \n", x.a, &(x.a), sizeof(x.a));
       printf("X.b vaut %d et est à l'adresse %p et occuppe %u octets \n", x.b, &(x.b), sizeof(x.b));
       printf("X.c vaut %lf  et est à l'adresse %p et occuppe %u octets \n", x.c, &(x.c), sizeof(x.c));

       printf("X.a vaut %c, (*y).a vaut %c et y->a vaut %c \n", x.a, (*y).a, y->a);
       printf("X.b vaut %d, (*y).b vaut %d et y->b vaut %d \n", x.b, (*y).b, y->b);
       printf("X.c vaut %lf, (*y).c vaut %lf et y->c vaut %lf \n", x.c, (*y).c, y->c);
}
