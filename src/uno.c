#include<stdbool.h>
#include<stdio.h>
#include<stdlib.h>

#include "../inc/store.h"
#include "../inc/mode.h"
//getopt使用
#include<ctype.h>
// #include<unistd.h>
// extern char *ptarg;
// extern int optind;
// extern int optopt;
// extern int opterr;
// extern int optreset;
// int getopt(int argc,char *const *argv,const char *optstring);

// int ch;
// bool store = false;
// bool load = false;

FILE *fptr;
//開新局為0,載入歷史紀錄為1  
//int NeworOld;


//store
int players;
extern node StartCard;
extern int RealPlayer[14]; 

//指標
extern Record *head;
extern Record *current;

char *filename;//檔名

int main(int argc, char **argv) {
    
    char n[] = "-n";//-n
    char s[] = "-s";//-s
    char l[] = "-l";//-l
    if(argc == 4){//除程式本身外還有三個參數
        if(strncmp(argv[1], n, 2) == 0){
            if(strncmp(argv[2], s, 2) == 0){
                filename = argv[3];
                if((fptr = fopen(filename, "w")) == NULL){
                    printf("\033[1;31m無法創建檔案!\033[m");
                }else{
					//new game
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

					//save
					printf("儲存中...\n");
					fprintf(fptr,"%d\n", players);
					fprintf(fptr,"%d %d\n", StartCard.color, StartCard.name);
					//only store player
					for(int i = 0; i < 7; ++i)
						fprintf(fptr,"%d %d ", RealPlayer[i*2],RealPlayer[i*2+1]);
					fprintf(fptr,"\n");
					
					while (head != NULL)
					{
						fprintf(fptr,"%d %d %d %d\n", head->order, head->IFpass, head->card->color, head->card->name);
						printf("%d %d %d %d\n", head->order, head->IFpass, head->card->color, head->card->name);
						head = head->next;
					}
                }
                fclose(fptr);
            }
            else{
                printf("輸入格式錯誤!\n");
            }
        }
        else{
            printf("輸入格式錯誤!\n");
        }
    
    }
    else if(argc == 3){//除程式本身外還有兩個參數
        if(strncmp(argv[1], l, 2) == 0){
            filename = argv[2];
            if((fptr = fopen(filename, "r")) == NULL){
                printf("\033[1;31m找不到檔案!\033[m");
            }
            else{
                //load
				char data[50];
				char color[50], name[50];
				fseek(fptr, SEEK_SET, 0);
				printf("載入紀錄\n");
				//printf("載入\033[1;37m %s \033[m紀錄\n", filename);
				fscanf(fptr,"%s\n", data);
				if(atoi(data)== 3){
					printf("三人局\n");
				}
				else if(data[0] == '4'){
					printf("四人局\n");
				}
				fscanf(fptr,"%s %s\n",color, name);
				node tmp;
				tmp.color = atoi(color);
				tmp.name = atoi(name);
				printf("底牌是: ");
				PrintCard(&tmp);
				printf("\n");
				node *current = NULL;
				for(int i = 0; i < 7; ++i){
					fscanf(fptr,"%s %s\n",color, name);
					node *newnode;
					newnode = (node *) malloc (sizeof(node));
					newnode->color = atoi(color);
					newnode->name = atoi(name);
					if(current == NULL) {
						player1 = newnode;
						current = newnode;
						newnode->next = newnode->prev = NULL;
					}else{
						current -> next = newnode;

						newnode->prev = current;
						newnode->next = NULL;
				
						current = newnode;
					}
				}
				PlayerCurrentCard();
				char ifpass[50];
				int ID;
				while(fscanf(fptr,"%s %s %s %s", data, ifpass,color, name) != EOF){
					printf("現在是玩家 %s\n", data);
					ID = atoi(data);
					int flag = ifpass[0]; // '1' 
					//fscanf(fptr,"%s %s\n", color, name);
					//printf("%s %s %s %s\n",data, ifpass, color, name );
					if(ID == 1){
					if( flag > 48 && flag < 51 ){
						if(flag == 49)
							printf("pass :");
						else
							printf("抽到 :");
						node *newnode;
						newnode = (node *) malloc (sizeof(node));
						newnode->color = atoi(color);
						newnode->name = atoi(name);
						newnode->next = player1->next;
						newnode->prev = player1;
						if(player1->next != NULL){
							player1->next->prev = newnode;
						}
						player1->next = newnode; 
						PrintCard(newnode);   
						printf("\n");
					}
					else{
						printf("usedCard :");
						if(flag == 51 /*black*/){
						
							tmp.color = 0;
						}
						else{
							tmp.color = atoi(color);
							//printf("%d", atoi(color));
						}
							tmp.name = atoi(name);
							PrintCard(&tmp);
							printf("\n");
							player1 = deletecard(player1, tmp);
							if(flag == 51 /*black*/){
								printf("玩家選擇顏色:");
								if(atoi(color) == yellow){
									printf("%s\n",Y(yellow));
								}
								else if(atoi(color) == red){
									printf("%s\n", R(red));
								}
								else if(atoi(color) == green){
									printf("%s\n", G(green));
								}
								else if(atoi(color) == blue){
									printf("%s\n", B(blue));
								}

						}
					}
					if(player1 != NULL){
						PlayerCurrentCard();
					}
					else{
						printf("你贏了\n");
					}
					
					}
					else if(ID == 2){
						if( flag == 49 )
							printf("玩家2抽了一張牌\n");
						else{
							printf("usedCard :");
							tmp.color = atoi(color);
							tmp.name = atoi(name);
							PrintCard(&tmp);
							printf("\n");
						}
					}
					else if(ID == 3){
						if( flag == 49 )
							printf("玩家3抽了一張牌\n");
						else{
							printf("usedCard :");
							tmp.color = atoi(color);
							tmp.name = atoi(name);
							PrintCard(&tmp);
							printf("\n");
						}
					}
					else if(ID == 4){
						if( flag == 49 )
							printf("玩家4抽了一張牌\n");
						else{
							printf("usedCard :");
							tmp.color = atoi(color);
							tmp.name = atoi(name);
							PrintCard(&tmp);
							printf("\n");
						}
					}
				}
				printf("遊戲結束！\n");
            }
        }
        else{
            printf("輸入格式錯誤\n");
        }
        fclose(fptr);
    }
    else{
        printf("輸入格式錯誤!\n");
    }
}

