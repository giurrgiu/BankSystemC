#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <time.h>

#include "commands.h"

void print_commands()
{
    printf("\t\t   2.EDIT ACCOUNT \n");
    printf("\t\t   3.CREATE ACCOUNT\n");
    printf("\t\t   4.DELETE ACCOUNT\n");
    printf("\t\t   5.VIEW ACCOUNT\n");
    printf("\t\t   6.MAKE A TRANSACTION\n");
    printf("\t\t   7.EXIT\n");
}

void Login(struct client *loggedClient)
{
    char *userPrompt;

    system("cls");
    printf("To login, type login [FirstName] [LastName]\n");

    Verify_Login(userPrompt, loggedClient);
    
    Write_Client(fClients, loggedClient);
    
    free(userPrompt);
    
    printf("Logged in succesfully!\n");
    

    Sleep(1000);
}

void Edit(struct client *loggedClient)
{
    struct account chosenAccount;
    int editAccount, editChoice;
    int fileLinePosition;

    system("cls");
    printf("Edit Account\n");
    printf("Which account do you want to edit?\n");
    
    Show_Accounts(fAccounts, *loggedClient);
    
    printf("Select an account:");
    editAccount = Verify_Choice(1, loggedClient->length);

    printf("\n");

    chosenAccount = Return_Account(*loggedClient, editAccount);

    printf("Edit:\n1.IBAN: %s\n2.CURRENCY: %s\n3.FUNDS: %lld\n", chosenAccount.IBAN, chosenAccount.CURRENCY, chosenAccount.AMOUNT);
    printf("Select an option:");

    editChoice = Verify_Choice(1, 3);

    printf("\n");
    
    int *status_IBAN = malloc(sizeof(int));
    
    Edit_Account(loggedClient, editAccount, editChoice, 0, status_IBAN);
    
    if (*status_IBAN == 0 || editChoice>1)
    {
        chosenAccount = Return_Account(*loggedClient, editAccount);

        fileLinePosition = Get_Line_Position(fAccounts, *loggedClient, editAccount);
        
        Update_Accounts(fAccounts, *loggedClient, fileLinePosition, EDIT_ON, editAccount);
        printf("Your account was succesfully edited!");
    }
    
    free(status_IBAN);
    Sleep(2000);
}

void Create(struct client *loggedClient)
{
    char IBAN[40];
    char *fullName;
    char currency[4];
    
    long long deposit;
    
    system("cls");
    printf("Create Account\n");
    
    fullName = malloc(strlen(loggedClient->surname) + strlen(loggedClient->name) + 3);
    fullName = Concatenate_Names(fullName, loggedClient->surname, loggedClient->name);

    printf("For an account to be created, an IBAN will be created.\n");
    Generate_IBAN(IBAN);

    printf("For an account to be created, you will have to choose a form of currency:\n");
    printf("\t1.RON\n");
    printf("\t2.EUR\n");
    printf("\t3.USD\n");
    
    enum Currency clientCurrency;
    
    int client_choice;
    clientCurrency = Verify_Choice(START_CURRENCY, END_CURRENCY);
    
    switch (clientCurrency)
    {
        case 1:
            strcpy(currency, "RON");
            break;
        case 2:
            strcpy(currency, "EUR");
            break;
        case 3:
            strcpy(currency, "USD");
            break;
    }

    printf("Chosen currency: %s\n", currency);
    printf("For an account to be created, you will have to deposit some funds:");
    scanf("%lld", &deposit);

    Append(loggedClient, IBAN, fullName, currency, deposit);

    Write_Account(fAccounts, *loggedClient);

    free(fullName);
    printf("Your account was succesfully created!");
    Sleep(2000);
}

void Delete(struct client *loggedClient)
{
    int userChoice, fileLine;
    
    system("cls");
    printf("Delete Account \n");

    if(loggedClient->length==0)
        printf("You don't have an account to delete!");
    else 
    {
        printf("Accounts owned: %d\n", loggedClient->length);
        printf("Which account do you want to delete?\n");
        
        Show_Accounts(fAccounts, *loggedClient);
        
        printf("Choice:");
        userChoice = Verify_Choice(1, loggedClient->length);
        
        Delete_Account(loggedClient, userChoice);
        
        fileLine = Get_Line_Position(fAccounts, *loggedClient, userChoice);
        
        Update_Accounts(fAccounts, *loggedClient, fileLine, EDIT_OFF, -1);
        printf("Your account was succesfully deleted!");
    }
    Sleep(2000);
}

void View(struct client loggedClient)
{
    system("cls");
    printf("Accounts owned: %d\n", loggedClient.length);
    
    Show_Accounts(fAccounts, loggedClient);
    
    char wait[2];
    printf("Press any key to continue:");
    scanf("%1s", wait);
}

void Transact(struct client *loggedClient)
{
    int pickAccount;
    int fileLine;
    
    struct account chosenAccount;
    
    long long transferFunds;

    system("cls");
    printf("Perform a Transaction\n");
    printf("From which account do you want to transfer funds?\n");

    Show_Accounts(fAccounts, *loggedClient);

    printf("Choose an account:");

    pickAccount = Verify_Choice(1, loggedClient->length);
    chosenAccount = Return_Account(*loggedClient, pickAccount);

    Print_Account(chosenAccount);
    
    printf("\nEnter the amount of funds you want to transfer:");
    
    scanf("%lld", &transferFunds);

    int *status_IBAN = malloc(sizeof(int));
    
    Edit_Account(loggedClient, pickAccount, 3, transferFunds, status_IBAN);
    
    fileLine = Get_Line_Position(fAccounts, *loggedClient, pickAccount);
    
    char sendToIBAN[40];
    
    printf("\nWrite the IBAN of the receiver:");
    scanf("%39s", &sendToIBAN);
    
    int existIBAN=Verify_IBAN(fAccounts,sendToIBAN);

    if(existIBAN==0)
        printf("The IBAN you provided is not in use by any of our clients!");
    else 
    {
        Update_Accounts(fAccounts, *loggedClient, fileLine, EDIT_ON, pickAccount);
        Update_Funds(fAccounts, sendToIBAN, transferFunds);

        printf("You have sent the amount of %lld to %s\n", transferFunds, sendToIBAN);

        printf("The transaction has worked!");
        free(status_IBAN);
    }
    Sleep(2000);
}
