#include <stdio.h>
// m�thode pour le rendu cmd de Windob
#include <windows.h>

void main()
{
    // pour installer utf-8 dans l'invite de cmd Windob
    // SetConsoleOutputCP(65001);

    // cours sur les pointeurs et la m�moire
    char a = 'Z';
    char* p = &a; // char* repr�sente un pointeur,le pointeur r�cup�re l'adresse m�moire de ma variable (par ex 0x800)

    printf("la variable a contient %c � l'adresse %p\n", a, p);
    // %c contenu de la variable 'char' et %p contenu de la variable 'pointer'
    printf("la variable acc�d�e par le pointeur %c \n", *p); // d�r�f�rence le pointeur p (r�cup�re le contenu point�)
    *p = 'B';
    printf("la variable acc�d�e par le pointeur %c \n", *p);
    return 0;

}
