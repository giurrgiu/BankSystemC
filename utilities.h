#ifndef UTILITIES_H

#define UTILITIES_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <windows.h>

#include "clients.h"
#include "files.h"

#define TOKEN " "

long long Convert_To_Long_Long(char number[]);

void Generate_IBAN(char IBAN[]);

char *Concatenate_Names(char *fullName, char firstName[], char lastName[]);

int Verify_Choice(int mini, int maxi);

void Verify_Login(char *userPrompt, struct client *loggedClient);

#endif