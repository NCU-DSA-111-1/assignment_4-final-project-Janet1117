#ifndef MODE_H
#define MODE_H
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include"node.h"
void ThreePlayer();
void FourPlayer();

void initialize_three_player_card();
void initialize_four_player_card();

void shuffle(int *player_order, size_t amount);

int i, j;

typedef struct player_card_t{
    struct player_card_t *prev;
    node info;
    struct player_card_t *next;
}player_card;




//三人模式
void ThreePlayer(){
    int three_player_order[3] = {0, 1, 2};//出排順序:0代表player1,以此類推
    int player_amount = (int) sizeof(three_player_order) / sizeof(three_player_order[0]);
    
    //打亂順序
    shuffle(three_player_order, player_amount);
    
    //初始化玩家手中的牌
    initialize_three_player_card();
    
}

//四人模式
void FourPlayer(){
    int four_player_order[4] = {0, 1, 2, 3};//出排順序:0代表player1,以此類推
    int player_amount = (int) sizeof(four_player_order) / sizeof(four_player_order[0]);
    
    //打亂順序
    shuffle(four_player_order, player_amount);
    
    //初始化玩家手中的牌
    initialize_four_player_card();

}

//初始化3人模式玩家手中的牌
void initialize_three_player_card(){
    //每位玩家手中的牌，player1固定為真人玩家
    player_card *player1 = NULL;//真人玩家手中的牌
    player_card *player2 = NULL;//電腦玩家手中的牌
    player_card *player3 = NULL;//電腦玩家手中的牌
}

//初始化4人模式玩家手中的牌
void initialize_four_player_card(){
    //每位玩家手中的牌，player1固定為真人玩家
    player_card *player1 = NULL;//真人玩家手中的牌
    player_card *player2 = NULL;//電腦玩家手中的牌
    player_card *player3 = NULL;//電腦玩家手中的牌
    player_card *player4 = NULL;//電腦玩家手中的牌
}

//隨機出排順序
void shuffle(int *player_order, size_t amount){
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