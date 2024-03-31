#ifndef MAIN_H

#define MAIN_H

#define START_CURRENCY 1
#define END_CURRENCY 3
#define START_MENU 1
#define END_MENU 7

#include "clients.h"
#include "commands.h"
#include "files.h"
#include "utilities.h"

enum Currency
{
    RON = 1,
    EUR,
    USD
};

enum Menu
{
    LOGIN = 1,
    EDIT,
    CREATE,
    DELETE_,
    VIEW,
    TRANSACT,
    EXIT
};

#endif