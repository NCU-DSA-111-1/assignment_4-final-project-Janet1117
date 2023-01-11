#ifndef MODE_H
#define MODE_H
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include"node.h"
#include"stack.h"
#include"player.h"
#include"setupplayer.h"
#include"cardfunction.h"
#include"computeruser.h"

#define P(card) "\033[1;35m"#card"\033[m"
#define D(card) "\033[1;36m"#card"\033[m"
#define W(card) "\033[1;37m"#card"\033[m"

void ThreePlayer();//三人模式
void FourPlayer();//四人模式
void initialize();//初始化

void SetupThreePlayerCard();//三人模式開局每人發七張牌
void SetupFourPlayerCard();//四人模式開局每人發七張牌

void GameOver(int PlayerAmount);//遊戲是否結束1:是

void ComputerCurrentCard(node *player);//印出電腦玩家的牌


int i, j;
int WhoWin = -1;//誰獲勝 -1:遊戲繼續
int count;



//三人模式
void ThreePlayer(){
    system("clear");
    //規則介紹
    printf("uno規則:\n\nuno有108張牌，共有5種顏色和15種牌\n顏色分別為");
    printf("%s、",R(紅));
    printf("%s、",Y(黃));
    printf("%s、",G(綠));
    printf("%s",B(藍));
    printf("和黑色\n");
    printf("%s、",R(紅));
    printf("%s、",Y(黃));
    printf("%s和",G(綠));
    printf("%s",B(藍));
    printf("色分別有 0~9、禁止、迴轉和+2牌\n黑色有 萬用和+4");
    printf("\n\n以下特殊牌介紹:\n禁止:禁止下一位玩家出牌\n迴轉:反轉出排順序\n +2 :下一位玩家罰抽兩張牌\n萬用:將顏色改為");
    printf("%s、",R(紅));
    printf("%s、",Y(黃));
    printf("%s或",G(綠));
    printf("%s",B(藍));
    printf("色，顏色由玩家自定\n +4 :下一位玩家罰抽四張牌，並將顏色改為");
    printf("%s、",R(紅));
    printf("%s、",Y(黃));
    printf("%s或",G(綠));
    printf("%s",B(藍));
    printf("色，顏色由玩家自定");
    printf("\n\n以下為規則介紹:\n每位玩家開局一人隨機獲得七張牌\n玩家只能出與 已出牌池 最上面相同顏色、相同數字、萬用或+4\n沒牌可出時需抽一牌\n獲勝條件:玩家手上牌全出玩即獲勝\n\n");
    printf("\n以下出牌範例:\n以 %s 為例:請輸入:黃 0\n以 %s 為例:請輸入:黑 萬用，選擇要換的顏色:若想將顏色換成黃色，請輸入黃\n\n", Y(0), W(萬用));
    printf("%s",Y(規則閱讀完畢，是否開始遊戲?[y/n]:));
    scanf("%s", YorN);
    while (YorN[0] != 'y'){
        printf("%s",Y(規則閱讀完畢，是否開始遊戲?[y/n]:));
        scanf("%s", YorN);
    }
    
    system("clear");
    
    //遊戲設定
    PlayerNumber = 3;
    RevserseOrNot = 0;
    int player_amount = (int) sizeof(three_player_order) / sizeof(three_player_order[0]);
    
    initialize();
    count = 0;
    //打亂順序
    ShuffleOrder(three_player_order, player_amount);
    printf("出牌順序為:");
    for(i = 0; i < 3; i++){
        if(three_player_order[i] == 0){
            printf("玩家1 ");
        }else if(three_player_order[i] == 1){
            printf("玩家2 ");
        }else if(three_player_order[i] == 2){
            printf("玩家3 ");
        }
    }
    printf("\n您為玩家1\n\n");

    SetUpDeck();
    ShuffleDeck(stack, 108);
    while((stack[top].name == wild) || (stack[top].name == wild_draw_four)){
        ShuffleDeck(stack, 108);
    }
    //設置底牌
    UsedCard = DrawOne(UsedCard);
    printf("底牌是: ");
    PrintCard(UsedCard);
    printf("\n");

    //開局一人發七張牌
    SetupThreePlayerCard();

    while (WhoWin == -1){
        
        
        //真人玩家出牌
        if(three_player_order[order] == 0){
            PlayerInput();
            SpecialCardFunction(drawNumber, three_player_order, &order, PlayerNumber);
            //迴轉
            if(drawNumber == 6){
                if(RevserseOrNot == 0){
                    RevserseOrNot = 1;
                }else if(RevserseOrNot == 1){
                    RevserseOrNot = 0;
                }
            }
        }
        
        //玩家2出牌
        else if(three_player_order[order] == 1){
            cardpool = computeruser(UsedCard, &player2, &drawNumber);
            if(cardpool == UsedCard){
                printf("\n%s抽了一張牌\n", P(玩家2));
            }else{
                printf("\n%s出了", P(玩家2));
                PrintCard(cardpool);
                printf("\n");
            }
            UsedCard = cardpool;
            SpecialCardFunction(drawNumber, three_player_order, &order, PlayerNumber);
            //迴轉
            if(drawNumber == 6){
                if(RevserseOrNot == 0){
                    RevserseOrNot = 1;
                }else if(RevserseOrNot == 1){
                    RevserseOrNot = 0;
                }
            }
        }
        
        //玩家3出牌
        else if(three_player_order[order] == 2){
            cardpool = computeruser(UsedCard, &player3, &drawNumber);
            if(cardpool == UsedCard){
                printf("\n%s抽了一張牌\n", D(玩家3));
            }else{
                printf("\n%s出了", D(玩家3));
                PrintCard(cardpool);
                printf("\n");
            }
            UsedCard = cardpool;
            SpecialCardFunction(drawNumber, three_player_order, &order, PlayerNumber);
            //迴轉
            if(drawNumber == 6){
                if(RevserseOrNot == 0){
                    RevserseOrNot = 1;
                }else if(RevserseOrNot == 1){
                    RevserseOrNot = 0;
                }
            }
        }
        
        

        GameOver(3);//遊戲是否結束

        sleep(1);
        if((count == player_amount - 1) && (WhoWin == -1)){
            sleep(1);
            system("clear");
        }

        count = (count == 2) ? 0 : (count + 1);

        if(WhoWin == -1){
            printf("\n上一位玩家出的牌 : ");
            PrintCard(UsedCard);
            printf("\n");
        }
    
        if(RevserseOrNot % 2 == 0){
            order = (order == 2) ? 0 : (order + 1);
        }else{
            order = (order == 0) ? 2 : (order - 1);
        }
        
    }
    //獲勝玩家
    if(WhoWin == 0){
        printf("\033[1;33m恭喜您獲勝!\n\033[m");
    }else if(WhoWin == 1){
        printf("\033[1;33m玩家2獲勝!\n\033[m");
    }else if(WhoWin == 2){
        printf("\033[1;33m玩家3獲勝!\n\033[m");
    }
    
}

