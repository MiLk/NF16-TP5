#ifndef ARBRE_H_INCLUDED
#define ARBRE_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    struct Node * left; /* fils gauche */
    struct Node * right; /* fils droit */
    char name; /* nom de l�op�rateur */
    int value; /* valeur de la constante */
} Node;

typedef Node* NodePtr; /* pointeur sur un noeud */

NodePtr creer_noeud(char nom, int valeur);
void liberer_noeud(NodePtr node);
NodePtr saisie_expression();
void pre_ordre(NodePtr);
void in_ordre(NodePtr);
void post_ordre(NodePtr);
void affiche_expression(NodePtr node);
void calcul_intermediaire(NodePtr node);
int is_feuille(NodePtr node);
NodePtr clone(NodePtr node);
int identiques(NodePtr node1,NodePtr node2);
void calcul(NodePtr node);
void developpement(NodePtr node);
void derivation(NodePtr node, char v);

#endif
