#ifndef NODE_H
#define NODE_H

#include <stdio.h>
#include <stdlib.h>

enum color{
    black, red, yellow, green, blue
};

enum name{
    zero, one, two, three, four, five, six, seven, eight, nine, skip, reverse, drawtwo, wild, wild_draw_four
};

typedef struct node_t{
    int color;
    int name;
    struct node_t *next;
}node;


#endif 