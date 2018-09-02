#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct strProduit Produit;
typedef struct strAchat Achat;

void afficherSelection();
void traiterAchat();
void afficherTicketDeCaisse();
Produit rechercher(int reference);

struct strProduit
{
    int reference;
    char nom[15];
    float prix;
};

struct strAchat
{
    int reference;
    int quantite;
};

Produit catalogue[]=
{
    {2555, "savon", 2.9},
    {7555, "gel douche", 3.9},
    {2575, "mousse à raser", 2.77}
};

Achat panier[10];

Produit chercher(int ref)
{
    int a;
    Article temp;
    for (a = 0 ; a < nbArtcile; a++)
    {
        if (catalogue[a].reference==ref)
        {
            temp = catalogue[a];break;
        }
        return temp;
    }
    a=0;
    while(catalogue[a].reference!=ref && a<nbArticle)
    {
        a++;
    }
}

}

int main(int argc, char* argv[])
{
    int article;
    int reference;


    do
    {
        for (article = 0; article < 1 ; article++)
        {
            printf("%d_______%s(%.lf)\n", catalogue[article].reference, catalogue[article].nom, catalogue[article].reference,catalogue[article].prix);
        }
        printf("0_______validation du panier\n");
        scanf("%d", &reference);
        if (reference !=0)
        {
            //traiterAchat(reference);
        }
    } while (reference !=0);

    //afficherTicketDeCaisse();

    return 0;
}
