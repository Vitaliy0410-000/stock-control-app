#include "stockcontrol.h"

void add_product_for_administrator(){
    sqlite3 *db;
    int rc =sqlite3_open("product.db",&db);
    if(rc!=SQLITE_OK){
        fprintf(stderr,"connection error: %s\n",sqlite3_errmsg(db));
        return  ;
    }
    while(1){
        char title_for_db[100];
        printf("Write title product: \n");
        fgets(title_for_db,sizeof(title_for_db),stdin);
        title_for_db[strcspn(title_for_db,"\n")]='\0';

        char quantity[100];
        int quantity_int;
        printf("Write quantity product: \n");
        fgets(quantity,sizeof(quantity),stdin);
        if (sscanf(quantity, "%d", &quantity_int) != 1) {
            printf("Error: quantity must be a number!\n");
            continue;
        }
        char price[100];
        int price_int;
        printf("Write price product: \n");
        fgets(price,sizeof(price),stdin);
        if (sscanf(price, "%d", &price_int) != 1) {
            printf("Error: price must be a number!\n");
            continue;
        }

        sqlite3_stmt *stmt;
        const char *insert_sql="INSERT INTO products(title,quantity,price) VALUES  (?,?,?);";
        if(sqlite3_prepare_v2(db,insert_sql,-1,&stmt,NULL)!=SQLITE_OK){
            fprintf(stderr,"Eror preparation : %s\n",sqlite3_errmsg(db));
            continue;
        }
        sqlite3_bind_text(stmt, 1, title_for_db, -1, SQLITE_STATIC);
        sqlite3_bind_int(stmt, 2, quantity_int);
        sqlite3_bind_int(stmt, 3, price_int);

        rc = sqlite3_step(stmt);
        if (sqlite3_step(stmt)!= SQLITE_DONE) {
            fprintf(stderr, "Eror: %s\n", sqlite3_errmsg(db));
        } else {
            printf("User successfully add for database!\n", title_for_db);
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


void add_product_for_users(){
    sqlite3 *db;
    int rc =sqlite3_open("product.db",&db);
    if(rc!=SQLITE_OK){
        fprintf(stderr,"connection error: %s\n",sqlite3_errmsg(db));
        return  ;
    }
    while(1){
        char title_for_db[100];
        printf("Write title product: \n");
        fgets(title_for_db,sizeof(title_for_db),stdin);
        title_for_db[strcspn(title_for_db,"\n")]='\0';

        char quantity[100];
        int quantity_int;
        printf("Write quantity product: \n");
        fgets(quantity,sizeof(quantity),stdin);
        if (sscanf(quantity, "%d", &quantity_int) != 1) {
            printf("Error: quantity must be a number!\n");
            continue;
        }
        char price[100];
        int price_int;
        printf("Write price product: \n");
        fgets(price,sizeof(price),stdin);
        if (sscanf(price, "%d", &price_int) != 1) {
            printf("Error: price must be a number!\n");
            continue;
        }

        sqlite3_stmt *stmt;
        const char *insert_sql="INSERT INTO products(title,quantity,price) VALUES  (?,?,?);";
        if(sqlite3_prepare_v2(db,insert_sql,-1,&stmt,NULL)!=SQLITE_OK){
            fprintf(stderr,"Eror preparation : %s\n",sqlite3_errmsg(db));
            continue;
        }
        sqlite3_bind_text(stmt, 1, title_for_db, -1, SQLITE_STATIC);
        sqlite3_bind_int(stmt, 2, quantity_int);
        sqlite3_bind_int(stmt, 3, price_int);

        rc = sqlite3_step(stmt);
        if (sqlite3_step(stmt)!= SQLITE_DONE) {
            fprintf(stderr, "Eror: %s\n", sqlite3_errmsg(db));
        } else {
            printf("User successfully add for database!\n", title_for_db);
        }

        sqlite3_finalize(stmt);

        int stop_add;
        printf("if you want  stop press 1 ");
        scanf("%d",&stop_add);
        while (getchar() != '\n');
        if(stop_add ==1){
            sqlite3_close(db);
            users_panel();
            return;
    }
}
} 



int callback_for_product(void *data ,int argc,char **argv,char **col_name){
    printf("\nProduct details:\n");
    printf("--------------------------------\n");
    for(int i = 0; i < argc; i++) {
        if(strcmp(col_name[i], "quantity") == 0 || strcmp(col_name[i], "price") == 0) {
            printf("%-12s: %s\n", col_name[i], argv[i] ? argv[i] : "0");
        } else {
            printf("%-12s: %s\n", col_name[i], argv[i] ? argv[i] : "NULL");
        }
    }
    printf("--------------------------------\n");
    return 0;
}

void print_product(){
    sqlite3 *db;
    char *err_msg = 0;
    int rc =sqlite3_open("product.db",&db);
    if(rc!=SQLITE_OK){
        fprintf(stderr,"connection error: %s\n",sqlite3_errmsg(db));
        return  ;
    }
    const char *sql="SELECT id,title,quantity,price FROM products ORDER BY title;";
    rc=sqlite3_exec(db,sql,callback_for_product,NULL,&err_msg);
    if(rc != SQLITE_OK){
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
    }

    
    sqlite3_close(db);
    return ;
}

void seach_product_for_title(){
    sqlite3 *db;
    char search_for_title_product[100];
    
    int rc = sqlite3_open("product.db", &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Connection error: %s\n", sqlite3_errmsg(db));
        return;
    }
    
    printf("Enter the seach for the title: ");
    fgets(search_for_title_product, sizeof(search_for_title_product), stdin);
    search_for_title_product[strcspn(search_for_title_product, "\n")] = '\0'; 
    
    sqlite3_stmt *stmt;
    const char *sql = "SELECT id, title,quantity,price FROM products WHERE title LIKE ?;";
    
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Request preparation error: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return;
    }
    
    sqlite3_bind_text(stmt, 1, search_for_title_product, -1, SQLITE_STATIC);
    
    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        printf("\nFound user:\n");
        printf("ID: %d\n", sqlite3_column_int(stmt, 0));
        printf("Title: %s\n", sqlite3_column_text(stmt, 1));
        printf("Quantity: %d\n", sqlite3_column_int(stmt, 2));
        printf("Price: %d\n", sqlite3_column_int(stmt, 3));
    } else {
        printf("Product with title  '%s' not found.\n",search_for_title_product );
    }
    
    sqlite3_finalize(stmt);
    sqlite3_close(db);
}
void seach_product_for_quantity(){
    sqlite3 *db;
    char quantity_input[20];
    int search_quantity;

    int rc = sqlite3_open("product.db", &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Connection error: %s\n", sqlite3_errmsg(db));
        return;
    }
    
    printf("Enter the seach for the quantity: ");
    fgets(quantity_input, sizeof(quantity_input), stdin);
    if (sscanf(quantity_input, "%d", &search_quantity) != 1) {
        printf("Eror:Write only number!\n");
        sqlite3_close(db);
        return;
     
    
    sqlite3_stmt *stmt;
    const char *sql = "SELECT id, title,quantity,price FROM products WHERE quantity= ?;";
    
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Request preparation error: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return;
    }
    
    sqlite3_bind_int(stmt, 1, search_quantity);
    printf("\nSearch results by quantity(quantity = %d):\n", search_quantity);
    bool found = false;
    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        found = true;
        printf("ID:       %d\n", sqlite3_column_int(stmt, 0));
        printf("Title: %s\n", sqlite3_column_text(stmt, 1));
        printf("Quantity: %d\n", sqlite3_column_int(stmt, 2));
        printf("Price:     %.d\n", sqlite3_column_int(stmt, 3));
    }
    
    if (!found) {
        printf("Product with title  '%s' not found.\n",quantity_input );
    }
    
    
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    }
}