//四人模式
void FourPlayer(){
    system("clear");
    //規則介紹
    printf("uno規則:\n\nuno有108張牌，共有5種顏色和15種牌\n顏色分別為");
    printf("%s、",R(紅));
    printf("%s、",Y(黃));
    printf("%s、",G(綠));
    printf("%s",B(藍));
    printf("和黑色\n");
    printf("%s、",R(紅));
    printf("%s、",Y(黃));
    printf("%s和",G(綠));
    printf("%s",B(藍));
    printf("色分別有 0~9、禁止、迴轉和+2牌\n黑色有 萬用和+4");
    printf("\n\n以下特殊牌介紹:\n禁止:禁止下一位玩家出牌\n迴轉:反轉出排順序\n +2 :下一位玩家罰抽兩張牌\n萬用:將顏色改為");
    printf("%s、",R(紅));
    printf("%s、",Y(黃));
    printf("%s或",G(綠));
    printf("%s",B(藍));
    printf("色，顏色由玩家自定\n +4 :下一位玩家罰抽四張牌，並將顏色改為");
    printf("%s、",R(紅));
    printf("%s、",Y(黃));
    printf("%s或",G(綠));
    printf("%s",B(藍));
    printf("色，顏色由玩家自定");
    printf("\n\n以下為規則介紹:\n每位玩家開局一人隨機獲得七張牌\n玩家只能出與 已出牌池 最上面相同顏色、相同數字、萬用或+4\n沒牌可出時需抽一牌\n獲勝條件:玩家手上牌全出玩即獲勝\n\n");
    printf("\n以下出牌範例:\n以 %s 為例:請輸入:黃 0\n以 %s 為例:請輸入:黑 萬用，選擇要換的顏色:若想將顏色換成黃色，請輸入黃\n\n", Y(0), W(萬用));
    printf("%s",Y(規則閱讀完畢，是否開始遊戲?[y/n]:));
    scanf("%s", YorN);
    while (YorN[0] != 'y'){
        printf("%s",Y(規則閱讀完畢，是否開始遊戲?[y/n]:));
        scanf("%s", YorN);
    }
    
    system("clear");

    //遊戲設定
    PlayerNumber = 4;
    RevserseOrNot = 0;
    int player_amount = (int) sizeof(four_player_order) / sizeof(four_player_order[0]);
    
    void initialize();
    count = 0;

    //打亂順序
    ShuffleOrder(four_player_order, player_amount);
    printf("出牌順序為:");
    for(i = 0; i < 4; i++){
        if(four_player_order[i] == 0){
            printf("玩家1 ");
        }else if(four_player_order[i] == 1){
            printf("玩家2 ");
        }else if(four_player_order[i] == 2){
            printf("玩家3 ");
        }else if(four_player_order[i] == 3){
            printf("玩家4 ");
        }
    }
    printf("\n您為玩家1\n\n");

    SetUpDeck();
    ShuffleDeck(stack, 108);
    while((stack[top].name == wild) || (stack[top].name == wild_draw_four)){
        ShuffleDeck(stack, 108);
    }
    //設置底牌
    UsedCard = DrawOne(UsedCard);
    printf("底牌是: ");
    PrintCard(UsedCard);
    printf("\n");
    
    //開局一人發七張牌
    SetupFourPlayerCard();

    while (WhoWin == -1){
        
        //真人玩家出牌
        if(four_player_order[order] == 0){
            PlayerInput();
            SpecialCardFunction(drawNumber, four_player_order, &order, PlayerNumber);
            //迴轉
            if(drawNumber == 6){
                if(RevserseOrNot == 0){
                    RevserseOrNot = 1;
                }else if(RevserseOrNot == 1){
                    RevserseOrNot = 0;
                }
            }
        }
        
        //玩家2出牌
        else if(four_player_order[order] == 1){
            cardpool = computeruser(UsedCard, &player2, &drawNumber);
            if(cardpool == UsedCard){
                printf("\n%s抽了一張牌\n", P(玩家2));
            }else{
                printf("\n%s出了", P(玩家2));
                PrintCard(cardpool);
                printf("\n");
            }
            UsedCard = cardpool;
            SpecialCardFunction(drawNumber, four_player_order, &order, PlayerNumber);
            //迴轉
            if(drawNumber == 6){
                if(RevserseOrNot == 0){
                    RevserseOrNot = 1;
                }else if(RevserseOrNot == 1){
                    RevserseOrNot = 0;
                }
            }
        }
        
        //玩家3出牌
        else if(four_player_order[order] == 2){
            cardpool = computeruser(UsedCard, &player3, &drawNumber);
            if(cardpool == UsedCard){
                printf("\n%s抽了一張牌\n", D(玩家3));
            }else{
                printf("\n%s出了", D(玩家3));
                PrintCard(cardpool);
                printf("\n");
            }
            UsedCard = cardpool;
            SpecialCardFunction(drawNumber, four_player_order, &order, PlayerNumber);
            //迴轉
            if(drawNumber == 6){
                if(RevserseOrNot == 0){
                    RevserseOrNot = 1;
                }else if(RevserseOrNot == 1){
                    RevserseOrNot = 0;
                }
            }
        }

        //玩家4出牌
        else if(four_player_order[order] == 3){
            cardpool = computeruser(UsedCard, &player4, &drawNumber);
            if(cardpool == UsedCard){
                printf("\n%s抽了一張牌\n", W(玩家4));
            }else{
                printf("\n%s出了", W(玩家4));
                PrintCard(cardpool);
                printf("\n");
            }
            UsedCard = cardpool;
            SpecialCardFunction(drawNumber, four_player_order, &order, PlayerNumber);
            //迴轉
            if(drawNumber == 6){
                if(RevserseOrNot == 0){
                    RevserseOrNot = 1;
                }else if(RevserseOrNot == 1){
                    RevserseOrNot = 0;
                }
            }
        }
        

        GameOver(4);//判斷遊戲是否結束

        sleep(1);
        if((count == player_amount - 1) && (WhoWin == -1)){
            sleep(1);
            system("clear");
        }

        count = (count == 3) ? 0 : (count + 1);

        if(WhoWin == -1){
            printf("\n上一位玩家出的牌 : ");
            PrintCard(UsedCard);
            printf("\n");
        }
        
        if(RevserseOrNot % 2 == 0){
            order = (order == 3) ? 0 : (order + 1);
        }else{
            order = (order == 0) ? 3 : (order - 1);
        }
        
    }

    //獲勝玩家
    if(WhoWin == 0){
        printf("\033[1;33m恭喜您獲勝!\n\033[m");
    }else if(WhoWin == 1){
        printf("\033[1;33m玩家2獲勝!\n\033[m");
    }else if(WhoWin == 2){
        printf("\033[1;33m玩家3獲勝!\n\033[m");
    }else if(WhoWin == 3){
        printf("\033[1;33m玩家4獲勝!\n\033[m");
    }

}


