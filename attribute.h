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

int appendAttribute(FILE *dataDictionary, Attribute *NewAttribute);
void reassingAttributePointer(FILE *dataDictionary, const long CurrentHeader, Attribute *NewAttribute);
void printAttributeyData(FILE *dataDicitonary, long currentHeaderPointer);
int removeAttribute(FILE *dataDictionary, long currentAttributeHeader, Attribute *AttributeTmp);



#endif

