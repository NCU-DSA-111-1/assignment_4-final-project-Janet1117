#ifndef FUNCTION_H
#define FUNCTION_H

#include "node.h"

//gamerule.c
node *ruleandrenewpokerpile (node *pokerpile, node *card, int *draw, node *head);
node *makenode(node *input);
void changewildcolor(node *input);
int changedraw(int cardname);
node *insertafter(node *list, node *insert);
node *deleteafter(node *list, node *card);
int foolproof(node *list, node *card);

//computer.c
node *computeruser(node *pokerpile, node **computerusercard, int *draw);
//void countcolor(int cardcolor);


#endif