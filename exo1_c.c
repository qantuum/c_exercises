// ALGO POUR FAIRE
//    *
//   ***
//  *****
// *******

/*On considère :

 - H la hauteur du triangle : ENTIER
 - L le numéro de ligne qui va de 0 à H-1 : ENTIER
 - E le nombre d'étoile qui est égal : ENTIER
 - S le nombre d'espaces avant les étoiles : ENTIER
 - i pour les boucles : ENTIER
DEBUT
AFFICHER('Pyramide \n')
AFFICHER('=============\n\n')
AFFICHER('donner le nombre de lignes : ')
H<-CHAINE_VERS_ENTIER(LIRE())
H<-10
POUR nbLignes DE 0 à H-1, PAS 1 FAIRE
	S<-H-L-1
	E<-2*L+1
	POUR i DE 0 A S-1 FAIRE
		AFFICHER (" ")
	FIN POUR
	POUR i DE 0 A S-1 FAIRE
		AFFICHER("*")
	FIN POUR
	LIGNE_SUIVANTE()
FIN POUR
FIN


 -----------HORS-ALGO-------
On utilise l'exemple pour essayer de déterminer E et S en fonction de L et H

H vaut 7

      *       L=0 E= 1=2*0+1 S=6=6-0
     ***      L=1 E= 3=2*1+1 S=5=6-1
    *****     L=2 E= 5=2*2+1 S=4=6-2
   *******    L=3 E= 7=2*3+1 S=3=6-3
  *********   L=4 E= 9=2*4+1 S=2=6-4
 ***********  L=5 E=11=2*5+1 S=1=6-5
************* L=6 E=13=2*6+1 S=0=6-6

On en déduit que E=2*L+1 et S=H-1-L
 -----------HORS-ALGO FIN---*/

#include <stdio.h>
void main()
{
	char H = 0; // en C la variable n'a pas besoin d'être initialisée, contrairement au JAVA
	char L = 0;
	char E = 0;
	char S = 0;
	char i = 0;

	printf("\n");
	printf("Pyramide\n");
	printf("========\n");
	printf("Donnez le nombre de lignes !!!");
	scanf("%d", &H); // & est un pointeur
    for (L=0; L<H; L++)
    {
    	E = 2*L+1;
    	S = H-1-L;

    	for (i=0; i<S; i++)
    	{
        	printf (" ");
    	}

    	for (i=0; i<E; i++)
    	{
        	printf ("*");
    	}
    	printf("\n");
    }
}