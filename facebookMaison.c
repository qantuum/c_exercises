#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct strPers Personne;

struct strPers
 {
  char*      prenom;        /* Un champ de type "chaine de caracteres" qui contient le prenom de la personne               */
  char*      patronyme;     /* Un champ de type "chaine de caracteres" qui contient le nom de famille de la personne       */
  int        age;           /* Un champ de type "entier" qui contient l'age de la personne                                 */
  Personne** contacts;      /* Un champ de type "pointeur vers un pointeur de Personne" => ce champ peut etre vu           */
                            /* comme un tableau de taille indefini, dont chaque case contient un pointeur sur une personne */
  int        nbContacts;    /* Un champ de type "entier" qui contient le nombre de contacts de la personne, autrement dit  */
                            /* la taille du tableau "contacts"                                                             */
 };

/* Cette fonction va construire, de facon dynamique ( avec malloc ), une instance de Personne    */
/* Elle prend, en parametre, les caracteristiques de la personne afin de renseigner le different */ 
/* champ de la structure associee au type Personne                                               */
/* Elle renvoie un pointeur sur l'instance de Personne ou NULL (en cas d'echec)                  */

Personne* faireNaitrePersonne ( char* _prenom     ,
                                char* _patronyme  ,
                                int   _age        ,
                                int   _nbContacts );

/* Cette fonction va supprimer de la memoire toutes les informations relatives a la personne designee */
/* en parametre.                                                                                      */

/* On passe un parametre de type "Personne**" qui peut etre interprete comme "un pointeur sur un      */
/* pointeur de Personne" : cela permet de modifier la valeur de ce pointeur (pour le mettre a NULL)   */
/* en affectant le pointeur original (passage par adresse d'une variable de type Personne*)           */

void fumerPersonne ( Personne** p );

void afficherPersonne ( Personne* p            ,
                        int       afficherAmis ,
                        char*     chaineAvant  );

void brancherPersonne ( Personne* p1 ,
                        Personne* p2 );

void ajouterContact ( Personne* p       ,
                      Personne* pAjoute );

void debrancherPersonne ( Personne* p1 ,
                          Personne* p2 );

void supprimerContact ( Personne* p          ,
                        Personne* pSupprimer );

/* Lorsqu'on lance un programme, notamment depuis la ligne de commande, on peut lui passer des parametres pour controler le        */
/* fonctionnement du programme. Ces parametres peuvent etre recuperes grace a "argc" et "argv" qui sont renseignes automatiquement */

/* Exemple : on lance le programme en ecrivant "./facebookMaison Langue FRANCAIS"                                                  */
/*               argc    vaut 3                                                                                                    */
/*               argv[0] vaut "facebookMaison"                                                                                     */
/*               argv[1] vaut "Langue"                                                                                             */
/*               argv[2] vaut "FRANCAIS"                                                                                           */

int main ( int argc , char* argv [] )
 {
  Personne* personnes [4];

            personnes [0] = faireNaitrePersonne ( "Marie"  , "PIERRE"  , 16 , 3 );
            personnes [1] = faireNaitrePersonne ( "Jean"   , "MARIE"   , 26 , 3 );
            personnes [2] = faireNaitrePersonne ( "Pierre" , "LAURENT" , 46 , 3 );
            personnes [3] = faireNaitrePersonne ( "Jean"   , "PIERRE"  , 50 , 3 );

  for ( int i = 0 ; i<4 ; i++ )
   {
    printf ( "Pointeur sur la personne %d : %p \n" , i , personnes[i] );
   }

  printf ("\nAvant l'interconnexion des amis\n\n");

  for ( int i = 0 ; i<4 ; i++ )
   {
    afficherPersonne ( personnes [i] , 1 , "" );
   }

  for ( int i = 0 ; i<4 ; i++ )
   {
    for ( int j = 0 ; j<4 ; j++ )
     {
      if ( i == j )
       continue;

      brancherPersonne ( personnes [i] , personnes [j] );
     } 
   } 

  printf ("\nApres l'interconnexion des amis\n\n");


  for ( int i = 0 ; i<4 ; i++ )
   {
    afficherPersonne ( personnes [i] , 1 , "" );
   }

  for ( int i = 0 ; i<4 ; i++ )
   {
    fumerPersonne ( personnes + i );
   }

  printf ("\n");

  for ( int i = 0 ; i<4 ; i++ )
   {
    printf ( "Pointeur sur la personne %d : %p \n" , i , personnes[i] );
   }

  return 0;
 }

