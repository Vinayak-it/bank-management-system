#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Account {
    int accountNumber;
    char name[50];
    float balance;
    struct Account* next;
};

struct Account* head = NULL;

struct Account* findAccount(int accNo) {
    struct Account* current = head;
    while (current != NULL) {
        if (current->accountNumber == accNo) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

void createAccount() {
    int accNo;
    printf("\nEnter Account Number: ");
    scanf("%d", &accNo);

    if (findAccount(accNo) != NULL) {
        printf("Error: An account with number %d already exists.\n", accNo);
        return;
    }

    struct Account* newAccount = (struct Account*)malloc(sizeof(struct Account));
    if (newAccount == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }

    newAccount->accountNumber = accNo;
    printf("Enter Name: ");
    scanf(" %[^\n]", newAccount->name);
    printf("Enter Initial Deposit: $");
    scanf("%f", &newAccount->balance);

    newAccount->next = head;
    head = newAccount;

    printf("Account created successfully!\n");
}

void deposit() {
    int accNo;
    float amount;
    printf("\nEnter Account Number: ");
    scanf("%d", &accNo);

    struct Account* acc = findAccount(accNo);
    if (acc == NULL) {
        printf("Account not found.\n");
        return;
    }

    printf("Enter Deposit Amount: $");
    scanf("%f", &amount);

    if (amount <= 0) {
        printf("Invalid amount.\n");
        return;
    }

    acc->balance += amount;
    printf("Deposited $%.2f. New Balance: $%.2f\n", amount, acc->balance);
}

void withdraw() {
    int accNo;
    float amount;
    printf("\nEnter Account Number: ");
    scanf("%d", &accNo);

    struct Account* acc = findAccount(accNo);
    if (acc == NULL) {
        printf("Account not found.\n");
        return;
    }

    printf("Enter Withdrawal Amount: $");
    scanf("%f", &amount);

    if (amount <= 0) {
        printf("Invalid amount.\n");
        return;
    }

    if (amount > acc->balance) {
        printf("Insufficient balance! Current Balance: $%.2f\n", acc->balance);
        return;
    }

    acc->balance -= amount;
    printf("Withdrew $%.2f. New Balance: $%.2f\n", amount, acc->balance);
}

void checkBalance() {
    int accNo;
    printf("\nEnter Account Number: ");
    scanf("%d", &accNo);

    struct Account* acc = findAccount(accNo);
    if (acc == NULL) {
        printf("Account not found.\n");
        return;
    }

    printf("\n--- Account Details ---\n");
    printf("Account No: %d\n", acc->accountNumber);
    printf("Holder:     %s\n", acc->name);
    printf("Balance:    $%.2f\n", acc->balance);
}

void displayAll() {
    if (head == NULL) {
        printf("\nNo accounts registered yet.\n");
        return;
    }

    struct Account* current = head;
    printf("\n%-12s %-20s %-10s\n", "Account No", "Name", "Balance");
    printf("--------------------------------------------\n");
    while (current != NULL) {
        printf("%-12d %-20s $%-10.2f\n", current->accountNumber, current->name, current->balance);
        current = current->next;
    }
}

void cleanup() {
    struct Account* current = head;
    while (current != NULL) {
        struct Account* temp = current;
        current = current->next;
        free(temp);
    }
}

int main() {
    int choice;

    while (1) {
        printf("\n=== Bank Management System ===\n");
        printf("1. Create Account\n");
        printf("2. Deposit Money\n");
        printf("3. Withdraw Money\n");
        printf("4. Check Balance\n");
        printf("5. Display All Accounts\n");
        printf("6. Exit\n");
        printf("Enter your choice (1-6): ");
        if (scanf("%d", &choice) != 1) {
            break;
        }

        switch (choice) {
            case 1: createAccount(); break;
            case 2: deposit(); break;
            case 3: withdraw(); break;
            case 4: checkBalance(); break;
            case 5: displayAll(); break;
            case 6:
                cleanup();
                printf("Exiting system. Goodbye!\n");
                return 0;
            default:
                printf("Invalid selection. Try again.\n");
        }
    }

    cleanup();
    return 0;
}
