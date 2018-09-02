
// ALGORITHME BONJOUR
// DEBUT
// AFFICHER ("Bonjour")
// FIN

#include <stdio.h> // nécessaire pour utiliser la commande printf
void main ()
{
	printf("Bonjour");
}

// compilé : source -> prog -> exécutable -> code machine

// semi-compilé (java) : source -> prog (javac) -> byte code -> exe (java) -> code machine

// interprété : src -> interpréteur -> code machine

// C : source -> pré-processeur(#include, #exclude,...) -> compilateur -> éditeur de liens -> exécutable

// #include : dans le code source, le #include est remplacé par son target !
// compilateur donne du code machine (fichier, objet)
// éditeur de liens -> code machine produit + autre codes machines fournis dans des bibliothèques
// bibli de base : bibliothèque 'standard'

// nano ~/.bashrc
// export PATH=$PATH:.
// quitter nano et ensuite . ~/.bashrc
// pour régler des PATH d'exécutables
// pour écrire fichier.c au lieu de ./fichier.c

// ssh id@idboard.net -p 40000 -X
// > qtcreator

// environnement à installer sous windows : xming

// sudo apt -y install build-essentials

// gcc -- commande permettant de compiler mon programme c
// gcc fichier.c -> donne fichier a.out
// alors que gcc fichier.c -o nom_voulu donne le bon nom au fichier out

// nano bonjour.c