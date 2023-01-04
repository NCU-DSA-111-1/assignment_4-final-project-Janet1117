#include "function.h"

#define not_conform_to_the_rule 0 //不符合條件
#define conform_to_the_rule 1 //符合出牌規則或出的牌為wild
#define this_card_is_drawtwo 2 //符合規則且出的牌為drawtwo
#define this_card_is_wild_darwfour 4 //符合規則且出的牌為wild draw four
#define this_card_is_skip 5 //符合規則且出的牌為skip
#define this_card_is_reverse 6 //符合規則且出的牌為reverse

//function 填參數舉例 cardpool = ruleandrenewpokerpile(cardpool, inputcard, &drawnumber);
node *ruleandrenewpokerpile (node *pokerpile, node *card, int *draw)
{
    *draw = 0;//預設都先是0

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
            pokerpile->next = makenode(card);
            *draw = changedraw(card->name);
            
        }

        //牌為黑色且名稱為wild或wild draw four 將黑色改為輸入的顏色
        else if((card->color == black) && ((card->name == wild) || (card->name == wild_draw_four)))
        {
            changewildcolor(card);
            pokerpile->next = makenode(card);
            *draw = changedraw(card->name);
        }

        //出數字牌名稱卻為wild之類的牌
        else
        {
            *draw = not_conform_to_the_rule;
            return pokerpile;
        }

        pokerpile = pokerpile->next;
        return pokerpile;
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
    char wildcolor[7];
    while(1)
    {
        printf("請選擇要換的顏色:");
        scanf("%s", wildcolor);
        printf("%c\n", wildcolor[2]);
        if(wildcolor[2] == 'a')
        {
            printf("牌的顏色不可為黑\n");
            continue;
        }
        else
        {
            switch(wildcolor[2])
            {
                case 'd':
                    input->color = red;
                    break;

                case 'u':
                    input->color = blue;
                    break;
                
                case 'e':
                    input->color = green;
                    break;
                
                case 'l':
                    input->color = yellow;
                    break;

                default:
                    break;
            }
            break;
        }
    }
}

