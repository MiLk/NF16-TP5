#include "arbre.h"
#include "pile.h"

NodePtr creer_noeud(char nom, int valeur)
{
    NodePtr noeud = (NodePtr)malloc(sizeof (Node));
    noeud->left = NULL;
    noeud->right = NULL;
    noeud->name = nom;
    noeud->value = valeur;
    return noeud;
}

void liberer_noeud(NodePtr node)
{
    if (node != NULL)
    {
        liberer_noeud(node->left);
        liberer_noeud(node->right);
        free(node);
    }
}

NodePtr saisie_expression()
{
    Pile* stack = creer_pile();
    int i = 0,j = 0; // Validation de l'expression
    char c = '\0';
    NodePtr tmp;
    while (c != '\n')
    {
        c = getchar();
        switch (c)
        {
            case '+':
            case '*':
                if(j == 0 && i < 2)
                {
                    printf("Expression invalide : les deux premiers caracteres doivent etre des operandes !\n");
                    return NULL;
                }
                tmp = creer_noeud(c, '\0');
                tmp->right = depiler(stack);
                tmp->left = depiler(stack);
                empiler(stack, tmp);
                j++; // on incremente le nombre d'operateurs
                break;
            default:
                if (c >= '0' && c <= '9') // Si le caract�re saisi est un chiffre
                {
                    empiler(stack, creer_noeud('\0', c - '0')); // On l'empile on le convertissant en entier
                    i++; // on incremente le nombre d'operande
                }
                else if (c >= 'a' && c <= 'z') //	Le caract�re est une variable
                {
                    empiler(stack, creer_noeud(c, '\0'));
                    i++; // on incremente le nombre d'operande
                }
                else if (c != '\n' && c != ' ')
                {
                    printf("Erreur de saisie : caractere inconnu.\n");
                    return NULL;
                }
                break;
        }
    }
    if(i != ( j + 1 ) ) // Si le nombre d'operateurs ou d'operandes est incorrect
    {
        printf("Expression invalide : nombre d'operateurs ou d'operandes incorrect !\n");
        return NULL;
    }
    tmp = depiler(stack);
    if(tmp->name != '+' && tmp->name != '*')
    {
        printf("Expression invalide : le dernier caractere doit etre un operateur !\n");
        return NULL;
    }
    return tmp;
}

void pre_ordre(NodePtr node)
{
    if(node == NULL)
    {
        printf("Expression inexistante ou incorrecte !\n");
        return;
    }
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
    if(node == NULL)
    {
        printf("Expression inexistante ou incorrecte !\n");
        return;
    }
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
    if(node == NULL)
    {
        printf("Expression inexistante ou incorrecte !\n");
        return;
    }
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
    if(node == NULL)
    {
        printf("Expression inexistante ou incorrecte !\n");
        return;
    }
    if (node->name != '\0')
        if (node->name >= 'a' && node->name <= 'z')
            printf("%c", node->name);
        else
        {
            printf("(");
            affiche_expression(node->left);
            printf("%c", node->name);
            affiche_expression(node->right);
            printf(")");
        } else
        printf("%d", node->value);
}

void calcul_intermediaire(NodePtr node)
{
    if(node == NULL)
    {
        printf("Expression inexistante ou incorrecte !\n");
        return;
    }
    if (!is_feuille(node))
    {
        if (!is_feuille(node->right))
        {
            if (!is_feuille(node->left))
                calcul_intermediaire(node->left);
            calcul_intermediaire(node->right);
        } else
        {
            if (!is_feuille(node->left))
                calcul_intermediaire(node->left);
            else
            { // Left & Right sont des feuilles
                char name = node->name;
                int val = node->value;
                char left = node->left->name;
                int vall = node->left->value;
                char right = node->right->name;
                int valr = node->right->value;
                switch (node->name)
                {
                    case '+':
                        // Dans le cas de deux constantes
                        if (node->left->name == '\0' && node->right->name == '\0')
                            node->value = node->left->value + node->right->value;
                            // Si au moins une constante et vaut 0
                        else if (node->left->name == '\0' && node->left->value == 0)
                            node->name = node->right->name;
                            // Si la deuxième est constante et vaut 0
                        else if (node->right->name == '\0' && node->right->value == 0)
                            node->name = node->left->name;
                            // Si les 2 sont des variables
                        else
                            return;
                        break;
                    case '*':
                        // Dans le cas de deux constantes
                        if (node->left->name == '\0' && node->right->name == '\0')
                            node->value = node->left->value * node->right->value;
                            // Si au moins une constante et vaut 0
                        else if ((node->left->name == '\0' && node->left->value == 0) ||
                                (node->right->name == '\0' && node->right->value == 0))
                            node->value = 0;
                            // Si au moins une constante et vaut 1
                        else if (node->left->name == '\0' && node->left->value == 1)
                            node->name = node->right->name;
                            // Si la deuxième est constante et vaut 1
                        else if (node->right->name == '\0' && node->right->value == 1)
                            node->name = node->left->name;
                            // Si les 2 sont des variables
                        else
                            return;
                        break;
                }
                if (node->name == '*' || node->name == '+')
                    node->name = '\0';
                free(node->left);
                free(node->right);
                node->left = NULL;
                node->right = NULL;
            }
        }
    }
}

