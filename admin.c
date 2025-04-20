#include "stockcontrol.h"

int is_all_digits(const char *str);
void exits();

void add_users(){
    sqlite3 *db;
    int rc =sqlite3_open("users_password_and_login.db",&db);
    if(rc!=SQLITE_OK){
        fprintf(stderr,"connection error: %s\n",sqlite3_errmsg(db));
        return  ;
    }
    while(1){
        char login_for_db[100];
        printf("Write login user: \n");
        fgets(login_for_db,sizeof(login_for_db),stdin);
        login_for_db[strcspn(login_for_db,"\n")]='\0';

        char password_input[100];
        int password_int;
        printf("Write password user: \n");
        fgets(password_input,sizeof(password_input),stdin);
        if (sscanf(password_input, "%d", &password_int) != 1) {
            printf("Error: password must be a number!\n");
            continue;
        }

        sqlite3_stmt *stmt;
        const char *insert_sql="INSERT INTO users(login,password) VALUES  (?,?);";
        if(sqlite3_prepare_v2(db,insert_sql,-1,&stmt,NULL)!=SQLITE_OK){
            fprintf(stderr,"Eror preparation : %s\n",sqlite3_errmsg(db));
            continue;
        }
        sqlite3_bind_text(stmt, 1, login_for_db, -1, SQLITE_STATIC);
        sqlite3_bind_int(stmt, 2, password_int);

        if (sqlite3_step(stmt)!= SQLITE_DONE) {
            fprintf(stderr, "Eror: %s\n", sqlite3_errmsg(db));
        } else {
            printf("User successfully add for database!\n", login_for_db);
        }

        sqlite3_finalize(stmt);

        int stop_add;
        printf("if you want  stop press 1 ");
        scanf("%d",&stop_add);
        while (getchar() != '\n');
        if(stop_add ==1){
            sqlite3_close(db);
            administration_panel();
            return;
    }
}

}


int callback(void *data ,int argc,char **argv,char **col_name){
    printf("Users : \n");
    for(int i=0;i<argc;i++){
        printf("  %s:  %s\n",col_name[i],argv[i]? argv[i]: "NULL");
    }
    return 0;
}

void print_users(){
    sqlite3 *db;
    char *err_msg = 0;
    int rc =sqlite3_open("users_password_and_login.db",&db);
    if(rc!=SQLITE_OK){
        fprintf(stderr,"connection error: %s\n",sqlite3_errmsg(db));
        return  ;
    }
    char *sql="SELECT login,password FROM users;";
    rc=sqlite3_exec(db,sql,callback,0,&err_msg);
    if(rc != SQLITE_OK){
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
    }

    
    sqlite3_close(db);
    return ;
}


void find_user_by_login() {
    sqlite3 *db;
    char search_login[100];
    
    int rc = sqlite3_open("users_password_and_login.db", &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Connection error: %s\n", sqlite3_errmsg(db));
        return;
    }
    
    printf("Enter the user login for the search: ");
    fgets(search_login, sizeof(search_login), stdin);
    search_login[strcspn(search_login, "\n")] = '\0'; 
    
    sqlite3_stmt *stmt;
    const char *sql = "SELECT id, login, password FROM users WHERE login = ?;";
    
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Request preparation error: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return;
    }
    
    sqlite3_bind_text(stmt, 1, search_login, -1, SQLITE_STATIC);
    
    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        printf("\nFound user:\n");
        printf("ID: %d\n", sqlite3_column_int(stmt, 0));
        printf("Login: %s\n", sqlite3_column_text(stmt, 1));
        printf("Password: %d\n", sqlite3_column_int(stmt, 2));
    } else {
        printf("User with login  '%s' not found.\n", search_login);
    }
    
    sqlite3_finalize(stmt);
    sqlite3_close(db);
}


void delete_user() {
    sqlite3 *db;
    char login_to_delete[100];
    
    int rc = sqlite3_open("users_password_and_login.db", &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Connection error: %s\n", sqlite3_errmsg(db));
        return;
    }
    
    printf("Enter the user login for the user to be deleted: ");
    fgets(login_to_delete, sizeof(login_to_delete), stdin);
    login_to_delete[strcspn(login_to_delete, "\n")] = '\0'; 
    
    sqlite3_stmt *stmt;
    const char *sql = "DELETE FROM users WHERE login = ?;";
    
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Request preparation error: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return;
    }
    
    sqlite3_bind_text(stmt, 1, login_to_delete, -1, SQLITE_STATIC);
    
    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        fprintf(stderr, "Deletion error: %s\n", sqlite3_errmsg(db));
    } else {
        if (sqlite3_changes(db) > 0) {
            printf("User '%s' successfully deleted!\n", login_to_delete);
        } else {
            printf("User with login '%s' not found.\n", login_to_delete);
        }
    }
    
    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

void clear_users_table() {
    sqlite3 *db;
    char *err_msg = NULL;
    
    int rc = sqlite3_open("users_password_and_login.db", &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Connection error: %s\n", sqlite3_errmsg(db));
        return;
    }
    
    const char *sql = "DELETE FROM users;";
    
    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Table clearing errorы: %s\n", err_msg);
        sqlite3_free(err_msg);
    } else {
        printf("The users table has been successfully cleared!\n");
    }
    
    sqlite3_close(db);
}


void administration_panel(){
    while(1){
        char input[100];
        printf("============================\t\n");
        printf("Hello administrator!!!\n");
        printf("You can choice functions\n");
        printf("1 add user\n");
        printf("2 print user\n");
        printf("3 seach user for login\n");
        printf("4 delete user for login\n");
        printf("0 clean data base users  \n");
        printf("5 add product\n");
        printf("6 print product \n");
        printf("7 search product for id  \n");
        printf("8 delete product for id \n");
        printf("9 exit  \n");
        printf("10 clean data base product exit  \n");

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
            case 1: add_users(); break;
            case 2: print_users(); break;
            case 3: find_user_by_login(); break;
            case 4: delete_user(); break;
            case 0: clear_users_table(); break;
            case 5: add_product_for_administrator(); break;
            case 6: print_product(); break;
            case 7: seach_product(); break;
            case 8: delete_product(); break;
            case 9: exits();break;
            case 10:clear_product_table(); return;  
            default: printf("Invalid choice! Please select 0-10.\n");
     
        }
    }
}
