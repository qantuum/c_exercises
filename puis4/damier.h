#ifndef __DAMIER__
#define __DAMIER__



// définitions des constantes (n'est pas typé -> remplace)
#define H 6
#define L 7


typedef struct 
 {
  int cpt;
  int decV;
  int decH;
  int limV;
  int limH;
 }
 Direction;


// il faut déclarer les fonctions avant la fonction main, même si on ne les remplit pas
void initialiser();
void afficher ();
int placerJeton(int nC);

void Testerfinjeu();

char getJoueurCourant();
void poserJeton (int numLigne, int numColonne);
void incrementerNbJetons ();
void changerJoueur();
char getFinDuJeu();


#endif
























