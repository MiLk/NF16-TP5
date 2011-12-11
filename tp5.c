#include <stdio.h>
#include <stdlib.h>
#include "arbre.h"

/*
 *
 */
int main(int argc, char** argv)
{
    int n=0,m=0, i=0, taille=0;
    char v;
    NodePtr tab[50], node;
    do
    {
        printf("1- Saisir une expression\n2- Selectionner une expression\n");
        scanf("%d",&n);
        switch(n)
        {
            case 1:
                if(taille<50)
                {
                    getchar();
                    node = saisie_expression();
                    if(node != NULL)
                    {
                        taille++;
                        tab[taille]= node;
                        affiche_expression(tab[taille]);
                    }
                    printf("\n\n");
                }
                else
                    printf("Erreur. Trop d'expressions ont ete saisies.\n");
                break;
            case 2:
                if(taille >0)
                {
                    for(i=1;i<=taille;i++)
                    {
                        printf("%d- ",i);
                        affiche_expression(tab[i]);
                        printf("\n");
                    }
                    scanf("%d",&n);
                    printf("\nFonctions a executer :\n1- Affichage pre-ordre\n2- Affichage in-ordre\n3- Affichage post-ordre\n4- Duplication\n5- Calcul\n6- Developpement\n7- Derivation\n");
                        scanf("%d",&m);
                        switch(m)
                        {
                            case 1:
                                pre_ordre(tab[n]);
                                printf("\n\n");
                                break;
                            case 2:
                                in_ordre(tab[n]);
                                printf("\n\n");
                                break;
                            case 3:
                                post_ordre(tab[n]);
                                printf("\n\n");
                                break;
                            case 4:
                                taille++;
                                tab[taille] = clone(tab[n]);
                                printf("Nouvelle expression generee.\n\n");
                                break;
                            case 5:
                                calcul(tab[n]);
                                printf("\nResultat :\n");
                                affiche_expression(tab[n]);
                                printf("\n\n");
                                break;
                            case 6:
                                developpement(tab[n]);
                                printf("\nResultat :\n");
                                affiche_expression(tab[n]);
                                printf("\n\n");
                                break;
                            case 7:
                                printf("\nSaisir la variable de derivation\n");
                                getchar();
                                scanf("%c",&v);
                                derivation(tab[n],v);
                                printf("\nResultat :\n");
                                affiche_expression(tab[n]);
                                printf("\n\n");
                                break;
                        }
                }
                else
                    printf("Aucune expression n'a ete saisie.\n");
                break;
        }
    }while(n>0);
    for(i=1;i<=taille;i++)
        liberer_noeud(tab[i]);
    return (EXIT_SUCCESS);
}

