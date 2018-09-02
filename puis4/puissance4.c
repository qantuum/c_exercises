#include <stdio.h>

#define FAUX 0
#define VRAI 1

#define HAUTEUR 6
#define LARGEUR 7

char damier [HAUTEUR][LARGEUR];

int joueurCourant = 0;
int nbJetons      = 0;
int finDuJeu      = -1;

void initialiser    (        );
void afficher       (        );
int  placerJeton    ( int nC );
int  testerFinDuJeu ( int nL , 
                      int nC );


int main ( int argc , char* agrv [] )
 {
  int numLigne, numColonne;

  initialiser ();
  afficher ();

  do 
   {
    printf ("Joueur %d, donnez un numero de colonne : " , joueurCourant);
    scanf ( "%d", &numColonne );

    numLigne = placerJeton ( numColonne );

    switch (numLigne)
     {
      case -2 : printf ("Numero de colonne incorrect\n");
                break;

      case -1 : printf ("Colonne pleine\n");
                break;

      default : damier [ numLigne ][ numColonne ] = ( joueurCourant==0 ? 'X' : 'O' ); 
                nbJetons++;
                afficher ();

                finDuJeu = testerFinDuJeu ( numLigne , numColonne );

                joueurCourant = (joueurCourant+1)%2;

     }
   }
   while ( finDuJeu == -1 );

   if ( finDuJeu == 2 )
         printf ("C'est un match nul\n");
    else printf ("Le joueur %d a gagne\n", finDuJeu);

  return 0;
 }


void initialiser ()
 {
  int nL, nC;

  for ( nL = 0 ; nL < HAUTEUR ; nL++ )
   for ( nC = 0 ; nC < LARGEUR ; nC++ )
    damier [nL][nC] = '.';
 }

void afficher ()
 {
  int nL, nC;

  for ( nL = 0 ; nL < 2*HAUTEUR+1 ; nL++ )
   {
    for ( nC = 0 ; nC < 2*LARGEUR+1 ; nC++ )
     switch ( (nC%2)*2 + (nL%2) )
      {
       case 0 : printf ("+");
                break;

       case 1 : printf ("|");
                break;

       case 2 : printf ("-");
                break;

       case 3 : printf ("%c", damier [nL/2][nC/2]);
      }

    printf ("\n");
   }
 }

int  placerJeton ( int nC )
 {
  if ( nC < 0 || nC >= LARGEUR )
        {
         return -2;
        }
   else {
         int nL = HAUTEUR - 1;

         while ( nL > -1 && damier [nL][nC] != '.' )
          nL--;

         return nL;
        }
 }

typedef struct
 {
  int cpt;
  int arret;
  int decV;
  int decH;
  int limV;
  int limH;
 }
 Direction;

int testerFinDuJeu ( int nL , 
                     int nC )
 {
  Direction d [7] = {    
                      { 0 , FAUX , -1 ,  1 , 0       , LARGEUR } ,
                      { 0 , FAUX ,  0 ,  1 , 0       , LARGEUR } ,
                      { 0 , FAUX ,  1 ,  1 , HAUTEUR , LARGEUR } ,
                      { 0 , FAUX ,  1 ,  0 , HAUTEUR , 0       } ,
                      { 0 , FAUX ,  1 , -1 , HAUTEUR , 0       } ,
                      { 0 , FAUX ,  0 , -1 , 0       , 0       } ,
                      { 0 , FAUX , -1 , -1 , 0       , 0       } 
                    };

  int  dec, dir;
  char jc = ( joueurCourant == 0 ? 'X' : 'O' );

  for ( dec = 1 ; dec < 10 ; dec++)
   {
    for ( dir=0 ; dir<7 ; dir++ )
     {
      if ( 
           ( nL + dec * d[dir].decV <  d[dir].limV && d[dir].decV < 0 )           || 
           ( nL + dec * d[dir].decV >= d[dir].limV && d[dir].decV > 0 )           ||  
           ( nC + dec * d[dir].decH <  d[dir].limH && d[dir].decH < 0 )           || 
           ( nC + dec * d[dir].decH >= d[dir].limH && d[dir].decH > 0 )           ||  
           ( damier [ nL + dec * d[dir].decV ] [ nC + dec * d[dir].decH ] != jc ) || 
           ( d[dir].arret == VRAI ) 
         )
        
            d[dir].arret = VRAI; 
       else d[dir].cpt +=1;
     }
   }

  printf ("On teste si le joueur %d a gagne depuis la case L=%d,C=%d: \n" , joueurCourant, nL, nC);
  printf (" - Somme 1 : %d+%d+1=%d \n"  , d[0].cpt , d[4].cpt , ( d[0].cpt + d[4].cpt + 1 ) );
  printf (" - Somme 2 : %d+%d+1=%d \n"  , d[1].cpt , d[5].cpt , ( d[1].cpt + d[5].cpt + 1 ) );
  printf (" - Somme 3 : %d+%d+1=%d \n"  , d[2].cpt , d[6].cpt , ( d[2].cpt + d[6].cpt + 1 ) );
  printf (" - Somme 4 : %d+  1=%d \n\n" , d[3].cpt ,            ( d[3].cpt            + 1 ) );

  if ( d[0].cpt + d[4].cpt + 1 >= 4 || d[1].cpt + d[5].cpt + 1 >= 4 || d[2].cpt + d[6].cpt + 1 >= 4 || d[3].cpt + 1 >= 4 )
        return joueurCourant;
   else if ( nbJetons == HAUTEUR * LARGEUR )
              return 2;
         else return -1;
 }
