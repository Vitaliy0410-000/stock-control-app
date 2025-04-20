#include "stockcontrol.h"

int is_all_digits(const char *str){
    for(int i=0;str[i]!='\0';i++){
        if(!isdigit(str[i])) return 0;
    }
    return 1;
}

void exits(){
    printf("Good lucky!!\n");
    exit(1);
}