#include "arbre.h"
#include "pile.h"

NodePtr creer_noeud(char nom, int valeur)
{
    NodePtr noeud = malloc(sizeof (Node));
    noeud->left = NULL;
    noeud->right = NULL;
    noeud->name = nom;
    noeud->value = valeur;
    return noeud;
}

NodePtr saisie_expression()
{
    Pile* stack = creer_pile();
    char c = '\0';
    NodePtr tmp;
    while (c != '\n')
    {
        c = getchar();
        switch (c)
        {
            case '+':
            case '*':
                tmp = creer_noeud(c, '\0');
                tmp->right = depiler(stack);
                tmp->left = depiler(stack);
                empiler(stack, tmp);
                break;
            default:
                if (c >= '0' && c <= '9') // Si le caract�re saisi est un chiffre
                    empiler(stack, creer_noeud('\0', c - '0')); // On l'empile on le convertissant en entier
                else if (c >= 'a' && c <= 'z') //	Le caract�re est une variable
                    empiler(stack, creer_noeud(c, '\0'));
                else if (c != '\n' && c != ' ')
                    printf("Erreur de saisie.\n");
                break;
        }
    }
    return depiler(stack);
}

void pre_ordre(NodePtr node)
{
    if (node->name != '\0')
    {
        printf("%c", node->name);
        pre_ordre(node->left);
        pre_ordre(node->right);
    } else
        printf("%d", node->value);
}

void in_ordre(NodePtr node)
{
    if (node->name != '\0')
    {
        in_ordre(node->left);
        printf("%c", node->name);
        in_ordre(node->right);
    } else
        printf("%d", node->value);
}

void post_ordre(NodePtr node)
{
    if (node->name != '\0')
    {
        printf("%c", node->name);
        post_ordre(node->left);
        post_ordre(node->right);
    } else
        printf("%d", node->value);
}

void affiche_expression(NodePtr node)
{
    if (node->name != '\0')
    {
        printf("(");
        affiche_expression(node->left);
        printf("%c", node->name);
        affiche_expression(node->right);
        printf(")");
    } else
        printf("%d", node->value);
}