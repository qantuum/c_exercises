#include <stdio.h>
// méthode pour le rendu cmd de Windob
#include <windows.h>

void fct(char* v);

void main()
{
    // pour installer utf-8 dans l'invite de cmd Windob
    SetConsoleOutputCP(65001);

    // var declaration
    char a = 'Z';
    char i = 45;
    float j = 20;
    double k = 30.4;

    // pointer declaration
    char* pa = &a;
    char* pi = &i;
    float* pj = &j;
    double* pk = &k;

    printf("a contient %c et occuppe %u octets à l'adresse %p \n", a, sizeof(a), pa);
    printf("i contient %c et occuppe %u octets à l'adresse %p \n", i, sizeof(i), pi);
    printf("j contient %f et occuppe %u octets à l'adresse %p \n", j, sizeof(j), pj);
    printf("k contient %lf et occuppe %u octets à l'adresse %p \n", k, sizeof(k), pk);

    printf("pa contient %u octets \n", sizeof(pa));
    printf("pi contient %u octets \n", sizeof(pi));
    printf("pj contient %u octets \n", sizeof(pj));
    printf("pk contient %u octets \n", sizeof(pa));

    // ici on constate que les instances de ma variable b (dedans et dehors fonction) occupent des adresses mémoire différentes !
    char b = 'B';
    printf("b contient %c à l'adresse %p\n", b, &b);
    fct(&b);
    printf("b contient %c à l'adresse %p\n", b, &b);

}

void fct (char* v)
{
    printf("dans fct, *v contient %c à l'adresse %p\n", *v, &v);
    *v = *v+1;
    printf("dans fct, *v contient %c à l'adresse %p\n", *v, &v);
}
