// ajouter bibliothèque permettant de gérer les printf et scanf
#include <stdio.h>
// ajouter bibliothèque permettant de gérer les nombres et les calculs
#include <stdlib.h>

// définitions des constantes (n'est pas typé -> remplace)
#define H 6
#define L 7

// variables GLOBALES
int nbJetons;
char joueurCourant;
char damier [L][H]; // tableau de dimensions L et H
int nL; // n° lignes
int nC; // n° colonnes
char finDuJeu;
// il faut déclarer les fonctions avant la fonction main, même si on ne les remplit pas
int placerJeton(int nC);
char Testerfinjeu();

// fct initialiser, rend toutes mes 'cases' du tableau égales à un espace
void initialiser()
{
    // variables temporaires pour parcourir les for
    int c = 0;
    int l = 0;

    // parcourir les lignes sur la hauteur
    for (l=0; l<H; l++)
    {
        // parcourir les colonnes sur la longueur
        for (c=0; c<L; c++)
        {
            // assigner un espace à toutes les "cases" du tableau
            damier [c][l] =  ' ' ;
        }
    }
}

// fct afficher, affiche ma grille
void afficher ()
{
    // variables temporaires pour parcourir les for
    int c = 0;
    int l = 0;

    // parcourir les lignes sur la hauteur
    for (l=0; l<2*H+1; l++)
    {
        // parcourir les colonnes sur la longueur
        for (c=0; c<2*L+1; c++)
        {
            // algo : poids binaire correspondant à mes match ligne*colonnes
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
                // placer le contenu de ma variable damier (définie dans initialiser) -- on met c/2 et l/2 car on parcourt jusqu'à 2L+1 et 2H+1
                printf ( "%c", damier[c/2][l/2] );
                break;
            }
        }
        // on va à la ligne
        printf("\n");
    }
}

// fonction main
int main(int argc, char * argv[])
{
    // je rends mes 'cases' égales à un espace
    initialiser();
    // j'affiche la première grille
    afficher();

    // dowhile -- tant que la partie est en cours
    do {
        // demande au joueur courant de mettre son jeton
        printf("joueur %d donnez une colonne", joueurCourant);
        // commande pour récupérer une donnée écrite
        scanf("%d", &nC);
        // on place le jeton par la fonction placer
        nL = placerJeton(nC);

        // deux cas différents à cela
        switch(nL){
            case -2 : printf("colonne invalide\n"); break;

            case -1 : printf("colonne pleine\n"); break;

            // donne la valeur du jeton du joueur à la cellule du damier
            default : damier[nC][nL] = (joueurCourant ==0? 'X':'O');
                        // on re-teste s'il y a la fin du jeu
                        finDuJeu = Testerfinjeu(); 
                        // on ajoute au compte de jetons total
                        nbJetons ++;
                        // le joueur courant passe la main
                        // 0+1=1, 1%2 = 1
                        // 1+1=2, 2%2 = 0, ... -> ça fonctionne
                        joueurCourant = (joueurCourant + 1)%2;
                        // on réaffiche la grille avec le résultat                    
                        afficher();     
        }

    } while(finDuJeu == -1); // si fin de jeu devient différent de -1, on arrête la boucle.
    // pour arrêter la boucle il est important que la variable finDuJeu osit globale (déclarée en dehors)

    if(finDuJeu == 2){
        printf("Match nul\n");
    }else{
        printf("%d gagne\n", finDuJeu);
    }
}

// algorithme pour tester à chaque action joueur, si le joueur gagne
char Testerfinjeu(){

    // var compte, compte dans les directions
    int cpt[] = {0,0,0,0,0,0,0};
    // jeton du joueur courant
    char jetonCourant = (joueurCourant==0? 'X':'O');
    int nLigne = nL;
    int nCol = nC;

    // test haut-droite
    while((nLigne >= 0) && (nCol < L) && (damier[nCol][nLigne] == jetonCourant)){
        cpt[0]++;
        nLigne--;
        nCol ++;
    }

    // test haut
    nLigne = nL;
    nCol = nC+1;

    while((nCol < L) && (damier[nCol][nLigne] == jetonCourant)){

        cpt[1]++;
        nCol++;
    }

    // test bas-droite
    nLigne = nL+1;
    nCol = nC+1;

    while((nLigne < H) && (nCol < L) && (damier[nCol][nLigne] == jetonCourant)){

        cpt[2]++;
        nLigne++;
        nCol++;
    }

    // test bas
    nLigne = nL+1;
    nCol = nC;

    while((nLigne < H) && (damier[nCol][nLigne] == jetonCourant)){

        cpt[3]++;
        nLigne++;
    }

    // test gauche-bas
    nLigne = nL+1;
    nCol = nC-1;

    while((nLigne < H) && (nCol >= 0) && (damier[nCol][nLigne] == jetonCourant)){

        cpt[4]++;
        nLigne++;
        nCol--;
    }

    // test gauche
    nLigne = nL;
    nCol = nC-1;

    while((nCol >= 0) && (damier[nCol][nLigne] == jetonCourant)){

        cpt[5]++;
        nCol--;
    }

    // test haut-gauche
    nLigne = nL-1;
    nCol = nC-1;

    while((nLigne >= 0) && (nCol >= 0) && (damier[nCol][nLigne] == jetonCourant)){

        cpt[6]++;
        nLigne--;
        nCol--;
    }

    //  test dans les deux directions
    if((cpt[0] + cpt[4] >=4) || // diagonale montante (ne marchait pas en ajoutant +1 !!!)
        (cpt[1] + cpt[3] +1 >=4) || // verticale
        (cpt[2] + cpt[6] +1 >=4) || // diagonale descendante 
        (cpt[5] +1 >=4)) // horizontale (droite par déduction donc pas besoin de recompter)
    {

        return joueurCourant; // joueur qui gagne


    } else if(nbJetons == H*L) { // jeu nul, toutes les cases sont occupées

        return 2;
        
    
    } else { // continuer jeu (boucle)

        return -1;
    }

}

// place le jeton avec un argument n° colonne fourni
int placerJeton(int nC){

    int nL;

    // si n° colonne inférieur à 0 ou supérieur à la longueur du tableau
    if ( nC < 0 || nC >= L){
        
        return -2; // code d'erreur
    }
    else{

        nL = H-1; // nouvelle variable n° ligne
 
        while(nL > -1 && damier[nC][nL] != ' '){

            nL --; // on part de bas en haut pour ce test

        }

        
    }
        return (nL); // on obtient un n° de ligne pour les coordinnées du jeton

}

