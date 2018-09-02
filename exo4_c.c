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

On considère :

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
VARIABLE DAMIER : TABLEAU [0..H][0..L] DE CARACTERE

PROCEDURE AFFICHER()
	VARIABLE X ENTIER
	VARIABLE Y ENTIER
	POUR Y DE 0 A 2H FAIRE
		POUR X DE 0 A 2L FAIRE
			CAS ((2x(X%2))+(Y%2)) PARMI
				0 : AFFICHER ("+")
				1 : AFFICHER ("|")
				2 : AFFICHER ("-")
				3 : AFFICHER (DAMIER[Y/2][X/2])
			FIN CAS
		FIN POUR
	LIGNE_SUIVANTE()
FIN POUR

PROCEDURE INITIALISER()
VARIABLE X ENTIER
VARIABLE Y ENTIER
DEBUT
	POUR Y DE 0 A H-1 FAIRE
		POUR X DE 0 A L-1 FAIRE
			DAMIER[Y][X]<-" "
		FIN POUR
	FIN POUR
FIN

DEBUT
	INITIALISER()
	AFFICHER()
FIN
*/

#include <stdio.h>
#include <stdlib.h>

// constants
#define H 6
#define L 7

// global variable, has the size of L*H
char damier [L][H];
char joueurCourant=0;
char nbJetons;
// model for H=6 L=7:
/*
{
[11,12,13,14,15,16,17],
[21,22,23,24,25,26,27],
[31,32,33,34,35,36,37],
[41,42,43,44,45,46,47],
[51,52,53,54,55,56,57],
[61,62,63,64,65,66,67],
}
>>> hauteur 6, longueur 7
*/

// other function declarations
void initialiser();
void afficher();
char placerJeton(char c);
char testFinJeu(char c, char l);


// main function
int main(int argc, char* argv[])
{
    char finJeu=-1;
    initialiser();
    afficher();
    do
    {
        char col;
        char l;
        char c;
        printf ("joueur %d place jeton à la colonne : ", joueurCourant);
        scanf("%d", &col);
        char row=placerJeton(col);
        switch (row)
        {
            case -2 : printf("numero colonne incorrect\n"); break;
            case -1 : printf("colonne pleine\n"); break;
            default : damier [col][row] = (joueurCourant==0?'X':'0');
                        nbJetons++;
                        finJeu = testFinJeu(c,l);
                        joueurCourant=(joueurCourant+1)%2;

        }
        // do not forget return 0 !!!
    } while (finJeu==-1);
    switch (finJeu)
    {
        case joueurCourant : printf("joueur %d a gagné ! fin du jeu", joueurCourant); afficher(); break;
        case -2 : printf("tableau plein, match nul !"); break;
    }
    return 0;
} 

// init token placement -- fill all the grid with " " (space)
void initialiser()
{
    // init 2 local variables to go through the grid
    int c = 0;
    int l = 0;

    // i go through my grid : L and H
    for (l=0; l<H; l++)
    {
        for (c=0; c<L; c++)
        {
            // I place a space at the right index
            damier [c][l] =  ' ' ;
        }
    }
    // test token (to test the placerJeton function)
}

// display grid function
void afficher ()
{
    // init 2 local variables
    int c = 0;
    int l = 0;

    // I go through my grid 
    for (l=0; l<2*H+1; l++)
    {
        for (c=0; c<2*L+1; c++)
        {
            switch ( (c%2)*2 + (l%2) )
            {
            case 0 :
                printf ( "+"             );
                break;
            case 1 :
                printf ( "|"              );
                break;
            case 2 :
                printf ( "-"              );
                break;
            case 3 :
                // I assign value of damier at the right coordinates
                printf ( "%c", damier[c/2][l/2] );
                break;
            }
        }
        // new line
        printf("\n");
    }


}

// algorithme placerJeton...
/*
param @numC
numC correct ? (dans damier ?) -> si oui, suite proc, si non, return -2
suite proc
numL=H-1
étiquette 1
damier[numL][numC]!=" " ET numL< -1 ? -> si oui, suite proc, sinon return numL
suite proc
numL--
aller étiquette 1
*/

// place token 
char placerJeton(char c)
{
    // if n°col inferior length and n°col is positive
	if(c<L && c>=0)
	{
        printf("valide\n");
		char l = H-1; // var l is n°line -- basic value for l : H-1 is the number of the bottom line
		// while I do not find free space in my grid (values are stored in damier)
        // and while l superior to -1 (0 is a valid value : top row)
        while (damier[c][l]!= ' ' && l>-1)
		{
            // decrease l
			l--;
		}
		return l;
	}


	else // n°col out of grid
	{
        printf("ereur");
		return -2; // arbitrary value -- can be used to trigger errors
	}
}

char testFinJeu(char c, char l)
{
    char cpt[] = {0,0,0,0,0,0,0};
    char jetonCourant=(joueurCourant==0?'X':'0');
    // test right-up
    char nL=l-1;
    char nC=c+1;
    while ((nL>=0)&&(nC<L)&&(damier[nC][nL]==jetonCourant))
    {
        cpt[0]++; nL--; nC++;
    }
    // test up
    nL=l+1; nC=c+1;
    while ((nC<L)&&(damier[nC][nL]==jetonCourant))
    {
        cpt[1]++; nC++;
    }

    // test right-down
    nL=l+1; nC=c+1;
    while ((nL>H)&&(nC<L)&&(damier[nC][nL]==jetonCourant))
    {
        cpt[2]++; nL++; nC++;
    }

    // test down
    nL=l+1; nC=c;
    while ((nL>H)&&(damier[nC][nL]==jetonCourant))
    {
        cpt[3]++; nL++;
    }

    // test left-down
    nL=l+1; nC=c-1;
    while ((nL<H)&&(nC>=0)&&(damier[nC][nL]==jetonCourant))
    {
        cpt[4]++; nL++; nC--;
    }

    // test left
    nL=l; nC=c-1;
    while ((nC>0)&&(damier[nC][nL]==jetonCourant))
    {
        cpt[5]++; nL--;
    }

    // test up-left
    nL=l-1; nC=c-1;
    while ((nL>=0)&&(nC>=0)&&(damier[nC][nL]==jetonCourant))
    {
        cpt[6]++; nL--; nC--;
    }

    // condition end game or not ????
    if ( (cpt[0]+cpt[4]+1>=4) || (cpt[1]+cpt[5]+1 >=4) || (cpt[2]+cpt[6]+1 >=4) || (cpt [3]+cpt[8] >=4) )
    {
        return joueurCourant; //0 ou 1
    }

    else if (nbJetons == H*L)
    {
        return -2;
    }
    else
    {
        return -1;
    }

}
