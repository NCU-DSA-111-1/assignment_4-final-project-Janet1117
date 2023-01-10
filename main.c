#include<stdbool.h>
#include<stdio.h>
#include<stdlib.h>

#include "node.h"

//getopt使用
#include<ctype.h>
#include<unistd.h>
extern char *ptarg;
extern int optind;
extern int optopt;
extern int opterr;
extern int optreset;
int getopt(int argc,char *const *argv,const char *optstring);

int ch;
bool store = false;
bool load = false;

FILE *fptr;
//開新局為0,載入歷史紀錄為1  
int NeworOld;

int main(int argc,char *argv[]){

	//getopt
	opterr=0;
	while((ch=getopt(argc,argv,"ns:l:"))!=-1){
		switch(ch){
			case 'n':
				//printf("-n被印出");
				NeworOld=0;
				break;

			case 's':
				//printf("-s被印出 %s",optarg);
				store = true;
				if((fptr=fopen(optarg,"w"))==NULL){
					printf("File can not be opened.\n");
					return 0;
				}
				NeworOld=0;
				break;
			case 'l':
				//printf("-l被印出 %s",optarg);
				load = true;
				if((fptr=fopen(optarg,"r"))==NULL){
					printf("File can not be opened.\n");
					return 0;
				}
				NeworOld =1;
				break;
		}
	}
}