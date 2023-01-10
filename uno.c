#include"mode.h"

int main(){
    int ThreeOrFour;

    system("clear");

    printf("3人模式:您和兩名電腦玩家\n4人模式:您與三位電腦玩家\n\n");
    printf("請選擇您想要 3人模式 或 4人模式\n");
    printf("若想3人模式請輸入3，4人模式請輸入4:");
    scanf("%d", &ThreeOrFour);
    while ((ThreeOrFour != 3) && (ThreeOrFour != 4)){
        printf("若想3人模式請輸入3，4人模式請輸入4:");
        scanf("%d", &ThreeOrFour);
    }
    
    //3人模式
    if(ThreeOrFour == 3){
        ThreePlayer();
    }

    //4人模式
    else{
        FourPlayer();
    }
    return 0;
}