#ifndef FILES_H

#define FILES_H

#define ACCOUNTS_FILE "accounts.txt"
#define CLIENTS_FILE "clients.txt"
#define EDIT_ON 1
#define EDIT_OFF 0

#include "clients.h"
#include "utilities.h"

FILE *fAccounts;
FILE *fClients;

void Write_Client(FILE *clients, struct client *loggedClient);

void Write_Account(FILE *accounts, struct client loggedClient);

void Show_Accounts(FILE *accounts, struct client loggedClient);

void Update_Accounts(FILE *accounts, struct client L, int position, short edit, int accountPosition);

void Update_Funds(FILE *accounts, char sendToIBAN[40], long long newFunds);

int Verify_IBAN(FILE *accounts, char checkIBAN[]);

int Get_Line_Position(FILE *accounts, struct client L, int position);

#endif