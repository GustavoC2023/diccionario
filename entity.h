#ifndef ENTITY_H
#define ENTITY_H
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


#define MAIN_HEADER_POSITION 0L

typedef struct DataEntity {
    long FileDirection;
    char Name[50];
    long ApData;
    long ApAtributo;
    long ApEntidad;
} Entity;

int appendEntity(FILE *dataDicitonary, Entity* dataEntity);
void reassignEntityPointers(FILE *dataDicitonary, long currentHeaderPointer, const char* newEntityName, long newEntityDirection);
long getDataDictionaryHeader(FILE *dataDicitonary);
void printEntityData(FILE *dataDicitonary, long currentHeaderPointer);
int removeEntity(FILE *dataDictionary, long currentEntityPointer, Entity *entityTemp);
int ModifyEntityName(FILE *dataDictionary, long currentEntityPointer, Entity *entityTemp, long *removedApAtributo);
long search_entity(FILE *dataDictionary, const long Header, const char* EntityName);

#endif
