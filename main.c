#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <time.h>

#include "main.h"


int client_logged = 0;

struct client loggedClient;

enum Menu menuOption;

void commands(int menuOption);


void Menu(int *logged)
{
    
    system("cls");
    printf("\t\t    Bank of Checheci \t\t\n");

    if (*logged == 0)
    {
        *logged = 1;
        commands(1);
    }
    else
    {
    print_commands();
    
    printf("\nYour option:");
    menuOption=Verify_Choice(START_MENU+1,END_MENU);    

    commands(menuOption);
    }
}

void commands(int menuOption)
{
    enum Menu command = menuOption;
    
    switch (command)
    {

        case 1:
            
            Login(&loggedClient);
            Menu(&client_logged);
            
            break;
            
        case 2:
            
            Edit(&loggedClient);
            Menu(&client_logged);
            
            break;

        case 3:
            
            Create(&loggedClient);
            Menu(&client_logged);
            
            break;

        case 4:
            
            Delete(&loggedClient);
            Menu(&client_logged);
            
            break;

        case 5:
            
            View(loggedClient);
            Menu(&client_logged);
            
            break;

        case 6:
            
            Transact(&loggedClient);
            Menu(&client_logged);
            
            break;
            
        case 7:
        
            LogOut_Client(&loggedClient);
            exit(EXIT_SUCCESS);
            
            break;
    
    }

}

int main()
{
    
    Menu(&client_logged);
    LogOut_Client(&loggedClient);
    return 0;
}