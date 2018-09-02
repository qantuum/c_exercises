// ALGORITHME variable
// VARIABLE
// x : boolean
// y : char
// z : int
// w : float (nbr réel)
// h : string
// DEBUT
// x<-true
// y<-a
// z<-0
// FIN
// AFFICHER(BOOLEEN_VERS_CHAINE(X)) -- transtypage -- fait par JAVA à notre insu
// AFFICHER(CARACTERE_VERS_CHAINE(Y))
// ... ...
// FIN

#include <stdio.h>
void main()
{
	_bool x; // _bool, car à la création du langage le booléen a été créé deux fois, c'est une des spécificités du C
	unsigned char y; // 0 - 255 (code ASCII) -- y=65 ou y='a' marchent indifféremment
	// wchar - dépend du compilateur, par ex UNICODE
	// char peut être utilisé comme un entier (prend moins de mémoire : 1o)
	unsigned char y1;
	char y2; // 1o -> signé : peut être nombre négatif -> -128 - 127 -> centré sur 0
	unsigned short y3; // 2o -> petit nombre, occupe 2o -> 0 - 65535
	short y4; // 2o -> avec les négatifs, centré sur 0 -> de -2^15 à (2^15-1)
	unsigned long y5; // 4o -> gros nombre allant entre 0 - (2^32-1)
	long y6; // 4o -> gros nombre centré sur 0 : -2^31 à (2^31-1)
	unsigned long long y7; // 8o -> 0 - (2^64-1)
	long long y8; // 8o -> -2^63 - (2^63-1)
	unsigned int y9; // ancienne archi (32bits) -> 2o | archi (64 bits) -> 4o
	// le type int est un peu bâtard... préférer les autres
	printf(sizeof(int)); // permet de retourner la taille en octets d'un entier, par ex...
	float w1; // 4o
	double w2; // 8o
	long double w3; // 10o
	char* h1; // chaîne de caractères -- non-modifiable (constante)
	char h2[]; // chaine de caractères -- modifiable

	// structures de contrôles parailles que JAVA ou PHP

}

// pour les constantes symboliques
// on remplace du texte
// # define H 6 -> remplace chaque appel de "H" par 6

// une autre manière
// const int H = 6; (utilise de la mémoire pour le stocker)

// tab : TABLEAU[0....INDICE FIN] DE ENTIER
// C : int tab [INDICE FIN]