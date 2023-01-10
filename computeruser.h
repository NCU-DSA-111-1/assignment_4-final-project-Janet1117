#ifndef COMPUTERUSER_H
#define COMPUTERUSER_H

#include "function.h"
#include <time.h>
#include"stack.h"

node *play;
int switched = 0;
int blackcount = 0;
int redcount = 0;
int yellowcount = 0;
int greencount = 0;
int bluecount = 0;


//呼叫computeruser的function 
node *computeruser(node *pokerpile, node **computerusercard, int *draw)
{
    *draw = 0;
    switched = 0;//判斷是否有可出的牌
    play = NULL;
    node *tmp;
    tmp = (*computerusercard);
    while(tmp != NULL)
    {
        if((switched == 0) && (((tmp->color == pokerpile->color) || (tmp->name == pokerpile->name)) ||(tmp->color == black)))
        {
            play = tmp;//找到的牌放進play
            switched = 1;
        }

        //countcolor(tmp->color);
        tmp = tmp->next;
    }

    //無牌可出
    if(play == NULL)
    {
        node *drawcard;
        node *tmpinsert;
        tmpinsert = (*computerusercard);
        //呼叫抽一張牌的函式 drawcard = 
        node tmpcard;
        tmpcard = pop();
        drawcard = (node *)malloc(sizeof(node));
        drawcard->color = tmpcard.color;
        drawcard->name = tmpcard.name;

        //找最後一張 並新增
        while(tmpinsert->next != NULL)
        {
            tmpinsert = tmpinsert->next;
        }
        tmpinsert = insertafter(tmpinsert, makenode(drawcard));
        
        //printf("電腦玩家無牌可出，抽取一張牌\n");
    }
    //有牌可以出的情況
    else
    {
        if(play->color == black)
        {
            //如果牌是黑色 換的顏色隨機一個非黑色的顏色的
            srand(time(NULL));
            play->color = ((rand() % 4) + 1);
            pokerpile = insertafter(pokerpile, makenode(play));
            *draw = changedraw(play->name);
        }
        else
        {
            pokerpile = insertafter(pokerpile, makenode(play));
            *draw = changedraw(play->name);
        }

        //刪掉電腦玩家手上的卡牌
        if(play->prev == NULL)//代表刪掉第一張
        {
            if(play->next == NULL)//刪掉的是最後一張
            {
                (*computerusercard) = NULL;
                free(play);
            }
            else
            {
                (*computerusercard) = play->next;
                (*computerusercard)->prev = NULL;
                free(play);
            }
        }
        else if(play->next == NULL)//刪掉最後一張牌
        {
            node *playprev;
            playprev = play->prev;
            playprev->next = NULL;
            free(play);
        }
        else
        {
            //刪掉中間的牌
            node *playprev;
            playprev = play->prev;
            play = deleteafter(playprev, play);
        }
    }
    return pokerpile;//回傳牌池的頭
}




/*void countcolor(int cardcolor)
{
    switch(cardcolor)
    {
        case red:
            redcount +=1;
            break;
        case blue:
            bluecount +=1;
            break;
        case yellow:
            yellowcount +=1;
            break;
        case green:
            greencount +=1;
            break;
        case black:
            blackcount +=1;
            break;
        default:
            break;
    }
}*/



#endif