int is_feuille(NodePtr node)
{
    if(node == NULL)
    {
        printf("Expression inexistante ou incorrecte !\n");
        return 0;
    }
    return (node->name != '+' && node->name != '*') ? 1 : 0;
}

NodePtr clone(NodePtr node)
{
    NodePtr newnode;
    if (node != NULL)
    {
        newnode = creer_noeud(node->name, node->value);
        newnode->left = clone(node->left);
        newnode->right = clone(node->right);
        return newnode;
    }
    return NULL;
}

int identiques(NodePtr node1, NodePtr node2)
{
    if (node1 == NULL)
        if (node2 == NULL)
            return 1;
        else
            return 0;
    else
        if (node2 == NULL)
        return 0;
    else if (node1->name != node2->name || node1->value != node2->value)
        return 0;
    else
        return identiques(node1->left, node2->left) * identiques(node1->right, node2->right);
}

void calcul(NodePtr node)
{
    if(node == NULL)
    {
        printf("Expression inexistante ou incorrecte !\n");
        return;
    }
    NodePtr tmp = clone(node);
    calcul_intermediaire(tmp);
    while (!identiques(tmp, node))
    {
        calcul_intermediaire(node);
        calcul_intermediaire(tmp);
    }
    liberer_noeud(tmp);
}

void developpement(NodePtr node)
{
    if (node != NULL)
    {
        if (node->name == '*')
        {
            NodePtr constant;
            if (node->left->name == '+')
            {
                printf("\ngauche\n");
                affiche_expression(node);
                printf("\n");
                node->name = '+';
                constant = clone(node->right);
                liberer_noeud(node->right->left);
                liberer_noeud(node->right->right);
                node->right->left = clone(node->left->right); // deuxieme coefficient
                liberer_noeud(node->left->right);
                node->left->right = constant; // partie droite invariante
                node->right->right = clone(constant); // partie droite invariante
                node->left->name = '*';
                node->right->name = '*';
                node->right->value = '\0';
                printf("\n");
                affiche_expression(node);
                printf("\n");
            } else if (node->right->name == '+')
            {
                printf("\ndroite\n");
                affiche_expression(node);
                printf("\n");
                node->name = '+';
                constant = clone(node->left);
                liberer_noeud(node->left->left);
                liberer_noeud(node->left->right);
                node->left->right = clone(node->right->left);
                liberer_noeud(node->right->left);
                node->right->left = constant;
                node->left->left = clone(constant);
                node->right->name = '*';
                node->left->name = '*';
                node->left->value = '\0';
                printf("\n");
                affiche_expression(node);
                printf("\n");
            }
        }
        developpement(node->left);
        developpement(node->right);
    }
}

void derivation(NodePtr node, char v)
{
    if (node != NULL)
        switch (node->name)
        {
            case('\0'): //Le noeud est une constante
                node->value = 0;
                break;
            case('+'):
                derivation(node->left, v);
                derivation(node->right, v);
                break;
            case('*'):
                node->left = clone(node);
                node->right = clone(node->left);
                node->name = '+';
                derivation(node->left->left, v);
                derivation(node->right->right, v);
                break;
            default:
                if (node->name == v)
                    node->value = 1;
                else
                    node->value = 0;
                node->name = '\0';
                break;
        }
}
