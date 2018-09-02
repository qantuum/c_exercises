#include <stdio.h>
#include <stdlib.h> // malloc est free sont definit ici


char * fct ()
{
  // "malloc" permets d'allouer de la mémoire dans le "TAS"
  //"malloc" prend en paramètre le nombre d'octets à allouer => ici 1 car 1char = 1 octets

  // "malloc" renvoie un " void * " (pointeur générique), il faut le caster(transtyper) en "char *"
  // pour pouvoir le stocker dans "t" ( detype char *)
  char * t = (char*)malloc(1);

  // On teste si "t" est non NULL avant d'utiliser "t"
  // => si t == NULL, ça signifie que malloc à échoué(pas trouvé le nmb d'octet contigus dans le tas)
  //=> si on déférence le pointeur NULL, le programme crash
  if (t!=NULL)
  {

    // ici on déférence "t" pour stocker et la lettre "A"
    *t ='A';
  }

  //là, on renvoie le pointeur pour l'utiliser en dehors de "fct"
  //=> si on perd l'adresse de la zone allouée dans le TAS, on a plus moyen de la manipuler
  return t;
}

void main ()
{

  // on stocke l'adresse de la zone allouée dans le tas que contient 'A', dans "l", de type char *
  char * l = fct();

  // On teste si "l" est non NULL avant d'utiliser "l"
  //=> Si on déférence le pointeur NULL, ça crash
  // => Si on fait free sur le pointeur NULL, ça crash aussi !
  if(l != NULL)
  {
    printf("%c\n", *l );

    // Désalloue la mémoire pointée par "l" dans le tas
    // => Le TAS diminue
    //=> Si on oublie, on parle de fuite de mémoire
    //=> Le TAS rique de toucher la "PILE" , donc ca crash !
    free (l);
  }
}
