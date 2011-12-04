#ifndef PILE_H
#define	PILE_H

#include "arbre.h"

typedef struct Element { 
    NodePtr noeud;
    struct Element* succ;
} Element ;
typedef struct Pile {
    Element* head;
} Pile;

Pile* creer_pile();
void empiler(Pile* pile, NodePtr noeud);
NodePtr depiler(Pile* pile);

#endif	/* PILE_H */

