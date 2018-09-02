/*

DAMIER

+-+-+-+-+-+-+-+-+
| | | | | | | | |
+-+-+-+-+-+-+-+-+
| | | | | | | | |
+-+-+-+-+-+-+-+-+
| | | | | | | | |
+-+-+-+-+-+-+-+-+
| | | | | | | | |
+-+-+-+-+-+-+-+-+
| | | | | | | | |
+-+-+-+-+-+-+-+-+
| | | | | | | | |
+-+-+-+-+-+-+-+-+
| | | | | | | | |
+-+-+-+-+-+-+-+-+

On considÃ¨re :

 - H : la hauteur du damier (qui vaut 13)
 - L : la largeur du damier (qui vaut 15)
 - l : le numéro de ligne
 - c : le numéro de colonne

On fait varier c de 0 à 15, on constate que :

 - les colonnes paires comportent un "+" ou un "|"
 - les colonnes impaires comportent un "-" ou un " "

On fait varier l de 0 à 13, on constate que :

 - les lignes paires comportent un "+" ou un "-"
 - les lignes impaires comportent un "|" ou un " "

On combine les lignes et les colonnes, on constate que :

 - les colonnes paires et les lignes paires comportent un "+"
 - les colonnes paires et les lignes impaires comportent un "|"
 - les colonnes impaires et les lignes paires comportent un "-"
 - les colonnes impaires et les lignes impaires comportent un " "

Si on remplace "paires" par 0 et "impaires" par 1, on obtient :

 - les colonnes 0 et les lignes 0 comportent un "+"
 - les colonnes 0 et les lignes 1 comportent un "|"
 - les colonnes 1 et les lignes 0 comportent un "-"
 - les colonnes 1 et les lignes 1 comportent un " "

=> pour obtenir ce résultat, on utilise c%2 (resp. l%2) qui vaut :

 - 0 pour une colonne (resp. ligne) paire 
 - 1 pour une colonne (resp. ligne) impaire 

On peut combiner les deux bits en mettant un poids de 1 au bit des lignes et un poids de 2 au bit des colonnes, on a alors :

 - les colonnes 0 et les lignes 0 comportent un "+" => 00 = 0
 - les colonnes 0 et les lignes 1 comportent un "|" => 01 = 1
 - les colonnes 1 et les lignes 0 comportent un "-" => 10 = 2
 - les colonnes 1 et les lignes 1 comportent un " " => 11 = 3

=> pour obtenir ce résultat, on utilise (c%2)*2 + (l%2) dans un switch ... case lui-même dans 2 boucles for imbriquées.

On peut écrire l'algo >>>
PUISSANCE 4
CONSTANTE H ENTIER<-6
CONSTANTE L ENTIER<-7
VARIABLE c ENTIER
VARIABLE l ENTIER
DEBUT
POUR c DE 0 A 2H FAIRE
	POUR l DE 0 A 2L FAIRE
		CAS ((c%2)x2 + (l%2)) PARMI
			0 : AFFICHER "+"
			1 : AFFICHER "|"
			2 : AFFICHER "-"
			3 : AFFICHER " "
		FIN CAS
	FIN POUR
	LIGNE SUIVANTE()
FIN POUR
*/

#include <stdio.h>
void main ()
{
	char H = 17;
	char L = 17;
	char c = 0;
	char l = 0;

	afficher (H, L, c, l)
}

void afficher (char H, char L, char c, char l)
{
	// display column marks "manually" (because c for is not yet initiated)
	printf("   A  B  C  D  G  E  F  G");
	// return new line
	printf("\n");
	// array loop
	for (l=0; l<H; l++)
	{
		// init line marks, using l
		switch (l)
		{	
			case 0 : printf("  "); break;
			case 1 : printf("8 "); break;
			case 2 : printf("  "); break;
			case 3 : printf("7 "); break;
			case 4 : printf("  "); break;
			case 5 : printf("6 "); break;
			case 6 : printf("  "); break;
			case 7 : printf("5 "); break;
			case 8 : printf("  "); break;
			case 9 : printf("4 "); break;
			case 10 : printf("  "); break;
			case 11 : printf("3 "); break;
			case 12 : printf("  "); break;
			case 13 : printf("2 "); break;
			case 14 : printf("  "); break;
			case 15 : printf("1 "); break;
			case 16 : printf("  "); break;
		}
		// central array
		for (c=0; c<L; c++)
		{
			switch ( (c%2)*2 + (l%2) )
			{
				case 0 : printf ("+"); break;
				case 1 : printf ("|"); break;
				case 2 : printf ("--"); break;
				case 3 : printf ("  "); break; 
			}
		}
		// right-side line marks, using l
		switch (l)
		{
			case 1 : printf(" 8"); break;
			case 3 : printf(" 7"); break;
			case 5 : printf(" 6"); break;
			case 7 : printf(" 5"); break;
			case 9 : printf(" 4"); break;
			case 11 : printf(" 3"); break;
			case 13 : printf(" 2"); break;
			case 15 : printf(" 1"); break;
		}
		// next line of array
		printf ("\n");
	}
	// finish by adding manually column marks
	printf("   A  B  C  D  G  E  F  G");
	printf ("\n");
}

