#include "stockcontrol.h"

void administration_panel();
void users_panel();

void menu_authorisation_for_admin(){ 
    printf("======================================\n\t");
    const char login_admin[]="Vitaliy";
    const int password_admin=47894789;
    char user_login[100];
    int user_password;
    while(1){
    printf("Hello i am authorisation menu for the administrator!\n");
    printf("Write me you login:\n");
    scanf("%s",user_login);
    printf("write me you password:\n");
    scanf("%d",&user_password);
    if (strcmp(user_login, login_admin) == 0 && user_password == password_admin) {
        printf("Authorisation granted. Welcome Vitaly!\n");
        administration_panel();
        break;
    } else {
        printf("error. Wrong password!!!!.\n");
    }
    }
    printf("======================================\n");
}


void menu_authorisation_for_users(){
    sqlite3 *db;
    char user_login[100];
    char password_input[20];
    int user_password;

    int rc = sqlite3_open("users_password_and_login.db", &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Connection error: %s\n", sqlite3_errmsg(db));
        return;
    }

    while (1) {
        printf("======================================\n");
        printf("Hello user!\n");


        printf("Enter your login: ");
        fgets(user_login, sizeof(user_login), stdin);
        user_login[strcspn(user_login, "\n")] = '\0';

    
        printf("Enter your password (number only): ");
        fgets(password_input, sizeof(password_input), stdin);
        if (sscanf(password_input, "%d", &user_password) != 1) {
            printf("Error: Password must be a number!\n");
            continue; 
        }

        sqlite3_stmt *stmt;
        const char *sql = "SELECT id, login FROM users WHERE login = ? AND password = ?;";

        rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
        if (rc != SQLITE_OK) {
            fprintf(stderr, "Query preparation error: %s\n", sqlite3_errmsg(db));
            sqlite3_close(db);
            return;
        }

        sqlite3_bind_text(stmt, 1, user_login, -1, SQLITE_TRANSIENT);
        sqlite3_bind_int(stmt, 2, user_password);

        
        rc = sqlite3_step(stmt);
        if (rc == SQLITE_ROW) {
            printf("\n User authorized successfully!\n");
            printf("ID: %d\n", sqlite3_column_int(stmt, 0));
            printf("Login: %s\n", sqlite3_column_text(stmt, 1));
            sqlite3_finalize(stmt);
            users_panel();
        } else {
            printf(" Incorrect login or password. Try again.\n");
        }

        sqlite3_finalize(stmt);
    }

    sqlite3_close(db);
}
