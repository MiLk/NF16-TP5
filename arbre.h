#ifndef ARBRE_H_INCLUDED
#define ARBRE_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    struct Node * left; /* fils gauche */
    struct Node * right; /* fils droit */
    char name; /* nom de l'operateur */
    int value; /* valeur de la constante */
} Node;

typedef Node* NodePtr; /* pointeur sur un noeud */

/**
 * Allocation de la mémoire, création du noeud et assignation des valeurs passées en paramètres
 * @param nom Opérateur ou variable ou caractère nul
 * @param valeur Valeur de la constante ou caractère nul
 * @return Pointeur sur le noeud
 */
NodePtr creer_noeud(char nom, int valeur);
/**
 * Libère la mémoire allouée à un noeud et à ses descendants
 * @param node Noeud à libérer
 */
void liberer_noeud(NodePtr node);
/**
 * Fonction qui permet de saisir une expression et de créer un arbre
 * @return Racine de l'arbre créé
 */
NodePtr saisie_expression();
/**
 * Parcours l'arbre en pre-ordre
 * @param Racine de l'arbre à parcourir
 */
void pre_ordre(NodePtr);
/**
 * Parcours l'arbre en in-ordre
 * @param Racine de l'arbre à parcourir
 */
void in_ordre(NodePtr);
/**
 * Parcours l'arbre en post-ordre
 * @param Racine de l'arbre à parcourir
 */
void post_ordre(NodePtr);
/**
 * Affiche l'expression correspondant à un arbre
 * @param node Racine de l'arbre
 */
void affiche_expression(NodePtr node);
/**
 * Réalise les calculs entre les feuilles de l'arbre
 * @param node Racine de l'arbre
 */
void calcul_intermediaire(NodePtr node);
/**
 * Teste si un noeud est une feuille
 * @param node Noeud à tester
 * @return 1 si feuille, 0 sinon
 */
int is_feuille(NodePtr node);
/**
 * Copie un arbre et retourne un pointeur sur la racine du nouvel arbre
 * @param node Racine de l'arbre à copier
 * @return Racine du nouvel arbre
 */
NodePtr clone(NodePtr node);
/**
 * Teste si 2 arbres sont identiques
 * @param node1 Racine de l'arbre 1
 * @param node2 Racine de l'arbre 2
 * @return 1 si identiques, 0 sinon
 */
int identiques(NodePtr node1,NodePtr node2);
/**
 * Réalise tous les calculs possibles sur un arbre
 * @param node Racine de l'arbre à calculer
 */
void calcul(NodePtr node);
/**
 * Développe l'expression représentée par l'arbre spécifié
 * @param node Racine de l'arbre à développer
 */
void developpement(NodePtr node);
/**
 * Dérive l'expression représentée par l'arbre spécifié
 * @param node Racine de l'arbre
 * @param v Variable de dérivation
 */
void derivation(NodePtr node, char v);

#endif