Personne* faireNaitrePersonne ( char* _prenom     ,
                                char* _patronyme  ,
                                int   _age        ,
                                int   _nbContacts )
 {
  Personne* p = ( Personne* ) malloc ( sizeof ( Personne ) );

  /* On doit d'abord verifier que p est different du pointeur NULL avant de l'utiliser (c'est-a-dire le dereferencer). */
  /* Si on utilise le pointeur NULL (si on dereference le pointeur NULL), le programme plante.                         */

  if ( p )  /* On peut aussi ecrire "if ( p != NULL )" */
   {
    /* On doit d'abord creer la zone de memoire dans laquelle on va stocker le prenom de la personne.           */
    /* On utilise la fonction strlen (definie dans string.h) pour recuperer le nombre de lettre dans le prenom. */
    /* On ajoute "+ 1" afin de tenir compte du "\0" qui termine une chaine de caractere (et qui n'est pas       */
    /* comptabilise par strlen                                                                                  */

    p->prenom = ( char* ) malloc ( strlen ( _prenom ) + 1 );

    if ( p->prenom )  /* Comme il est d'usage, on verifie si l'adresse retournee par malloc n'est pas NULL */
     {
      /* On copie le contenu du parametre "_prenom" dans la zone de memoire pointee par p->prenom                       */
      /* Il est fortement deconseille de faire "p->prenom = _prenom" car "_prenom" est une variable locale qui se situe */
      /* dans la pile => elle sera "detruite" quand la fonction aura terminee son execution et la zone de memoire       */
      /* verra ulterieurement son contenu remplace par d'autres information                                             */

      strcpy ( p->prenom , _prenom );
     }

    /* On effectue le meme traitement que precedemment mais avec le champ "patronyme" et le parametre "_patronyme" */

    p->patronyme = ( char* ) malloc ( strlen ( _patronyme ) + 1 );

    if ( p->patronyme )
     {
      strcpy ( p->patronyme , _patronyme );
     }

    /* On affecte la valeur du parametre "_age" au champ "age" de la personne pointee par "p" */

    p->age = _age;

    /* On cree un tableau dont la taille correspond a "nbContacts" et dont chaque case contient un pointeur sur Personne    */
    /* On recupere la taille d'un pointeur sur une personne en faisant "sizeof ( Personne )" puis on mulitplie cette valeur */
    /* par "_nbContacts", ce qui donne le nombre d'octets a allouer dans le tas (le parametre de "malloc")                  */

    p->contacts = ( Personne** ) malloc ( sizeof ( Personne* ) * _nbContacts );

    if ( p->contacts )
     {
      /* Si on utilise une norme recente du langage C, on peut declarer une variable d'iteration dans une boucle for */
      /* Si on compile en ligne de commmande, on doit ajouter l'argument "-std=c99"                                  */

      /* On initialise chaque case du tableau des contacts de la personne à NULL                                     */

      for ( int c = 0 ; c < _nbContacts ; c++ )
       {
        p->contacts [c] = NULL;
       } 
     }

    p->nbContacts = _nbContacts;
   }

  return p;
 }

void fumerPersonne ( Personne** p )
 {
  /* On verifie que la personne existe bien */

  if ( *p )
   {
    /* On doit d'abord supprimer les zones de memoire "filles" avant de supprimer la zone de memoire principale */

    /* Avant de supprimer le tableau, il faut le parcourir avant de "debrancher" les deux personne        */
    /* Si on omet cette etape, les autres personnes conserveront le pointeur vers une personne supprimee  */
    /* dans leur tableau des contacts                                                                     */

    while ( (*p)->nbContacts )
     {
      debrancherPersonne ( *p , (*p)->contacts [0] );
     }

    /* On verifie que la zone permettant de stocker le tableau des contacts existe */

    if ( (*p)->contacts )
     {
      free ( (*p)->contacts );  /* On supprime la zone de memoire contenant le tableau des contacts */
     }

    printf ("\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>%s %s est mort (RIP)\n", (*p)->prenom, (*p)->patronyme);

    /* On verifie que la zone permettant de stocker le prenom existe */

    if ( (*p)->prenom )
     {
      free ( (*p)->prenom );  /* On supprime la zone de memoire contenant le prenom */
     }

    /* On verifie que la zone permettant de stocker le patronyme existe */

    if ( (*p)->patronyme )
     {
      free ( (*p)->patronyme );  /* On supprime la zone de memoire contenant le patronyme */
     }

    /* On peut (enfin) supprimer l'instance de Personne (la structure principale) de la memoire */
 
    free ( *p );

    /* On affecte NULL au pointeur */

    *p = NULL;
   }
 }

void afficherPersonne ( Personne* p            ,      /* Le pointeur vers la personne a afficher */
                        int       afficherAmis ,      /* Un entier, utilise comme boolen, pour indiquer si on veut afficher la liste des amis de la personne */
                        char*     chaineAvant  )      /* Une chaine de caracteres ecrite avant les caracteristiques de la personne */
 {
  if ( p )
   {
    printf ( "%s%s %s a %d an%s" ,   chaineAvant               ,
                                       p->prenom                 ,
                                       p->patronyme              ,
                                       p->age                    ,
                                     ( p->age > 1   ? "s" : "" ) );

    if ( afficherAmis )
          {
           if ( p->nbContacts == 0 )
                 {
                  printf ( " et n'a aucun ami (sic)\n");
                 }
            else {
                  printf ( " et a %d ami%s : \n" ,   p->nbContacts                    ,
                                                   ( p->nbContacts > 1   ? "s" : "" ) );

                  for ( int c = 0 ; c < p->nbContacts ; c++ )
                   {
                    afficherPersonne ( p->contacts [c] , 
                                       0               ,
                                       "   - "         );
                   }
                 }
          }
     else {
           printf ("\n");
          }
   }
 }


