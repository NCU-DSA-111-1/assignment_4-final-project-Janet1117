#ifndef CARDFUNCTION_H
#define CARDFUNCTION_H
#include<stdlib.h>
#include<stdio.h>


void reverse(int player_order[], int player_number);

//迴轉: player_order[]:玩家出排順序陣列、player_number:玩家數量
void reverse(int player_order[], int player_number){
    int tmp;
    for(int low = 0, high = player_number - 1; low < high; low++, high--){
        tmp = player_order[low];
        player_order[low] = player_order[high];
        player_order[high] = tmp;
    }
}


#endif