void initialize(){
    node *player1 = NULL;//真人玩家手中的牌
    node *player2 = NULL;//電腦玩家手中的牌
    node *player3 = NULL;//電腦玩家手中的牌
    node *player4 = NULL;//電腦玩家手中的牌
    node *UsedCard = NULL;//已出的牌
    node *cardpool = NULL;
    input = makelist(input);
}


//遊戲結束 1:遊戲結束,0:遊戲繼續
void GameOver(int PlayerAmount){
    WhoWin = -1;
    if(PlayerAmount == 3){
        if(player1 == NULL){
            WhoWin = 0;
        }else if(player2 == NULL){
            WhoWin = 1;
        }else if(player3 == NULL){
            WhoWin = 2;
        }
    }else{
        if(player1 == NULL){
            WhoWin = 0;
        }else if(player2 == NULL){
            WhoWin = 1;
        }else if(player3 == NULL){
            WhoWin = 2;
        }else if(player4 == NULL){
            WhoWin = 3;
        }
    }
}

//開局一人7張牌
void SetupThreePlayerCard(){
    for(i = 0; i < 7; i++){
        player1 = DrawOne(player1);
        player2 = DrawOne(player2);
        player3 = DrawOne(player3);
    }
}

//開局一人7張牌
void SetupFourPlayerCard(){
    for(i = 0; i < 7; i++){
        player1 = DrawOne(player1);
        player2 = DrawOne(player2);
        player3 = DrawOne(player3);
        player4 = DrawOne(player4);
    }
}

void ComputerCurrentCard(node *player){
    node *tmp;
    tmp = player;
    while (tmp != NULL){
        PrintCard(tmp);
        tmp = tmp->next;
    }
    printf("\n");
}

#endif