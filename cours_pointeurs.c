#include <stdio.h>
// méthode pour le rendu cmd de Windob
#include <windows.h>

void main()
{
    // pour installer utf-8 dans l'invite de cmd Windob
    // SetConsoleOutputCP(65001);

    // cours sur les pointeurs et la mémoire
    char a = 'Z';
    char* p = &a; // char* représente un pointeur,le pointeur récupère l'adresse mémoire de ma variable (par ex 0x800)

    printf("la variable a contient %c à l'adresse %p\n", a, p);
    // %c contenu de la variable 'char' et %p contenu de la variable 'pointer'
    printf("la variable accédée par le pointeur %c \n", *p); // déréférence le pointeur p (récupère le contenu pointé)
    *p = 'B';
    printf("la variable accédée par le pointeur %c \n", *p);
    return 0;

}
