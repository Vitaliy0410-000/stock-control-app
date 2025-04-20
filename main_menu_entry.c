#include "stockcontrol.h"
int is_all_digits(const char *str);
void exits();
void menu_authorisation_for_admin(); 


void main_menu_entry(){
    while(1){
        char choose_for_menu_entry[100];
        printf("======================================\n\t");
        printf("Hello this program stock control!!!\n");
        printf("Choose who you want to log in as\n");
        printf("press: -> 2 if you want to log in as administration\n");
        printf("press: -> 1 if you want to log in as user\n");
        printf("press: -> 0 if you want to exit\n");
        scanf("%s",choose_for_menu_entry);
        printf("======================================\n");
        if(is_all_digits(choose_for_menu_entry)){
            int choose=atoi(choose_for_menu_entry);
            if(choose==1){
                menu_authorisation_for_users();
            }
            else if(choose==2){
                menu_authorisation_for_admin();
            }
            else if(choose==0){
                 exits();
            }else{
                printf("Invalid input. Please press only 1 or 2 or 0!\n");
            }

        }
        else{
            printf("Invalid input. Only numbers allowed!\n");
        }

    }
}