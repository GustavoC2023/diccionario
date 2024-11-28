#include "attribute.h"

void printAttributeyData(FILE *dataDicitonary, long currentHeaderPointer) {
    long headerValue = -1L;
    
    fseek(dataDicitonary, currentHeaderPointer, SEEK_SET);
    fread(&headerValue, sizeof(long), 1, dataDicitonary);

    if(headerValue == -1L) {
        return;
    }
    else {
        Attribute tmp;
        long nextHeaderPointer;

        // Go to the Entity location and read its data.
        fseek(dataDicitonary, headerValue, SEEK_SET);
        // Read the name for the entity at the current position.
        fread(&tmp.name, sizeof(char), 50, dataDicitonary);
        fread(&tmp.Type,sizeof(AttributeType),1,dataDicitonary);
        fread(&tmp.size,sizeof(int),1,dataDicitonary); 

        char type[15];

        switch (tmp.Type)
        {
        case CHAR:
            strcpy(type,"CHAR");
            break;
        case INT:
            strcpy(type,"INT");
            break;
        case VARCHAR:
            strcpy(type,"VARCHAR");
            break;    
        
        default:

            printf("Inavlid option\n");
            break;
        }

        printf("\tAttribute: %s type: %s size: %d\n", tmp.name,type,tmp.size);
        nextHeaderPointer = ftell(dataDicitonary);
        printAttributeyData(dataDicitonary,nextHeaderPointer);
    } 
}

int appendAttribute(FILE *dataDictionary, Attribute *NewAttribute){

    int resultoperation=EXIT_SUCCESS;
    long currentAttribute=0L;

    fseek(dataDictionary,0L,SEEK_END);
    currentAttribute=ftell(dataDictionary);
    NewAttribute->FileDirection=currentAttribute;

    fwrite(&NewAttribute->name,sizeof(char),50,dataDictionary);
    fwrite(&NewAttribute->Type,sizeof(AttributeType),1,dataDictionary);
    fwrite(&NewAttribute->size,sizeof(int),1,dataDictionary);
    fwrite(&NewAttribute->ApAtributo,sizeof(long),1,dataDictionary);

    printf("New attribute %s has been added to the position %li\n",NewAttribute->name,NewAttribute->FileDirection);

    return resultoperation;
}

void reassingAttributePointer(FILE *dataDictionary, const long CurrentHeader, Attribute *NewAttribute){

    long HeaderVal =-1L;

    fseek(dataDictionary,CurrentHeader,SEEK_SET);
    fread(&HeaderVal,sizeof(long),1,dataDictionary);

    if(HeaderVal==-1L){

        fseek(dataDictionary,CurrentHeader,SEEK_SET);
        fwrite(&NewAttribute->FileDirection,sizeof(long),1,dataDictionary);
    }else{

        char CurrentAttributeName[MAX_NAME_SIZE];
        long AprAttribute;

        fseek(dataDictionary,HeaderVal,SEEK_SET);
        fread(&CurrentAttributeName,sizeof(char),MAX_NAME_SIZE, dataDictionary);

        AprAttribute=ftell(dataDictionary)+sizeof(AttributeType)+sizeof(int);

        if(strcmp(CurrentAttributeName,NewAttribute->name)<0){

            reassingAttributePointer(dataDictionary,AprAttribute,NewAttribute);

        }else{

            fseek(dataDictionary,CurrentHeader,SEEK_SET);
            fwrite(&NewAttribute->FileDirection,sizeof(long),1,dataDictionary);
            fseek(dataDictionary,NewAttribute->FileDirection+MAX_NAME_SIZE+sizeof(AttributeType)+sizeof(int),SEEK_SET);
            fwrite(&HeaderVal,sizeof(long),1,dataDictionary);
        }

    }

}

int removeAttribute(FILE *dataDictionary, long currentAttributeHeader, Attribute *AttributeTmp){

    long currentAttributeDirection =-1L;
    fseek(dataDictionary,currentAttributeHeader,SEEK_SET);
    fread(&currentAttributeDirection,sizeof(long),1,dataDictionary);

    if(currentAttributeDirection==-1L){

        fprintf(stderr,"Attribute was not found");
        return EXIT_FAILURE;
    }else{

        char currentAttributeName[MAX_NAME_SIZE];
        long nextAttribute;

        fseek(dataDictionary,currentAttributeDirection,SEEK_SET);

        fread(&currentAttributeName,sizeof(char),MAX_NAME_SIZE,dataDictionary);
        nextAttribute=ftell(dataDictionary)+sizeof(AttributeType)+sizeof(int);

        if(strcmp(currentAttributeName,AttributeTmp->name)==0){

            fread(&AttributeTmp->Type,sizeof(AttributeType),1,dataDictionary);
            fread(&AttributeTmp->size,sizeof(int),1,dataDictionary);
            fread(&AttributeTmp->ApAtributo,sizeof(long),1,dataDictionary);

            fseek(dataDictionary,currentAttributeHeader,SEEK_SET);
            fwrite(&AttributeTmp->ApAtributo,sizeof(long),1,dataDictionary);
            fprintf(stdout,"The attribute was eliminated!\n");
            return EXIT_SUCCESS;
        }else{

            return removeAttribute(dataDictionary,nextAttribute,AttributeTmp);
        }
        
    }

}

