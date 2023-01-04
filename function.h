#ifndef FUNCTION_H
#define FUNCTION_H

#include "node.h"

//gamerule.c
node *ruleandrenewpokerpile (node *pokerpile, node *card, int *draw);
node *makenode(node *input);
void changewildcolor(node *input);
int changedraw(int cardname);

#endif