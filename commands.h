#ifndef COMMANDS_H

#define COMMANDS_H

#include "main.h"

void print_commands();

void Login(struct client *loggedClient);

void Verify_Login(char *userPrompt, struct client *loggedClient);

void Edit(struct client *loggedClient);

void Create(struct client *loggedClient);

void Delete(struct client *loggedClient);

void View(struct client loggedClient);

void Transact(struct client *loggedClient);

#endif