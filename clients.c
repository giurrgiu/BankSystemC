#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "clients.h"
#include "files.h"

void LogOut_Client(struct client *loggedClient) {
    
    struct account *current = loggedClient->prim;
    struct account *next;
    
    while (current != NULL) 
    {
        next = current->next;
        free(current);
        current = next;
    }
    
    free(loggedClient->name);
    free(loggedClient->surname);
    
    loggedClient->length = 0;
}


struct account Return_Account(struct client loggedClient, int position)
{
    struct account *aux;
    aux = loggedClient.prim;
    
    int count = 1;
    
    while (aux != NULL)
    {
        if (count == position)
            return *aux;
        
        aux = aux->next;
        count++;
    }
}
void Print_Account(struct account loggedClient){
    printf("Your chosen account:%s %s\n\tFunds:%lld\n", loggedClient.IBAN, loggedClient.CURRENCY, loggedClient.AMOUNT);
}

void Append(struct client *loggedClient, char iban[], char owner[], char currency[], long long money)
{
    struct account *aux=malloc(sizeof(struct account));

    if (loggedClient->head == NULL)
    {

        strcpy(aux->IBAN, iban);
        strcpy(aux->OWNER, owner);
        strcpy(aux->CURRENCY, currency);

        aux->AMOUNT = money;

        aux->next = NULL;
        loggedClient->head = loggedClient->prim = loggedClient->last = aux;
        loggedClient->length = 1;

    }
    else
    {

        strcpy(aux->IBAN, iban);
        strcpy(aux->OWNER, owner);
        strcpy(aux->CURRENCY, currency);

        aux->AMOUNT = money;

        aux->next = NULL;

        loggedClient->length++;

        loggedClient->head->next = aux;
        loggedClient->head = aux;
        loggedClient->last = loggedClient->head;
        
    }
}

void Print_Accounts(struct client loggedClient)
{
    if (loggedClient.length != 0)
    {
        struct account *aux = loggedClient.prim;
        
        while (aux != NULL)
        {
            printf("%s %s %s %lld\n", aux->OWNER, aux->IBAN, aux->CURRENCY, aux->AMOUNT);
            aux = aux->next;
        }
    }
}
void Delete_Account(struct client *loggedClient, int position)
{
    if (loggedClient->length == 1)
    {
        free(loggedClient->prim);
        free(loggedClient->head);
        free(loggedClient->last);
    }

    else if (position == 1)
    {
        struct account *aux;

        aux = loggedClient->prim;
        loggedClient->prim = loggedClient->prim->next;

        aux->next = NULL;
        free(aux);
    }

    else if (position > 1 && position < loggedClient->length)
    {
        short count = 1;
        
        struct account *aux;
        aux = loggedClient->prim;
        
        while (count < position - 1)
        {
            aux = aux->next;
            count++;
        }
        
        struct account *to_delete = aux->next;
        
        aux->next = aux->next->next;
        to_delete->next = NULL;
        
        free(to_delete);
    }
    else if (position == loggedClient->length)
    {
        short count = 1;
        
        struct account *aux;
        aux = loggedClient->prim;
        
        while (count < position - 1)
        {
            aux = aux->next;
            count++;
        }
        struct account *to_delete = aux;
        to_delete = to_delete->next;
        
        aux->next = NULL;
        loggedClient->last = aux;
        
        to_delete->next = NULL;
        free(to_delete);
    }
    loggedClient->length--;
}

void Edit_Account(struct client *loggedClient, short account, short choice, long long transaction, int *status_IBAN)
{
    
    struct account *aux;
    aux = loggedClient->prim;
    
    short count = 1;
    
    while (aux != NULL)
    {
        if (count == account)
        {
            switch (choice)
            {

                case 1:
                {

                    char iban[40];
                    
                    printf("OLD IBAN: %s\n", aux->IBAN);
                    printf("New IBAN: ");
                    
                    scanf("%39s", &iban);

                    *status_IBAN = Verify_IBAN(fAccounts, iban);
                    
                    if (*status_IBAN == 1)
                    {
                        printf("You can't use this IBAN! \n\tIt is already in use");
                        return;
                    }
                    else
                        strcpy(aux->IBAN, iban);
                    
                    break;
                }

                case 2:
                {
                    char currency[4];
                    
                    printf("OLD CURRENCY: %s\n", aux->CURRENCY);
                    printf("New Currency: ");
                    
                    scanf("%4s", &currency);
                    
                    strcpy(aux->CURRENCY, currency);
                    
                    break;
                }

                case 3:
                {
                    long long amount;
                    
                    if (transaction == 0)
                    {
                        printf("OLD FUNDS: %lld\n", aux->AMOUNT);
                        printf("New Funds: ");
                        
                        scanf("%lld", &amount);
                    
                        aux->AMOUNT = amount;
                    }
                    else
                        aux->AMOUNT -= transaction;
                    break;
                }
            }
        }

        count++;
        aux = aux->next;
    }
}
