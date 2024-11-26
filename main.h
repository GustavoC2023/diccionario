#ifndef MAIN_H
#define MAIN_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "dictionary.h"
#define MAX_NAME_SIZE 50

void printMainMenu();
void printSubmenu();
int readUserInput();
void clearInputBuffer();
void processUserSelection(DictionaryMenuOption userSelection);
void processUserSelectionSubmenu(DictionaryMenuOption userSelection,char fileName[MAX_NAME_SIZE]);
void readUserString(const char *prompt, char *buffer, size_t size);

#endif