void brancherPersonne ( Personne* p1 ,
                        Personne* p2 )
 {
  if ( p1 && p2 )
   {
    ajouterContact ( p1 , p2 );
    ajouterContact ( p2 , p1 );
   }
 }

void ajouterContact ( Personne* p       ,
                      Personne* pAjoute )
 {
  if ( p && pAjoute )
   {
    int pasEncoreAjoute =  1;
    int indiceAjout     = -1;

    for ( int c = 0 ; c < p->nbContacts ; c++ )
     {
      if ( p->contacts [c] )
            {
             if ( p->contacts [c] == pAjoute )
              {
               pasEncoreAjoute = 0;
               break;
              }
            }
       else {
             if ( indiceAjout == -1 )
              {
               indiceAjout = c;
              }
            }
     }

    if ( pasEncoreAjoute )
     {
      if ( indiceAjout != -1 )
       {
        p->contacts [indiceAjout] = pAjoute;
       }
     }
   }
 }

void debrancherPersonne ( Personne* p1 ,
                          Personne* p2 )
 {
  if ( p1 && p2 )
   {
    printf ("\nOn debranche %s %s et %s %s\n", p1->prenom    ,
                                               p1->patronyme ,
                                               p2->prenom    ,
                                               p2->patronyme );

    supprimerContact ( p1 , p2 );
    supprimerContact ( p2 , p1 );
   }
 }


void supprimerContact ( Personne* p          ,
                        Personne* pSupprimer )
 {
  if ( p && pSupprimer )
   {
    printf ("\n  -> %s %s supprime %s %s de son carnet de contacts\n\n", p->prenom             ,
                                                                         p->patronyme          ,
                                                                         pSupprimer->prenom    ,
                                                                         pSupprimer->patronyme );

    for ( int c = 0 ; c < p->nbContacts ; c++ )
     {
      if ( p->contacts [c] == pSupprimer )
       {
        for ( int c2 = c+1 ; c2 < p->nbContacts ; c2++ )
         {
          p->contacts [c2-1] = p->contacts [c2];
         }

        p->contacts [p->nbContacts-1] = NULL;

        break;
       }
     }

    for ( int c = 0 ; c < p->nbContacts ; c++ )
     {
      printf ("      - contact %d : %s %s\n", c                                                          ,
                                              ( p->contacts [c] ? p->contacts [c]->prenom    : "AUCUN" ) ,
                                              ( p->contacts [c] ? p->contacts [c]->patronyme : ""      ) );
     }
  
    p->nbContacts -= 1;

    printf ("\n");

    afficherPersonne ( p , 1 , "");
   }
 }



