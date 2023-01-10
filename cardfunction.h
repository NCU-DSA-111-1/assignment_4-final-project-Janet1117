#ifndef CARDFUNCTION_H
#define CARDFUNCTION_H
#include<stdlib.h>
#include<stdio.h>
#include"node.h"
#include"stack.h"
#include"setupplayer.h"

void SpecialCardFunction(int draw, int *PlayerOrder, int *OrderNumber, int playerAmount);
node *DrawOne(node *player);//加一張牌
void DrawTwo(int *playerOrder, int *orderNumber, int playerAmount);
void DrawFour(int *playerOrder, int *orderNumber, int playerAmount);

int RevserseOrNot = 0;


//執行功能牌功能  
void SpecialCardFunction(int draw, int *PlayerOrder, int *OrderNumber, int playerAmount){
    //+2
    if(draw == 2){
        DrawTwo(PlayerOrder, OrderNumber, playerAmount);
    }
    //+4
    else if(draw == 4){
        DrawFour(PlayerOrder, OrderNumber, playerAmount);
    }
    //skip
    else if(draw == 5){
        if(RevserseOrNot % 2 == 0){
            *OrderNumber = (*OrderNumber == playerAmount - 1) ? 0 : (*OrderNumber + 1);
        }else{
            *OrderNumber = (*OrderNumber == 0) ? playerAmount - 1 : (*OrderNumber - 1); 
        }
    }
}

//加一張牌
node *DrawOne(node *player){
    node data;
    if(player == NULL){
        player = (node *) malloc (sizeof(node));
        data = pop();
        player->color = data.color;
        player->name = data.name;
        player->next = player->prev = NULL;
    }else{
        node *newnode;
        newnode = (node *) malloc (sizeof(node));
        data = pop();
        newnode->color = data.color;
        newnode->name = data.name;
        newnode->next = player->next;
        newnode->prev = player;
        if(player->next != NULL){
            player->next->prev = newnode;
        }
        player->next = newnode;        
    }
    return player;
}

//+2
void DrawTwo(int *playerOrder, int *orderNumber, int playerAmount){
    int next = *orderNumber;
    if(RevserseOrNot % 2 == 0){
        next = (next == playerAmount - 1) ? 0 : (next + 1);
    }else{
        next = (next == 0) ? (playerAmount - 1) : (next - 1);
    }
    if(playerOrder[next] == 0){
        for(i = 0; i < 2; i++){
            player1 = DrawOne(player1);
        }
    }else if(playerOrder[next] == 1){
        for(i = 0; i < 2; i++){
            player2 = DrawOne(player2);
        }
    }else if(playerOrder[next] == 2){
        for(i = 0; i < 2; i++){
            player3 = DrawOne(player3);
        }
    }else if(playerOrder[next] == 3){
        for(i = 0; i < 2; i++){
            player4 = DrawOne(player4);
        }
    }
}

//+4
void DrawFour(int *playerOrder, int *orderNumber, int playerAmount){
    int next = *orderNumber;
    if(RevserseOrNot % 2 == 0){
        next = (next == playerAmount - 1) ? 0 : (next + 1);
    }else{
        next = (next == 0) ? (playerAmount - 1) : (next - 1);
    }
    if(playerOrder[next] == 0){
        for(i = 0; i < 4; i++){
            player1 = DrawOne(player1);
        }
    }else if(playerOrder[next] == 1){
        for(i = 0; i < 4; i++){
            player2 = DrawOne(player2);
        }
    }else if(playerOrder[next] == 2){
        for(i = 0; i < 4; i++){
            player3 = DrawOne(player3);
        }
    }else if(playerOrder[next] == 3){
        for(i = 0; i < 4; i++){
            player4 = DrawOne(player4);
        }
    }
}

#endif