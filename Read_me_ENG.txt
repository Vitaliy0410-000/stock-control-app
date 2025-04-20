# 🛒 Stock Control Application

Hello! This is my **first educational project** written in the **C programming language**.
You are welcome to use this project for **educational** or **personal purposes**.

---

## 📚 What I learned during this project:

- basics of the **C language**;
- working with **SQLite databases**;
- understanding the **structure of an application**;
- using **Git version control system**.

---

## 🚀 Description

A C application using **SQLite**, designed for:

- managing products (adding, deleting, clearing the table);
- user authorization through a database;
- separate menus for **users** and **administrators**.

---

## ⚙️ Technologies used:

- C
- SQLite3
- Linux (Manjaro)
- GCC

---

## 📁 Project structure:

- `main.c` — entry point
- `main_menu_entry.c` — main menu
- `auth.c` — authorization menu for user or admin
- `product.c` — product management
- `user.c` — menu for regular users
- `admin.c` — menu for administrators
- `utils.c` — utility functions
- `product.db` — product database
- `users_password_and_login.db` — user database

---

## 🛠️ Build and run:

```bash
gcc -o Stock_Safe *.c -lsqlite3
./Stock_Safe