/*******************************************************************************************************************************************************************/
/* Voila ce qu'il se passe en memoire                                                                                                                              */
/*                                                                                                                                                                 */
/*             |                                                                                                       |                                           */
/*             |                                                                                                       |                                           */
/*             +-------------------------------------------------------------------------------------------------------+                                           */
/*             |                                                                                                       |  <------ Personne* tab [4];               */
/*  +------------ Adresse de la structure decrivant Marie PIERRE dans le tas                                           |                                           */
/*  |          |                                                                                                       |                                           */
/*  |          +-------------------------------------------------------------------------------------------------------+                                           */
/*  |          |                                                                                                       |                                           */
/*  | +---------- Adresse de la structure decrivant Jean MARIE dans le tas                                             |                                           */
/*  | |        |                                                                                                       |                                           */
/*  | |        +-------------------------------------------------------------------------------------------------------+                                           */
/*  | |        |                                                                                                       |                                           */
/*  | | +-------- Adresse de la structure decrivant Pierre LAURENT dans le tas                                         |                                           */
/*  | | |      |                                                                                                       |                                           */
/*  | | |      +-------------------------------------------------------------------------------------------------------+                                           */
/*  | | |      |                                                                                                       |                                           */
/*  | | | +------ Adresse de la structure decrivant Jean PIERRE dans le tas                                            |                                           */
/*  | | | |    |                                                                                                       |                                           */
/*  | | | |    +-------------------------------------------------------------------------------------------------------+                      +---------+          */
/*  | | | |    |                                                                                                       |                      | LA PILE |          */
/*  | | | |    |                                                                                                       |                      +---------+          */
/*  | | | |                                                                                                                                                        */
/*  | | | |  ===============================================================================================================================================       */
/*  | | | |                                                                                                                                                        */
/*  | | | |    |                                                                                                       |                      +--------+           */
/*  | | | |    |                                                                                                       |                      | LE TAS |           */
/*  | | | |    +-------------------------------------------------------------------------------------------------------+                      +--------+           */
/*  | | | |    |                                                                                                       | <---------------------------------+       */
/*  | | | |    |                                                                                                       | <--------------------------+      |       */
/*  | | | +--> | Le champ "prenom", de type char*, contient l'adresse du tableau de char contenant le prenom "Jean" ---------------+                |      |       */
/*  | | |      |                                                                                                       |           |                |      |       */
/*  | | |      +-------------------------------------------------------------------------------------------------------+           |                |      |       */
/*  | | |      |                                                                                                       |           |                |      |       */
/*  | | |      | Le champ "nom", de type char*, contient l'adresse du tableau de char contenant le nom "PIERRE" --------------+    |                |      |       */
/*  | | |      |                                                                                                       |      |    |                |      |       */
/*  | | |      +-------------------------------------------------------------------------------------------------------+      |    |                |      |       */
/*  | | |      |                                                                                                       |      |    |                |      |       */
/*  | | |      | Le champ age, de type int, contient l'age de Jean PIERRE, soit 50                                     |      |    |                |      |       */
/*  | | |      |                                                                                                       |      |    |                |      |       */
/*  | | |      +-------------------------------------------------------------------------------------------------------+      |    |                |      |       */
/*  | | |      |                                                                                                       |      |    |                |      |       */
/*  | | |      | Le champ contacts, de type Personne**, contient l'adresse du tableau de Personne* qui contient des    |      |    |                |      |       */
/*  | | |      | adresses de type Personne* vers chacun des contacts de Jean Pierre ----------------------------------------- | -- | ---+           |      |       */
/*  | | |      |                                                                                                       |      |    |    |           |      |       */
/*  | | |      +-------------------------------------------------------------------------------------------------------+      |    |    |           |      |       */
/*  | | |      |                                                                                                       |      |    |    |           |      |       */
/*  | | |      | Le champ nbContacts, de type int, contient le nombre d'amis de Jean PIERRE, soit 2                    |      |    |    |           |      |       */
/*  | | |      | C'est aussi la taille du tableau "contacts" du champ precedent                                        |      |    |    |           |      |       */
/*  | | |      |                                                                                                       |      |    |    |           |      |       */
/*  | | |      +-------------------------------------------------------------------------------------------------------+      |    |    |           |      |       */
/*  | | |      |                                                                                                       |      |    |    |           |      |       */
/*  | | |      | ////////////////////////////////////////////////////////////////////////////////////////////////////  |      |    |    |           |      |       */
/*  | | |      | ////////////////////////////////////////////////////////////////////////////////////////////////////  |      |    |    |           |      |       */
/*  | | |      | ////////////////////////////////////////////////////////////////////////////////////////////////////  |      |    |    |           |      |       */
/*  | | |      |                                                                                                       |      |    |    |           |      |       */
/*  | | |      +-------------------------------------------------------------------------------------------------------+      |    |    |           |      |       */
/*  | | |      |                                        P                                                              | <----+    |    |           |      |       */
/*  | | |      |                                        I                                                              |           |    |           |      |       */
/*  | | |      |                                        E                                                              |           |    |           |      |       */
/*  | | |      |                                        R                                                              |           |    |           |      |       */
/*  | | |      |                                        R                                                              |           |    |           |      |       */
/*  | | |      |                                        E                                                              |           |    |           |      |       */
/*  | | |      |                                        \0  (le 0 terminal qui termine une chaine de caractere en C    |           |    |           |      |       */
/*  | | |      +-------------------------------------------------------------------------------------------------------+           |    |           |      |       */
/*  | | |      |                                                                                                       |           |    |           |      |       */
/*  | | |      | ////////////////////////////////////////////////////////////////////////////////////////////////////  |           |    |           |      |       */
/*  | | |      | ////////////////////////////////////////////////////////////////////////////////////////////////////  |           |    |           |      |       */
/*  | | |      | ////////////////////////////////////////////////////////////////////////////////////////////////////  |           |    |           |      |       */
/*  | | |      |                                                                                                       |           |    |           |      |       */
/*  | | |      +-------------------------------------------------------------------------------------------------------+           |    |           |      |       */
/*  | | |      |                                        J                                                              | <---------+    |           |      |       */
/*  | | |      |                                        e                                                              |                |           |      |       */
/*  | | |      |                                        a                                                              |                |           |      |       */
/*  | | |      |                                        n                                                              |                |           |      |       */
/*  | | |      |                                        \0  (le 0 terminal qui termine une chaine de caractere en C    |                |           |      |       */
/*  | | |      +-------------------------------------------------------------------------------------------------------+                |           |      |       */
/*  | | |      |                                                                                                       |                |           |      |       */
/*  | | |      | ////////////////////////////////////////////////////////////////////////////////////////////////////  |                |           |      |       */
/*  | | |      | ////////////////////////////////////////////////////////////////////////////////////////////////////  |                |           |      |       */
/*  | | |      | ////////////////////////////////////////////////////////////////////////////////////////////////////  |                |           |      |       */
/*  | | |      |                                                                                                       |                |           |      |       */
/*  | | |      +-------------------------------------------------------------------------------------------------------+                |           |      |       */
/*  | | |      |                                                                                                       | <--------------+           |      |       */
/*  | | |      | Adresse du premier amis de Jean PIERRE (Jean MARIE) ------------------------------------------------------------------------+      |      |       */
/*  | | |      |                                                                                                       |                     |      |      |       */
/*  | | |      +-------------------------------------------------------------------------------------------------------+                     |      |      |       */
/*  | | |      |                                                                                                       |                     |      |      |       */
/*  | | |      | Adresse du second amis de Jean PIERRE (Pierre LAURENT) ----------------------------------------------------------------+    |      |      |       */
/*  | | |      |                                                                                                       |                |    |      |      |       */
/*  | | |      +-------------------------------------------------------------------------------------------------------+                |    |      |      |       */
/*  | | |      |                                                                                                       |                |    |      |      |       */
/*  | | |      | ////////////////////////////////////////////////////////////////////////////////////////////////////  |                |    |      |      |       */
/*  | | |      | ////////////////////////////////////////////////////////////////////////////////////////////////////  |                |    |      |      |       */
/*  | | |      | ////////////////////////////////////////////////////////////////////////////////////////////////////  |                |    |      |      |       */
/*  | | |      |                                                                                                       |                |    |      |      |       */
/*  | | |      +-------------------------------------------------------------------------------------------------------+                |    |      |      |       */
/*  | | |      |                                                                                                       | <--------------+    |      |      |       */
/*  | | |      |                                                                                                       | <------------------ | ---  | --+  |       */
/*  | | +----> | Le champ "prenom", de type char*, contient l'adresse du tableau de char contenant le prenom "Pierre" -------------+         |      |   |  |       */
/*  | |        |                                                                                                       |           |         |      |   |  |       */
/*  | |        +-------------------------------------------------------------------------------------------------------+           |         |      |   |  |       */
/*  | |        |                                                                                                       |           |         |      |   |  |       */
/*  | |        | Le champ "nom", de type char*, contient l'adresse du tableau de char contenant le nom "LAURENT" -------------+    |         |      |   |  |       */
/*  | |        |                                                                                                       |      |    |         |      |   |  |       */
/*  | |        +-------------------------------------------------------------------------------------------------------+      |    |         |      |   |  |       */
/*  | |        |                                                                                                       |      |    |         |      |   |  |       */
/*  | |        | Le champ age, de type int, contient l'age de Pierre LAURENT, soit 46                                  |      |    |         |      |   |  |       */
/*  | |        |                                                                                                       |      |    |         |      |   |  |       */
/*  | |        +-------------------------------------------------------------------------------------------------------+      |    |         |      |   |  |       */
/*  | |        |                                                                                                       |      |    |         |      |   |  |       */
/*  | |        | Le champ contact, de type Personne**, contient l'adresse du tableau de Personne* qui contient des     |      |    |         |      |   |  |       */
/*  | |        | adresses de type Personne* vers chacun des contacts de Pierre LAURENT -------------------------------------- | -- | ---+    |      |   |  |       */
/*  | |        |                                                                                                       |      |    |    |    |      |   |  |       */
/*  | |        +-------------------------------------------------------------------------------------------------------+      |    |    |    |      |   |  |       */
/*  | |        |                                                                                                       |      |    |    |    |      |   |  |       */
/*  | |        | Le champ nbContacts, de type int, contient le nombre de contacts de Pierre LAURENT, soit 2            |      |    |    |    |      |   |  |       */
/*  | |        | C'est aussi la taille du tableau "contacts" du champ precedent                                        |      |    |    |    |      |   |  |       */
/*  | |        |                                                                                                       |      |    |    |    |      |   |  |       */
/*  | |        +-------------------------------------------------------------------------------------------------------+      |    |    |    |      |   |  |       */
/*  | |        |                                                                                                       |      |    |    |    |      |   |  |       */
/*  | |        | ////////////////////////////////////////////////////////////////////////////////////////////////////  |      |    |    |    |      |   |  |       */
/*  | |        | ////////////////////////////////////////////////////////////////////////////////////////////////////  |      |    |    |    |      |   |  |       */
/*  | |        | ////////////////////////////////////////////////////////////////////////////////////////////////////  |      |    |    |    |      |   |  |       */
/*  | |        |                                                                                                       |      |    |    |    |      |   |  |       */
/*  | |        +-------------------------------------------------------------------------------------------------------+      |    |    |    |      |   |  |       */
/*  | |        |                                        L                                                              | <----+    |    |    |      |   |  |       */
/*  | |        |                                        A                                                              |           |    |    |      |   |  |       */
/*  | |        |                                        U                                                              |           |    |    |      |   |  |       */
/*  | |        |                                        R                                                              |           |    |    |      |   |  |       */
/*  | |        |                                        E                                                              |           |    |    |      |   |  |       */
/*  | |        |                                        N                                                              |           |    |    |      |   |  |       */
/*  | |        |                                        T                                                              |           |    |    |      |   |  |       */
/*  | |        |                                        \0  (le 0 terminal qui termine une chaine de caractere en C    |           |    |    |      |   |  |       */
/*  | |        +-------------------------------------------------------------------------------------------------------+           |    |    |      |   |  |       */
/*  | |        |                                                                                                       |           |    |    |      |   |  |       */
/*  | |        | ////////////////////////////////////////////////////////////////////////////////////////////////////  |           |    |    |      |   |  |       */
/*  | |        | ////////////////////////////////////////////////////////////////////////////////////////////////////  |           |    |    |      |   |  |       */
/*  | |        | ////////////////////////////////////////////////////////////////////////////////////////////////////  |           |    |    |      |   |  |       */
/*  | |        |                                                                                                       |           |    |    |      |   |  |       */
/*  | |        +-------------------------------------------------------------------------------------------------------+           |    |    |      |   |  |       */
/*  | |        |                                        P                                                              | <---------+    |    |      |   |  |       */
/*  | |        |                                        i                                                              |                |    |      |   |  |       */
/*  | |        |                                        e                                                              |                |    |      |   |  |       */
/*  | |        |                                        r                                                              |                |    |      |   |  |       */
/*  | |        |                                        r                                                              |                |    |      |   |  |       */
/*  | |        |                                        e                                                              |                |    |      |   |  |       */
/*  | |        |                                        \0  (le 0 terminal qui termine une chaine de caractere en C    |                |    |      |   |  |       */
/*  | |        +-------------------------------------------------------------------------------------------------------+                |    |      |   |  |       */
/*  | |        |                                                                                                       |                |    |      |   |  |       */
/*  | |        | ////////////////////////////////////////////////////////////////////////////////////////////////////  |                |    |      |   |  |       */
/*  | |        | ////////////////////////////////////////////////////////////////////////////////////////////////////  |                |    |      |   |  |       */
/*  | |        | ////////////////////////////////////////////////////////////////////////////////////////////////////  |                |    |      |   |  |       */
/*  | |        |                                                                                                       |                |    |      |   |  |       */
/*  | |        +-------------------------------------------------------------------------------------------------------+                |    |      |   |  |       */
/*  | |        |                                                                                                       | <--------------+    |      |   |  |       */
/*  | |        | Adresse du premier contact de Pierre LAURENT (Jean PIERRE) ---------------------------------------------------------------- | -----+   |  |       */
/*  | |        |                                                                                                       |                     |          |  |       */
/*  | |        +-------------------------------------------------------------------------------------------------------+                     |          |  |       */
/*  | |        |                                                                                                       |                     |          |  |       */
/*  | |        | Adresse du second contact de Pierre LAURENT (Jean MARIE) --------------------------------------------------------------+    |          |  |       */
/*  | |        |                                                                                                       |                |    |          |  |       */
/*  | |        +-------------------------------------------------------------------------------------------------------+                |    |          |  |       */
/*  | |        |                                                                                                       |                |    |          |  |       */
/*  | |        | ////////////////////////////////////////////////////////////////////////////////////////////////////  |                |    |          |  |       */
/*  | |        | ////////////////////////////////////////////////////////////////////////////////////////////////////  |                |    |          |  |       */
/*  | |        | ////////////////////////////////////////////////////////////////////////////////////////////////////  |                |    |          |  |       */
/*  | |        |                                                                                                       |                |    |          |  |       */
/*  | |        +-------------------------------------------------------------------------------------------------------+                |    |          |  |       */
/*  | +------> |                                                                                                       | <--------------+    |          |  |       */
/*  |          |                                                                                                       | <-------------------+          |  |       */
/*  |          |                                                                                                       | <----------------------+       |  |       */
/*  |          | Le champ "prenom", de type char*, contient l'adresse du tableau de char contenant le prenom "Jean" ---------------+            |       |  |       */
/*  |          |                                                                                                       |           |            |       |  |       */
/*  |          +-------------------------------------------------------------------------------------------------------+           |            |       |  |       */
/*  |          |                                                                                                       |           |            |       |  |       */
/*  |          | Le champ "nom", de type char*, contient l'adresse du tableau de char contenant le nom "MARIE" ---------------+    |            |       |  |       */
/*  |          |                                                                                                       |      |    |            |       |  |       */
/*  |          +-------------------------------------------------------------------------------------------------------+      |    |            |       |  |       */
/*  |          |                                                                                                       |      |    |            |       |  |       */
/*  |          | Le champ age, de type int, contient l'age de Jean MARIE, soit 26                                      |      |    |            |       |  |       */
/*  |          |                                                                                                       |      |    |            |       |  |       */
/*  |          +-------------------------------------------------------------------------------------------------------+      |    |            |       |  |       */
/*  |          |                                                                                                       |      |    |            |       |  |       */
/*  |          | Le champ contact, de type Personne**, contient l'adresse du tableau de Personne* qui contient des     |      |    |            |       |  |       */
/*  |          | adresses de type Personne* vers chacun des contacts de Jean MARIE ------------------------------------------ | -- | ---+       |       |  |       */
/*  |          |                                                                                                       |      |    |    |       |       |  |       */
/*  |          +-------------------------------------------------------------------------------------------------------+      |    |    |       |       |  |       */
/*  |          |                                                                                                       |      |    |    |       |       |  |       */
/*  |          | Le champ nbContacts, de type int, contient le nombre de contacts de Jean MARIE, soit 3                |      |    |    |       |       |  |       */
/*  |          | C'est aussi la taille du tableau "contacts" du champ precedent                                        |      |    |    |       |       |  |       */
/*  |          |                                                                                                       |      |    |    |       |       |  |       */
/*  |          +-------------------------------------------------------------------------------------------------------+      |    |    |       |       |  |       */
/*  |          |                                                                                                       |      |    |    |       |       |  |       */
/*  |          | ////////////////////////////////////////////////////////////////////////////////////////////////////  |      |    |    |       |       |  |       */
/*  |          | ////////////////////////////////////////////////////////////////////////////////////////////////////  |      |    |    |       |       |  |       */
/*  |          | ////////////////////////////////////////////////////////////////////////////////////////////////////  |      |    |    |       |       |  |       */
/*  |          |                                                                                                       |      |    |    |       |       |  |       */
/*  |          +-------------------------------------------------------------------------------------------------------+      |    |    |       |       |  |       */
/*  |          |                                        M                                                              | <----+    |    |       |       |  |       */
/*  |          |                                        A                                                              |           |    |       |       |  |       */
/*  |          |                                        R                                                              |           |    |       |       |  |       */
/*  |          |                                        I                                                              |           |    |       |       |  |       */
/*  |          |                                        E                                                              |           |    |       |       |  |       */
/*  |          |                                        \0  (le 0 terminal qui termine une chaine de caractere en C    |           |    |       |       |  |       */
/*  |          +-------------------------------------------------------------------------------------------------------+           |    |       |       |  |       */
/*  |          |                                                                                                       |           |    |       |       |  |       */
/*  |          | ////////////////////////////////////////////////////////////////////////////////////////////////////  |           |    |       |       |  |       */
/*  |          | ////////////////////////////////////////////////////////////////////////////////////////////////////  |           |    |       |       |  |       */
/*  |          | ////////////////////////////////////////////////////////////////////////////////////////////////////  |           |    |       |       |  |       */
/*  |          |                                                                                                       |           |    |       |       |  |       */
/*  |          +-------------------------------------------------------------------------------------------------------+           |    |       |       |  |       */
/*  |          |                                        J                                                              | <---------+    |       |       |  |       */
/*  |          |                                        e                                                              |                |       |       |  |       */
/*  |          |                                        a                                                              |                |       |       |  |       */
/*  |          |                                        n                                                              |                |       |       |  |       */
/*  |          |                                        \0  (le 0 terminal qui termine une chaine de caractere en C    |                |       |       |  |       */
/*  |          +-------------------------------------------------------------------------------------------------------+                |       |       |  |       */
/*  |          |                                                                                                       |                |       |       |  |       */
/*  |          | ////////////////////////////////////////////////////////////////////////////////////////////////////  |                |       |       |  |       */
/*  |          | ////////////////////////////////////////////////////////////////////////////////////////////////////  |                |       |       |  |       */
/*  |          | ////////////////////////////////////////////////////////////////////////////////////////////////////  |                |       |       |  |       */
/*  |          |                                                                                                       |                |       |       |  |       */
/*  |          +-------------------------------------------------------------------------------------------------------+                |       |       |  |       */
/*  |          |                                                                                                       | <--------------+       |       |  |       */
/*  |          | Adresse du premier contact de Jean MARIE (Pierre LAURENT) -------------------------------------------------------------------- | ------+  |       */
/*  |          |                                                                                                       |                        |          |       */
/*  |          +-------------------------------------------------------------------------------------------------------+                        |          |       */
/*  |          |                                                                                                       |                        |          |       */
/*  |          | Adresse du deuxieme contact de Jean MARIE (Jean PIERRE) ---------------------------------------------------------------------- | ---------+       */
/*  |          |                                                                                                       |                        |                  */
/*  |          +-------------------------------------------------------------------------------------------------------+                        |                  */
/*  |          |                                                                                                       |                        |                  */
/*  |          | Adresse du troisieme contact de Jean MARIE (Marie PIERRE)----------------------------------------------------------------+     |                  */
/*  |          |                                                                                                       |                  |     |                  */
/*  |          +-------------------------------------------------------------------------------------------------------+                  |     |                  */
/*  |          |                                                                                                       |                  |     |                  */
/*  |          | ////////////////////////////////////////////////////////////////////////////////////////////////////  |                  |     |                  */
/*  |          | ////////////////////////////////////////////////////////////////////////////////////////////////////  |                  |     |                  */
/*  |          | ////////////////////////////////////////////////////////////////////////////////////////////////////  |                  |     |                  */
/*  |          |                                                                                                       |                  |     |                  */
/*  |          +-------------------------------------------------------------------------------------------------------+                  |     |                  */
/*  |          |                                                                                                       | <----------------+     |                  */
/*  +--------> | Le champ "prenom", de type char*, contient l'adresse du tableau de char contenant le prenom "Marie" --------------+            |                  */
/*             |                                                                                                       |           |            |                  */
/*             +-------------------------------------------------------------------------------------------------------+           |            |                  */
/*             |                                                                                                       |           |            |                  */
/*             | Le champ "nom", de type char*, contient l'adresse du tableau de char contenant le nom "PIERRE" --------------+    |            |                  */
/*             |                                                                                                       |      |    |            |                  */
/*             +-------------------------------------------------------------------------------------------------------+      |    |            |                  */
/*             |                                                                                                       |      |    |            |                  */
/*             | Le champ age, de type int, contient l'age de Marie PIERRE, soit 16                                    |      |    |            |                  */
/*             |                                                                                                       |      |    |            |                  */
/*             +-------------------------------------------------------------------------------------------------------+      |    |            |                  */
/*             |                                                                                                       |      |    |            |                  */
/*             | Le champ contact, de type Personne**, contient l'adresse du tableau de Personne* qui contient des     |      |    |            |                  */
/*             | adresses de type Personne* vers chacun des contacts de Marie PIERRE ---------------------------------------- | -- | ---+       |                  */
/*             |                                                                                                       |      |    |    |       |                  */
/*             +-------------------------------------------------------------------------------------------------------+      |    |    |       |                  */
/*             |                                                                                                       |      |    |    |       |                  */
/*             | Le champ nbContacts, de type int, contient le nombre de contacts de Marie PIERRE, soit 1              |      |    |    |       |                  */
/*             | C'est aussi la taille du tableau "contacts" du champ precedent                                        |      |    |    |       |                  */
/*             |                                                                                                       |      |    |    |       |                  */
/*             +-------------------------------------------------------------------------------------------------------+      |    |    |       |                  */
/*             |                                                                                                       |      |    |    |       |                  */
/*             | ////////////////////////////////////////////////////////////////////////////////////////////////////  |      |    |    |       |                  */
/*             | ////////////////////////////////////////////////////////////////////////////////////////////////////  |      |    |    |       |                  */
/*             | ////////////////////////////////////////////////////////////////////////////////////////////////////  |      |    |    |       |                  */
/*             |                                                                                                       |      |    |    |       |                  */
/*             +-------------------------------------------------------------------------------------------------------+      |    |    |       |                  */
/*             |                                        P                                                              | <----+    |    |       |                  */
/*             |                                        I                                                              |           |    |       |                  */
/*             |                                        E                                                              |           |    |       |                  */
/*             |                                        R                                                              |           |    |       |                  */
/*             |                                        R                                                              |           |    |       |                  */
/*             |                                        E                                                              |           |    |       |                  */
/*             |                                        \0  (le 0 terminal qui termine une chaine de caractere en C    |           |    |       |                  */
/*             +-------------------------------------------------------------------------------------------------------+           |    |       |                  */
/*             |                                                                                                       |           |    |       |                  */
/*             | ////////////////////////////////////////////////////////////////////////////////////////////////////  |           |    |       |                  */
/*             | ////////////////////////////////////////////////////////////////////////////////////////////////////  |           |    |       |                  */
/*             | ////////////////////////////////////////////////////////////////////////////////////////////////////  |           |    |       |                  */
/*             |                                                                                                       |           |    |       |                  */
/*             +-------------------------------------------------------------------------------------------------------+           |    |       |                  */
/*             |                                        M                                                              | <---------+    |       |                  */
/*             |                                        a                                                              |                |       |                  */
/*             |                                        r                                                              |                |       |                  */
/*             |                                        i                                                              |                |       |                  */
/*             |                                        e                                                              |                |       |                  */
/*             |                                        \0  (le 0 terminal qui termine une chaine de caractere en C    |                |       |                  */
/*             +-------------------------------------------------------------------------------------------------------+                |       |                  */
/*             |                                                                                                       |                |       |                  */
/*             | ////////////////////////////////////////////////////////////////////////////////////////////////////  |                |       |                  */
/*             | ////////////////////////////////////////////////////////////////////////////////////////////////////  |                |       |                  */
/*             | ////////////////////////////////////////////////////////////////////////////////////////////////////  |                |       |                  */
/*             |                                                                                                       |                |       |                  */
/*             +-------------------------------------------------------------------------------------------------------+                |       |                  */
/*             |                                                                                                       | <--------------+       |                  */
/*             | Adresse du contact de Marie PIERRE (Jean PIERRE) ------------------------------------------------------------------------------+                  */
/*             |                                                                                                       |                                           */
/*             +-------------------------------------------------------------------------------------------------------+                                           */
/*             |                                                                                                       |                                           */
/*             |                                                                                                       |                                           */
/*                                                                                                                                                                 */
/*                                                                                                                                                                 */ 
/*******************************************************************************************************************************************************************/


