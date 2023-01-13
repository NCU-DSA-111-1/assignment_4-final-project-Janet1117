#ifndef STACK_H
#define STACK_H
#include<time.h>
#include"node.h"
#define STACKSIZE 108

int i, j;
int top = -1;

node stack[STACKSIZE];

node *UsedCard = NULL;//已出的牌
node *cardpool = NULL;

node SetCard(int color, int name);
void SetUpDeck();//設置108張牌並放入公用牌堆
void ShuffleDeck(node deck[], size_t amount);//洗牌
int empty();
int full();
void push(node data);
node pop();
node deal();//發一張牌
void reshuffledeck();//將已出的牌留最上面那張其他free，重新設置stack、洗牌

node SetCard(int Color, int Name){
    node card;
    card.color = Color;
    card.name = Name;
    card.next = NULL;
    card.prev = NULL;
    return card;
}

//設置108張牌並放入公用牌堆
void SetUpDeck(){
    node data;
    //red, yellow, green, blue
    for(i = 1; i < 5; i++){
        //每個顏色的0
        j = 0;
        data = SetCard(i, j);
        push(data);

        //每個顏色(黑以外)除0以外各2張
        for(j = 1; j < 13; j++){
            data = SetCard(i, j);
            push(data);
            push(data);
        }
    }
    //black
    for(i = 0, j = 13; j < 15; j++){
        data = SetCard(i ,j);
        push(data);
        push(data);
        push(data);
        push(data);
    }
    
}

//洗牌
void ShuffleDeck(node deck[], size_t amount){
    srand(time(NULL));
    if(amount > 1){
        size_t x;
        for(x = 0; x < amount; x++){
            size_t y = rand() / (RAND_MAX / (amount));
            node t = deck[y];
            deck[y] = deck[x];
            deck[x] = t;
        }
    }
}

int empty(){
    if(top == -1){
        return 1;
    }else{
        return 0;
    }
}

int full(){
    if(top == 107){
        return 1;
    }else{
        return 0;
    }
}

void push(node data){
    if(full() != 1){
        top++;
        stack[top] = data;
        stack[top].next = NULL;
        stack[top].prev = NULL;
    }
}

node pop(){
    node card;
    card = stack[top];
    top--;
    return card;
}

node deal(){
    node card;
    if(empty() == 1){
        reshuffledeck();
    }
    card = pop();
    return card;
}

//將已出的牌留最上面那張其他free，重新設置stack、洗牌
void reshuffledeck(){
    while(UsedCard != NULL){
        if((UsedCard == NULL) || (UsedCard->next == NULL)){
            break;
        }else{
            node *nextptr;
            nextptr = UsedCard->next;
            nextptr->next->prev = UsedCard;
            UsedCard->next = nextptr->next;
            free(nextptr);
        }
    }
    SetUpDeck();
    ShuffleDeck(stack, 108);
}

#endif