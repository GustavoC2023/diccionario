#ifndef ATRIBUTO_H
#define ATRIBUTO_H

#include <stdio.h>
#include <string.h>
#include "main.h"


typedef enum AttributeType{
    CHAR,
    INT,
    VARCHAR
}AttributeType;

typedef struct DataAttribute
{
    long FileDirection;
    char name[MAX_NAME_SIZE];
    AttributeType Type;
    int  size;
    long ApAtributo;
    
}Attribute;

int appendAttribute(FILE *dataDictionary, long entityPointer, Attribute *attribute);
void reassignAttributePointers(FILE *dataDictionary, long currentAttributePointer, Attribute newAttribute);
void printEntityData(FILE *dataDicitonary, long currentHeaderPointer);
long search_entity(FILE *dataDictionary, const long Header, const char* EntityName);


#endif