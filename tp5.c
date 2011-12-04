#include <stdio.h>
#include <stdlib.h>
#include "arbre.h"

/*
 * 
 */
int main(int argc, char** argv)
{
    NodePtr arbre = (NodePtr)malloc(sizeof(Node));
    arbre = saisie_expression();
    affiche_expression(arbre);
    printf("\n");
    calcul_intermediaire(arbre);
    affiche_expression(arbre);
    printf("\n");
    return (EXIT_SUCCESS);
}

