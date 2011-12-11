#include "pile.h"

Pile* creer_pile()
{
    Pile* pile = (Pile*)malloc(sizeof(Pile));
    return pile;
}

void empiler(Pile* pile, NodePtr noeud)
{
    //printf("Empiler %c %i \n",noeud->name,noeud->value);
    Element* element = (Element*)malloc(sizeof(Element));
    element->noeud = noeud;
    element->succ = pile->head;
    pile->head = element;
}

NodePtr depiler(Pile* pile)
{
    NodePtr node; 
    Element* element = pile->head;
    //printf("Depiler %c %i \n",element->noeud->name,element->noeud->value);
    pile->head = element->succ;
    node = element->noeud;
    free(element);
    return node;
}