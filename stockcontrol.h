#ifndef STOCKCONTROL_H
#define STOCKCONTROL_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <sqlite3.h>
#include <stdbool.h>

void main_menu_entry(); 
int is_all_digits(const char *str); 
void exits();
void menu_authorisation_for_admin(); 
void administration_panel();
void add_users();
int callback(void *data ,int argc,char **argv,char **col_name);
void clear_users_table();
void find_user_by_login();
void print_users();
void delete_user();
void add_product_for_administrator();
void add_product_for_users();
void print_product();
int callback_for_product(void *data ,int argc,char **argv,char **col_name);
void seach_product_for_title();
void seach_product();
void seach_product_for_quantity();
void seach_product_for_price();
void delete_product();
void clear_product_table();
void menu_authorisation_for_users();
void users_panel();
#endif