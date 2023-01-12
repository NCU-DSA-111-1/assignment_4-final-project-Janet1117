#ifndef STORE_H
#define STORE_h
#include"node.h"

void StoreAct(int order, node *cur, int IFpass);

//store 
typedef struct record{
	int order;//哪位玩家(真人玩家固定1)
	int IFpass;//動作
	node *card;
	struct record *prev;
	struct record *next;
}Record;

node StartCard;
int RealPlayer[14];

Record *head = NULL;
Record *current = NULL;

//store(order=玩家幾號,cur=要存的牌，ifpass->0為出牌,1為抽牌，2為被加牌)
void StoreAct(int order, node *cur, int IFpass){
    Record *tmp = (Record *)malloc(sizeof(Record));
    node *card = (node *)malloc(sizeof(node));;
    card->color = cur->color;
    card->name = cur->name;
    tmp->order = order;
    tmp->IFpass = IFpass;
    tmp->card = card;

    if(current == NULL){
		current = tmp;
		head = tmp;
		tmp->prev = NULL;
		tmp->next = NULL;

	}
	else{
		current -> next = tmp;

		tmp->prev = current;
		tmp->next = NULL;
		
		current = tmp;
	}

}

#endif