void seach_product_for_price(){
    sqlite3 *db;
    char price_input[20];
    int search_price;

    int rc = sqlite3_open("product.db", &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Connection error: %s\n", sqlite3_errmsg(db));
        return;
    }
    
    printf("Enter the seach for the price: ");
    fgets(price_input, sizeof(price_input), stdin);
    if (sscanf(price_input, "%d", &search_price) != 1) {
        printf("Eror:Write only number!\n");
        sqlite3_close(db);
        return;
     
    
    sqlite3_stmt *stmt;
    const char *sql = "SELECT id, title,quantity,price FROM products WHERE price= ?;";
    
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Request preparation error: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return;
    }
    
    sqlite3_bind_int(stmt, 1, search_price);
    printf("\nSearch results by price(price = %d):\n", search_price);
    bool found = false;
    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        found = true;
        printf("ID:       %d\n", sqlite3_column_int(stmt, 0));
        printf("Title: %s\n", sqlite3_column_text(stmt, 1));
        printf("Quantity: %d\n", sqlite3_column_int(stmt, 2));
        printf("Price:     %.d\n", sqlite3_column_int(stmt, 3));
    }
    
    if (!found) {
        printf("Product with price  '%s' not found.\n",price_input );
    }
    
    
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    }
}


void seach_product(){
    while(1){
    char input[100];
    if (fgets(input, sizeof(input), stdin) == NULL) {
        printf("Input error!\n");
        continue;
    }

    input[strcspn(input, "\n")] = '\0';
    printf("You can choice functions\n");
    printf("1 search  product for the title \n");
    printf("2 search product for the quantity\n");
    printf("3 seach product for the prise\n");
    printf("0 exit  \n");
    
    if (!is_all_digits(input)) {
        printf("Invalid input. Only numbers allowed!\n");
        continue;
    }

    int choice = atoi(input);
    switch(choice) {
        case 1: seach_product_for_title(); break;
        case 2: seach_product_for_quantity(); break;
        case 3: seach_product_for_price(); break;
        case 0: return;
        default: printf("Invalid choice! Please select 0-3.\n");
    }


}
}

void delete_product(){
    sqlite3 *db;
    char title_to_delete[100];
    
    int rc = sqlite3_open("product.db", &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Connection error: %s\n", sqlite3_errmsg(db));
        return;
    }
    
    printf("Enter the product title to be deleted: ");
    fgets(title_to_delete, sizeof(title_to_delete), stdin);
    title_to_delete[strcspn(title_to_delete, "\n")] = '\0'; 
    
    sqlite3_stmt *stmt;
    const char *sql = "DELETE FROM products WHERE title = ?;";
    
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Request preparation error: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return;
    }
    
    sqlite3_bind_text(stmt, 1, title_to_delete, -1, SQLITE_STATIC);
    
    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        fprintf(stderr, "Deletion error: %s\n", sqlite3_errmsg(db));
    } else {
        if (sqlite3_changes(db) > 0) {
            printf("Product '%s' successfully deleted!\n", title_to_delete);
        } else {
            printf("Product with title '%s' not found.\n", title_to_delete);
        }
    }
    
    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

void clear_product_table(){
    sqlite3 *db;
    char *err_msg = NULL;
    
    int rc = sqlite3_open("product.db", &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Connection error: %s\n", sqlite3_errmsg(db));
        return;
    }
    
    const char *sql = "DELETE FROM products;";
    
    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Table clearing error: %s\n", err_msg);
        sqlite3_free(err_msg);
    } else {
        printf("The users table has been successfully cleared!\n");
    }
    
    sqlite3_close(db);
}