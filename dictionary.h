#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <stdio.h>
#include <stdlib.h>


typedef enum DictionaryMenuOption
{
    PRINTF_DICTIONARY,
    ADD_ENTITY,
    DELETE_ENTITY,
    MODIFI_ENTITY,
    ADD_ATTRIBUTE,
    DELETE_ATTRIBIUTE,
    MODIFY_ATTRIBUTE,
    RETURN
} DictionaryMenuOption;

typedef enum DictionarySubMenu{
    NO_SELECTION,
    NEW_DICTIONARY,
    OPEN_DICTIONARY,
    CLOSE_PROGRAM
}DictionarSubMenu;

void initializeDataDictionary(const char *filename);
int openDataDictionary(const char *filename);
int newDataEntity(const char * filename, const char * entityName);
void printDataDictionary(const char * filename);
int removeDataEntity(const char *filename, long current_posicion, const char *entity_name);
int modifyEntityNameInFile(const char *filename, const char *EntityCurrentName, const char *entity_NewName);
int newDataAttribute(const char *filename, const char *entityName, const char *attributeName,int attributeType);



#endif