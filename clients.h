#ifndef CLIENTS_H

#define CLIENTS_H


struct account
{
    char IBAN[40];
    char OWNER[60];
    char CURRENCY[4];
    long long AMOUNT;
    struct account *next;
};

struct client
{
    int length;
    char *name;
    char *surname;
    struct account *head, *prim, *last;
};

void Append(struct client *L, char iban[], char owner[], char currency[], long long money);

void Delete_Account(struct client *L, int position);

void Print_Accounts(struct client L);

void Edit_Account(struct client *L, short account, short choice, long long transaction, int *status_IBAN);

struct account Return_Account(struct client L, int position);

void LogOut_Client(struct client *loggedClient);

void Print_Account(struct account loggedClient);

#endif
