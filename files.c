#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "files.h"

void Read_Accounts(FILE *accounts, struct client *loggedClient);

int File_Exists(FILE *accounts)
{
    
    int stateFile;

    accounts=fopen(ACCOUNTS_FILE, "r");

    if ( accounts != NULL)
        stateFile=1;
    else
        stateFile=0;

    fclose(accounts);
    
    return stateFile;

}

void Create_File(FILE *accounts)
{

    int stateFile=File_Exists(accounts);

    if (stateFile == 0)
    {
        accounts=fopen(ACCOUNTS_FILE,"w");
        
        if(accounts == NULL )
        {
            printf("Failed to create accounts file!");
            exit(EXIT_FAILURE);
        }
    }

    fclose(accounts);

}

int Verify_IBAN(FILE *accounts, char checkIBAN[])
{

    int stateFile = File_Exists(fAccounts);

    accounts = fopen(ACCOUNTS_FILE, "r");
    
    if (accounts == NULL)
    {
        printf("Failed to open the file!");
        exit(EXIT_FAILURE);
    }
    else
    {
        char searchSurname[50];
        char searchName[50];
        char iban[40], currency[4];
        char funds[50];

        while (fscanf(accounts, "%s %s %s %s %s", searchSurname, searchName, iban, currency, funds) > 0)
        {
            if (strcmp(checkIBAN, iban) == 0)
            {
                fclose(accounts);
                return 1;
            }
        }
    }
    fclose(accounts);
    return 0;
}
void Update_Accounts(FILE *accounts, struct client L, int position, short edit, int accountPosition)
{
    accounts = fopen(ACCOUNTS_FILE, "r");
    
    FILE *rewrite = fopen("aux.txt", "w");
    
    short editDone = 0;
    
    if (accounts == NULL)
    {
        printf("Failed to open the file!\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        if (rewrite == NULL)
        {
            printf("Failed to open the file!\n");
            exit(EXIT_FAILURE);
        }
        else
        {
            int c = fgetc(accounts);
            int lines = 1;
            
            while (c != EOF)
            {

                if (c == '\n')
                    lines++;
                
                if (lines != position)
                    fputc(c, rewrite);
                
                if (lines == position && edit == EDIT_ON && editDone == 0)
                {
                    struct account to_update = Return_Account(L, accountPosition);
                    
                    fprintf(rewrite, "\n%s %s %s %lld", to_update.OWNER, to_update.IBAN, to_update.CURRENCY, to_update.AMOUNT);
                    
                    editDone = 1;
                }
                
                c = fgetc(accounts);
            }
        }
    }

    fclose(accounts);
    fclose(rewrite);
    
    if (remove("accounts.txt") != 0)
    {
        printf("Failed to delete the original file");
        return;
    }

    if (rename("aux.txt", "accounts.txt") != 0)
    {
        printf("Failed to rename!");
        return;
    }

}

void Show_Accounts(FILE *accounts, struct client loggedClient)
{
    int count = 1;
    
    accounts = fopen(ACCOUNTS_FILE, "r");
    
    if (accounts == NULL)
    {
        printf("Failed to open the file!\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        char searchName[strlen(loggedClient.name)];
        char searchSurname[strlen(loggedClient.surname)];
        char iban[40], currency[4];
        char amount[50];
        
        while (fscanf(accounts, "%s %s %s %s %s", searchSurname, searchName, iban, currency, amount) > 0)
        {
            if (strcmp(searchSurname, loggedClient.surname) == 0 && strcmp(searchName, loggedClient.name) == 0)
            {
                printf("\t%d. %s %s %s %s %s\n", count, searchSurname, searchName, iban, currency, amount);
                count++;
            }
        }
    }
    
    fclose(accounts);
}
void Write_Client(FILE *clients, struct client *loggedClient)
{

    Create_File(fAccounts);

    clients = fopen(CLIENTS_FILE, "a+");
    
    if (clients == NULL)
    {
        printf("Failed to open the file clients!\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        char searchName[strlen(loggedClient->name)];
        char searchSurname[strlen(loggedClient->surname)];
        char found = 'x';
        char currentClient = 'x';
        
        int accountsRead=0;

        while (fscanf(clients, "%s %s", searchSurname, searchName) > 0)
        {
            //^ Check if searchName and searchName matches to the Client's names
            if (strcmp(searchSurname, loggedClient->surname) == 0 && strcmp(searchName, loggedClient->name) == 0)
            {
                found = 'y';
                currentClient = 'y';
            }
        }

        if (found == 'y')
            Read_Accounts(fAccounts, loggedClient);
        
        if (found == 'x')
            fprintf(clients, "%s %s\n", loggedClient->surname, loggedClient->name);
    }

    fclose(clients);
}

void Write_Account(FILE *accounts, struct client loggedClient)
{
    accounts = fopen(ACCOUNTS_FILE, "a");
    
    if (accounts == NULL)
    {
        printf("Failed to open the file!\n");
        exit(EXIT_FAILURE);
    }
    else
        fprintf(accounts, "%s %s %s %lld\n", loggedClient.last->OWNER, loggedClient.last->IBAN, loggedClient.last->CURRENCY, loggedClient.last->AMOUNT);
    
    fclose(accounts);
}

void Update_Funds(FILE *accounts, char sendToIBAN[40], long long newFunds)
{
    accounts = fopen(ACCOUNTS_FILE, "r");
    
    FILE *rewrite = fopen("aux.txt", "w");
    
    if (accounts == NULL)
    {
        printf("Failed to open the file!\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        if (rewrite == NULL)
        {
            printf("Failed to open the file!");
            exit(EXIT_FAILURE);
        }
        else
        {
            char surname[50];
            char name[50];
            char iban[40], currency[4];
            char amount[50];

            long long convertedAmount;
            int count = 1;

            while (fscanf(accounts, "%s %s %s %s %s", surname, name, iban, currency, amount) > 0)
            {
                if (strcmp(sendToIBAN, iban) == 0)
                {
                    convertedAmount = Convert_To_Long_Long(amount);
                    convertedAmount += newFunds;
                    
                    fprintf(rewrite, "%s %s %s %s %lld\n", surname, name, iban, currency, convertedAmount);
                }
                else
                    fprintf(rewrite, "%s %s %s %s %s\n", surname, name, iban, currency, amount);

                count++;
            }
        }
    }
    
    fclose(accounts);
    fclose(rewrite);
    
    if (remove(ACCOUNTS_FILE) != 0)
    {
        printf("Failed to delete the file!\n");
        return;
    }

    if (rename("aux.txt", ACCOUNTS_FILE) != 0)
    {
        printf("Failed to rename!");
        return;
    }

}

int Get_Line_Position(FILE *accounts, struct client L, int position)
{
    accounts = fopen(ACCOUNTS_FILE, "r");
    if (accounts == NULL)
    {
        printf("Failed to open the file!\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        char searchName[strlen(L.name)];
        char searchSurname[strlen(L.surname)];
        
        char iban[40], currency[4];
        char amount[50];
        
        int fileLines = 0;
        int clientLines = 0;
        
        while (fscanf(accounts, "%s %s %s %s %s", searchSurname, searchName, iban, currency, amount) > 0)
        {
            fileLines++;
            if (strcmp(searchSurname, L.surname) == 0 && strcmp(searchName, L.name) == 0)
            {
                clientLines++;
                if (clientLines == position)
                {
                    fclose(accounts);
                    return fileLines;
                }
            }
        }
    }
    fclose(accounts);
}

void Read_Accounts(FILE *accounts, struct client *loggedClient)
{

    accounts = fopen(ACCOUNTS_FILE, "r");

    if (accounts == NULL)
    {
        printf("Failed to open the file!\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        char searchName[strlen(loggedClient->name) + 1];
        char searchSurname[strlen(loggedClient->surname) + 1];
        
        char iban[40], currency[4];
        char amount[50];
        char *owner;
        long long amount_lld;
        int found=0;

        while (fscanf(accounts, "%s %s %s %s %s", searchSurname, searchName, iban, currency, amount) > 0)
        {
            if (strcmp(searchSurname, loggedClient->surname) == 0 && strcmp(searchName, loggedClient->name) == 0)
            {

                if (found==0)
                {
                    owner = malloc(strlen(searchSurname) + strlen(searchName) + 3);
                    owner = Concatenate_Names(owner, searchSurname, searchName);
                    found=1;
                }

                amount_lld = Convert_To_Long_Long(amount);

                Append(loggedClient, iban, owner, currency, amount_lld);
            }
        }
        free(owner);
        fclose(accounts);
    }
    fclose(accounts);
}