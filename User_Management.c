#include<stdio.h>
#include<string.h>
#include <conio.h>

#define MAX_USERS 10
#define Credential_Length 30

typedef struct {
    char username[Credential_Length];
    char password[Credential_Length];
} User;

User users[MAX_USERS];
int userCount = 0;

void registerUser();
int loginUser();
void fix_fgets_input(char*);
void input_credentials(char* username, char* password);
void input_password(char* password);


int main() {
    int options;
    int loginResult;
    while(1) {
    printf("\n=== User Management System ===\n\n");
    printf("1. Add User\n");
    printf("2. Log In\n");
    printf("3. Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &options);
    getchar();

    switch (options) {
        case 1:
            registerUser();
            break;
        case 2:
            loginResult = loginUser();
            if (loginResult >= 0) {
                printf("Login successful! Welcome, %s!\n", users[loginResult].username);
            } else {
                printf("Login failed! Incorrect username or password\n");
            }
            break;
        case 3:
            printf("Exiting...\n");
            return 0;
            break;
        default:
            printf("Invalid option. Please try again.\n");
            break;
    }
}
    return 0;
}

void registerUser() {
    if (userCount == MAX_USERS) {
        printf("Maximum %d users are supported! No more registrations allowed.\n", MAX_USERS);
        return;
    }

    char username[Credential_Length];
    char password[Credential_Length];

    printf("Registering new user...\n");
    printf("Enter username: ");
    fgets(username, Credential_Length, stdin);
    fix_fgets_input(username);

    if (strlen(username) == 0) {
        printf("Username cannot be empty. Registration failed.\n");
        return;
    }
    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].username, username) == 0) {
            printf("Username already exists. Registration failed.\n");
            return;
        }
    }
    printf("Enter password: ");
    input_password(password);

    if (strlen(password) == 0) {
        printf("Password cannot be empty. Registration failed.\n");
        return;
    }

    strncpy(users[userCount].username, username, Credential_Length);
    strncpy(users[userCount].password, password, Credential_Length);
    userCount++;

    printf("User registered successfully!\n");
}

int loginUser() {
    char username[Credential_Length];
    char password[Credential_Length];

    printf("Enter username: ");
    fgets(username, Credential_Length, stdin);
    fix_fgets_input(username);

    printf("Enter password: ");
    input_password(password);

    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            return i;
        }
    }
    return -1;
}

    void input_password(char* password) {
    int index = 0;
    char ch;

    while ((ch = getch()) != '\r' && index < Credential_Length - 1) {
        if (ch == '\b') { // Handle backspace
            if (index > 0) {
                index--;
                printf("\b \b");
            }
        } else {
            password[index++] = ch;
            printf("*");
        }
    }
    password[index] = '\0';
    printf("\n");
}

void fix_fgets_input(char* input) {
    int index = strcspn(input, "\n");
    input[index] = '\0';
}
