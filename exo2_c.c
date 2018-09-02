/*

PYRAMIDE CHELOU PAIR IMPAIR

      y
     xyx
    ooyoo
  xxxyxxx
 ooooyoooo
xxxxxyxxxxx

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
        SI i==E/2
        AFFICHER ("y")
        SINON
            SI L%2==0
            AFFICHER("o")
            SINON
            AFFICHER("x")
            FIN SI
        FIN SI
    FIN POUR
    LIGNE_SUIVANTE()
FIN POUR
FIN

*/

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
            if (i==E/2)
            {
                printf ("y");
            }
            else
            {
                if (L%2==0)
                {
            	   printf ("o");
                }
                else
                {
                    printf ("x");
                }
            }
    	}
    	printf("\n");
    }
}