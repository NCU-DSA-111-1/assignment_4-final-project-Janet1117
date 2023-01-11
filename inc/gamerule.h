#ifndef GAMERULE_H
#define GAMERULE_H

#include "function.h"

#define not_conform_to_the_rule 0 //不符合條件
#define conform_to_the_rule 1 //符合出牌規則或出的牌為wild
#define this_card_is_drawtwo 2 //符合規則且出的牌為drawtwo
#define this_card_is_wild_darwfour 4 //符合規則且出的牌為wild draw four
#define this_card_is_skip 5 //符合規則且出的牌為skip
#define this_card_is_reverse 6 //符合規則且出的牌為reverse

//function 填參數舉例 cardpool = ruleandrenewpokerpile(cardpool, inputcard, &drawnumber);
node *ruleandrenewpokerpile (node *pokerpile, node *card, int *draw, node *head)
{
    *draw = 0;//預設都先是0

    //防呆
    if(foolproof(head, card) == 0)
    {
        *draw = 0;
        return pokerpile;
    }

    else
    {
        //數字和顏色都不同且不為黑牌 不符合條件 draw =0
        if((card->color != pokerpile->color) && (card->name != pokerpile->name) && (card->color != black))
        {
            *draw = not_conform_to_the_rule;
            return pokerpile;
        }

        //符合規則
        else
        {
            //顏色一樣或名稱一樣且名稱不為wild或wild draw four
            if(((card->color == pokerpile->color) || (card->name == pokerpile->name)) && ((card->name != wild) && (card->name != wild_draw_four)))
            {
                pokerpile = insertafter(pokerpile, makenode(card));
                *draw = changedraw(card->name);
            }

            //牌為黑色且名稱為wild或wild draw four 將黑色改為輸入的顏色
            else if((card->color == black) && ((card->name == wild) || (card->name == wild_draw_four)))
            {
                changewildcolor(card);
                pokerpile = insertafter(pokerpile, makenode(card));
                *draw = changedraw(card->name);
            }

            //出數字牌名稱卻為wild之類的牌
            else
            {
                *draw = not_conform_to_the_rule;
                return pokerpile;
            }

            return pokerpile;
        }
    }
    
    

}

//建立新的節點
node *makenode(node *input)
{
    node *tmp;
    tmp = (node *)malloc(sizeof(node));
    tmp->color = input->color;
    tmp->name = input->name;
    tmp->next = NULL;
    tmp->prev = NULL;
    return tmp;
}

//更改draw的值
int changedraw(int cardname)
{
    switch(cardname)
    {
        case drawtwo:
            return this_card_is_drawtwo;
            break;
        
        case wild_draw_four:
            return this_card_is_wild_darwfour;
            break;

        case skip:
            return this_card_is_skip;
            break;

        case reverse:
            return this_card_is_reverse;
            break;

        default:
            return conform_to_the_rule;
            break;
    }

}

//更改黑色 將黑色改成使用者輸入的顏色
void changewildcolor(node *input)
{
    char wildcolor[20];
    while(1)
    {
        printf("請選擇要換的顏色:");
        scanf("%s", wildcolor);
        if(strcmp(wildcolor,"黑") == 0)
        {
            printf("牌的顏色不可為黑\n");
            continue;
        }
        else if(strcmp(wildcolor,"紅") == 0)
        {
            input->color = red;
            break;
        }
        else if(strcmp(wildcolor,"藍") == 0)
        {
            input->color = blue;
            break;
        }
        else if(strcmp(wildcolor,"綠") == 0)
        {
            input->color = green;
            break;
        }
        else if(strcmp(wildcolor,"黃") == 0)
        {
            input->color = yellow;
            break;
        }
        else
        {
            printf("沒這個顏色 請重新輸入");
            continue;
        }
    }
}

//新增在找到尾吧的linkedlist之後
node *insertafter(node *list, node *insert)
{
    list->next = insert;
    insert->prev = list;
    list = list->next;
    list->next = NULL;
    return list;
}

node *deleteafter(node *list, node *card)
{
    node *tmp;
    tmp = card->next;

    list->next = tmp;
    tmp->prev = list;
    free(card);
    return list;
}

//回傳0 沒有這張牌 回傳1 有這張牌
int foolproof(node *list, node *card)//如果要傳node進來自己改就行
{
    node *tmp;
    tmp = list;
    int switched = 0;

    while(tmp != NULL)
    {
        if((switched == 0) && ((tmp->color == card->color) && (tmp->name == card->name)))
        {
            switched = 1;
            break;
        }
        tmp = tmp->next;
    }

    return switched;//有這張牌回傳1 沒有回傳0
}



#endif