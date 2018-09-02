// ajouter bibliothèque permettant de gérer les printf et scanf
#include <stdio.h>
// ajouter bibliothèque permettant de gérer les nombres et les calculs
#include <stdlib.h>

#include "damier.h"



// fonction main
int main(int argc, char * argv[])
{
     int numLigne, numColonne;

    // je rends mes 'cases' égales à un espace
    initialiser();
    // j'affiche la première grille
    afficher();

    // dowhile -- tant que la partie est en cours
    do {
        // demande au joueur courant de mettre son jeton
        printf("joueur %d donnez une colonne", getJoueurCourant() );
        // commande pour récupérer une donnée écrite
        scanf("%d", &numColonne);
        // on place le jeton par la fonction placer
        numLigne = placerJeton(numColonne);

        // deux cas différents à cela
        switch(numLigne){
            case -2 : printf("colonne invalide\n"); break;

            case -1 : printf("colonne pleine\n"); break;

            // donne la valeur du jeton du joueur à la cellule du damier
            default : poserJeton (numLigne, numColonne);// damier[nC][nL] = (joueurCourant ==0? 'X':'O');
 
                     // printf ("nC=%d nL=%d => %c\n", nC, nL, damier[nC][nL]);


                        // on re-teste s'il y a la fin du jeu
                        Testerfinjeu();
                        // on ajoute au compte de jetons total
                        incrementerNbJetons (); // nbJetons ++;
                        // le joueur courant passe la main
                        // 0+1=1, 1%2 = 1
                        // 1+1=2, 2%2 = 0, ... -> ça fonctionne
                        changerJoueur(); //   joueurCourant = (joueurCourant + 1)%2;
                        // on réaffiche la grille avec le résultat
                        afficher();
        }

    } while(getFinDuJeu() == -1); // si fin de jeu devient différent de -1, on arrête la boucle.
    // pour arrêter la boucle il est important que la variable finDuJeu osit globale (déclarée en dehors)

    if(getFinDuJeu() == 2){
        printf("Match nul\n");
    }else{
        printf("%d gagne\n", getFinDuJeu());
    }
}

