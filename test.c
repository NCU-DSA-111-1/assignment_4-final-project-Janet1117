//#include"mode.h"
#include"cardfunction.h"
int main(){
    
    int three_player_order[3] = {0, 1, 2};
    int four_player_order[4] = {0, 1, 2, 3};
    reverse(three_player_order, 3);
    reverse(four_player_order, 4);

    int i;
    for(i = 0; i < 3; i++){
        printf("%d  ", three_player_order[i]);
    }
    printf("\n");

    for(i = 0; i < 4; i++){
        printf("%d  ", four_player_order[i]);
    }
    printf("\n");
    return 0;
}