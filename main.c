#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

struct Account {
    int accountNumber;
    char name[50];
    double balance;
    struct Account* next;
};

struct Account* head = NULL;

int readInt(const char* prompt) {
    char input[100];
    char* end;
    long value;

    while (1) {
        printf("%s", prompt);

        if (fgets(input, sizeof(input), stdin) == NULL)
            exit(0);

        errno = 0;
        value = strtol(input, &end, 10);

        if (end != input && errno == 0 &&
            value >= 1 && value <= 2147483647) {
            return (int)value;
        }

        printf("Invalid input. Please enter a valid positive integer.\n");
    }
}

double readAmount(const char* prompt) {
    char input[100];
    char* end;
    double value;

    while (1) {
        printf("%s", prompt);

        if (fgets(input, sizeof(input), stdin) == NULL)
            exit(0);

        errno = 0;
        value = strtod(input, &end);

        if (end != input && errno == 0 &&
            value >= 0 && value < 1e15) {
            return value;
        }

        printf("Invalid amount. Please enter a valid amount.\n");
    }
}

void readName(char* name, size_t size) {
    printf("Enter Name: ");

    if (fgets(name, size, stdin) == NULL)
        exit(0);

    name[strcspn(name, "\n")] = '\0';

    if (strlen(name) == 0) {
        strcpy(name, "Unknown");
    }
}

struct Account* findAccount(int accNo) {
    struct Account* current = head;

    while (current != NULL) {
        if (current->accountNumber == accNo)
            return current;

        current = current->next;
    }

    return NULL;
}

void createAccount() {
    int accNo = readInt("\nEnter Account Number: ");

    if (findAccount(accNo) != NULL) {
        printf("Error: Account number already exists.\n");
        return;
    }

    struct Account* newAccount =
        (struct Account*)malloc(sizeof(struct Account));

    if (newAccount == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }

    newAccount->accountNumber = accNo;
    readName(newAccount->name, sizeof(newAccount->name));

    newAccount->balance = readAmount("Enter Initial Deposit: $");

    newAccount->next = head;
    head = newAccount;

    printf("Account created successfully!\n");
}

void deposit() {
    int accNo = readInt("\nEnter Account Number: ");
    struct Account* acc = findAccount(accNo);

    if (acc == NULL) {
        printf("Account not found.\n");
        return;
    }

    double amount = readAmount("Enter Deposit Amount: $");

    if (amount <= 0) {
        printf("Amount must be greater than zero.\n");
        return;
    }

    acc->balance += amount;

    printf("Deposited $%.2f. New Balance: $%.2f\n",
           amount, acc->balance);
}

void withdraw() {
    int accNo = readInt("\nEnter Account Number: ");
    struct Account* acc = findAccount(accNo);

    if (acc == NULL) {
        printf("Account not found.\n");
        return;
    }

    double amount = readAmount("Enter Withdrawal Amount: $");

    if (amount <= 0) {
        printf("Amount must be greater than zero.\n");
        return;
    }

    if (amount > acc->balance) {
        printf("Insufficient balance! Current Balance: $%.2f\n",
               acc->balance);
        return;
    }

    acc->balance -= amount;

    printf("Withdrew $%.2f. New Balance: $%.2f\n",
           amount, acc->balance);
}

void checkBalance() {
    int accNo = readInt("\nEnter Account Number: ");
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

    printf("\n%-12s %-20s %-10s\n",
           "Account No", "Name", "Balance");
    printf("--------------------------------------------\n");

    while (current != NULL) {
        printf("%-12d %-20s $%-10.2f\n",
               current->accountNumber,
               current->name,
               current->balance);

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

    head = NULL;
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

        choice = readInt("Enter your choice (1-6): ");

        switch (choice) {
            case 1:
                createAccount();
                break;
            case 2:
                deposit();
                break;
            case 3:
                withdraw();
                break;
            case 4:
                checkBalance();
                break;
            case 5:
                displayAll();
                break;
            case 6:
                cleanup();
                printf("Exiting system. Goodbye!\n");
                return 0;
            default:
                printf("Invalid selection. Try again.\n");
        }
    }
}
