#include "stockcontrol.h"


void users_panel(){
    while(1){
        char input[100];
        printf("============================\t\n");
        printf("Hello users!!!\n");
        printf("You can choice functions\n");
        printf("1 add product\n");
        printf("2 print product \n");
        printf("3 search product for id  \n");
        printf("4 delete product for id \n");
        printf("5 exit  \n");
        if (fgets(input, sizeof(input), stdin) == NULL) {
            printf("Input error!\n");
            continue;
        }

        input[strcspn(input, "\n")] = '\0';

        
        if (!is_all_digits(input)) {
            printf("Invalid input. Only numbers allowed!\n");
            continue;
        }

        int choice = atoi(input);
        switch(choice) {
            case 1: add_product_for_users(); break;
            case 2: print_product(); break;
            case 3: seach_product(); break;
            case 4: delete_product(); break;
            case 5: exits();break;
            default: printf("Invalid choice! Please select 1-5.\n");
     
        }
    }
}

