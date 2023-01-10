#ifndef  SETUPPLAYER_H
#define SETUPPLAYER_H
#include<time.h>
#include"node.h"
#include"stack.h"

node *makelist(node *list);

void ShuffleOrder(int *player_order, size_t amount);

int i;

node *player1 = NULL;//真人玩家手中的牌
node *player2 = NULL;//電腦玩家手中的牌
node *player3 = NULL;//電腦玩家手中的牌
node *player4 = NULL;//電腦玩家手中的牌


node *makelist(node *list){
    if(list == NULL){
        list = (node *) malloc (sizeof(node));
        list->next = list->prev = NULL;
    }
    return list;
}


//隨機出排順序
void ShuffleOrder(int *player_order, size_t amount){
    //亂數前置
    srand(time(NULL));
    if(amount > 1){
        size_t x;
        for(x = 0; x < amount; x++){
            size_t y = rand() / (RAND_MAX / (amount));
            int t = player_order[y];
            player_order[y] = player_order[x];
            player_order[x] = t;
        }
    }
}

#endif