
#include "utilities.h"
//#include "clients.h"

long long Convert_To_Long_Long(char number[])
{
    long long num = 0;

    for (int i = 0; i < strlen(number); i++)
        num = num * 10 + (number[i] - '0');

    return num;
}

void Generate_IBAN(char IBAN[])
{
    srand(time(0));

    IBAN[0] = 'R';
    IBAN[1] = 'O',
    IBAN[2] = 'B';
    IBAN[3] = 'C';

    for (int i = 4; i < 39; i++)
    {
        int digit = rand() % 10;
        IBAN[i] = digit + '0';
    }

    IBAN[39] = '\0';

    printf("\nIBAN:%s\n", IBAN);

    if (Verify_IBAN(fAccounts, IBAN) == 0)
        return;
    else
    {

        //printf("NU!");
        Generate_IBAN(IBAN);
    }
}

char *Concatenate_Names(char *fullName, char firstName[], char lastName[])
{
    int i;

    strcpy(fullName, firstName);
    i = strlen(firstName);

    fullName[i] = ' ';
    i++;

    for (int j = 0; j < strlen(lastName); j++)
    {
        fullName[i] = lastName[j];
        i++;
    }

    fullName[i] = '\0';

    return fullName;
}

void Verify_Login(char *userPrompt, struct client *loggedClient)
{
    userPrompt = malloc(100);

    scanf(" %99[^\n]", userPrompt);

    char error = 'y';
    char firstName[100], lastName[100],command[50];
    
    int charF=0,charL=0,charC=0;
    int spaces=0;
    
    
    for (int i=0;i<strlen(userPrompt);i++)
    {
        if(userPrompt[i] == ' ')
            spaces++;
        else
        {
            if (spaces == 0)
            {  
                command[charC]=userPrompt[i];
                charC++;
            }
            if(spaces == 1)
            {
                firstName[charF]=userPrompt[i];
                charF++; 
            }
            if(spaces==2)
            {
                lastName[charL]=userPrompt[i];
                charL++;
            }
        }
    }
    
    command[charC]='\0';
    firstName[charF]='\0';
    lastName[charL]='\0';
    
    if(strcmp(command, "login") != 0)
    {
        printf("Invalid command!\n \tYou have to use command: login\n");
        error = 'x';
    }
    if (strlen(firstName) > 29)
    {
        printf("\tFirst Name's length is bigger than 29!\n");
        error = 'x';
    }

    if(strlen(lastName) > 29)
    {
        printf("\tLast Name's length is bigger than 29!\n");
        error = 'x';
    }

    if(error == 'x')
    {
        printf("Failed to log in!\n");

        Sleep(2000);

        system("cls");
        printf("To login, type login [FirstName] [LastName]\n");

        Verify_Login(userPrompt, loggedClient);
    }
    else 
    {
        loggedClient->surname=malloc(strlen(firstName)+1);
        loggedClient->name=malloc(strlen(lastName)+1);
        
        strcpy(loggedClient->surname,firstName);
        strcpy(loggedClient->name,lastName);
    }

    free(userPrompt);
}

int Verify_Choice(int mini, int maxi)
{
    int input;
    scanf("%d", &input);
    
    while (input < mini || input > maxi)
    {
        printf("The number must be between: [%d,%d] !\n", mini, maxi);
        scanf("%hd", &input);
    }
    
    return input;
}