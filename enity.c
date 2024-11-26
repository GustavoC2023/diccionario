#include "entity.h"
#include "attribute.h"

int appendEntity(FILE *dataDicitonary, Entity* dataEntity){
    int operationResult = EXIT_SUCCESS;
    long newEntityPosition = 0;
    
    fseek(dataDicitonary, MAIN_HEADER_POSITION, SEEK_END);

    newEntityPosition = ftell(dataDicitonary);
    dataEntity->FileDirection = newEntityPosition;

    // Add the entity name
    fwrite(&dataEntity->Name, sizeof(char), sizeof(dataEntity->Name), dataDicitonary);
    // Data pointer
    fwrite(&dataEntity->ApData, sizeof(long), 1, dataDicitonary);
    // Attributes pointer
    fwrite(&dataEntity->ApAtributo, sizeof(long), 1, dataDicitonary);
    // Next entity pointer
    fwrite(&dataEntity->ApEntidad, sizeof(long), 1, dataDicitonary);

    printf("New entity \"%s\" added at position %ld\n", dataEntity->Name, dataEntity->FileDirection);
    
    return operationResult;
}

void reassignEntityPointers(FILE *dataDicitonary, long currentHeaderPointer, const char* newEntityName, long newEntityDirection) {
    long headerValue = -1;
    
    fseek(dataDicitonary, currentHeaderPointer, SEEK_SET);
    fread(&headerValue, sizeof(headerValue), 1, dataDicitonary);

    if(headerValue == -1L) {
        // No more entities to iterate. Set the current pointer to the new entity direction.
        fseek(dataDicitonary, currentHeaderPointer, SEEK_SET);
        fwrite(&newEntityDirection, sizeof(long), 1, dataDicitonary);

        printf("La ultima entidad apunta a %li\n",newEntityDirection);

    }
    else {
        char currentEntityName[50];
        long nextHeaderPointer;

        // Go to the Entity location and read its data.
        fseek(dataDicitonary, headerValue, SEEK_SET);
        // Read the name for the entity at the current position.
        fread(&currentEntityName, sizeof(char), 50, dataDicitonary); 
        nextHeaderPointer = ftell(dataDicitonary) + (sizeof(long) * 2);
        // Compare the Entity names to determine whether the current entity should be before the new one or not.
        if(strcmp(currentEntityName, newEntityName) < 0) {
            // Current entity is before the new one.
            reassignEntityPointers(dataDicitonary, nextHeaderPointer, newEntityName, newEntityDirection);
        }
        else {
            // Reassign first pointer.
            fseek(dataDicitonary, currentHeaderPointer, SEEK_SET);
            fwrite(&newEntityDirection, sizeof(long), 1, dataDicitonary);
            // Reassign new entity pointer.
            fseek(dataDicitonary, newEntityDirection + 50 + (sizeof(long) * 2), SEEK_SET);
            fwrite(&headerValue, sizeof(long), 1, dataDicitonary);

            printf("La entidad %s apunta a %li\n",currentEntityName,newEntityDirection);
            printf("La nueva entidad %s apunta a %li\n",newEntityName,headerValue);
        }
    } 
}

long getDataDictionaryHeader(FILE *dataDicitonary) {
    long header;

    fseek(dataDicitonary, MAIN_HEADER_POSITION, SEEK_SET);
    fread(&header, sizeof(header), 1, dataDicitonary);

    return header;
}

void printEntityData(FILE *dataDicitonary, long currentHeaderPointer) {
    long headerValue = -1;
    
    fseek(dataDicitonary, currentHeaderPointer, SEEK_SET);
    fread(&headerValue, sizeof(headerValue), 1, dataDicitonary);

    if(headerValue == -1L) {
        return;
    }
    else {
        char currentEntityName[50];
        long nextHeaderPointer;

        // Go to the Entity location and read its data.
        fseek(dataDicitonary, headerValue, SEEK_SET);
        // Read the name for the entity at the current position.
        fread(&currentEntityName, sizeof(char), 50, dataDicitonary); 

        printf("Entity: %s\n", currentEntityName);
        nextHeaderPointer = ftell(dataDicitonary) + (sizeof(long)*2);
        printEntityData(dataDicitonary, nextHeaderPointer);
    } 
}
int removeEntity(FILE *dataDictionary, long currentEntityPointer, Entity *entityTemp)
{
    long currentEntityDirection = -1;
    fseek(dataDictionary, currentEntityPointer, SEEK_SET);
    fread(&currentEntityDirection, sizeof(long), 1, dataDictionary);

    if (currentEntityDirection == -1L)
    {
        fprintf(stderr, "Error de eliminaciÃ³n, entidad no encontrada\n");
        return EXIT_FAILURE;
    }
    else
    {
        char currentEntityNamel[50];
        long NextEntity;

        fseek(dataDictionary, currentEntityDirection, SEEK_SET);

        fread(&currentEntityNamel, sizeof(char), 50, dataDictionary);
        NextEntity = ftell(dataDictionary) + (sizeof(long) * 2);

        if (strcmp(currentEntityNamel, entityTemp->Name) == 0)
        {

            fread(&entityTemp->ApData,sizeof(long),1,dataDictionary);
            fread(&entityTemp->ApAtributo, sizeof(long), 1, dataDictionary);
            fread(&entityTemp->ApEntidad, sizeof(long), 1, dataDictionary);


            fseek(dataDictionary, currentEntityPointer, SEEK_SET);
            fwrite(&entityTemp->ApEntidad, sizeof(long), 1, dataDictionary);
            fprintf(stdout, "Eliminacion exitosa, entidad eliminada\n");
            return EXIT_SUCCESS;
        }
        else
        {
            return removeEntity(dataDictionary, NextEntity, entityTemp);
        }
    }
}

int ModifyEntityName(FILE *dataDictionary, long currentEntityPointer, Entity *entityTemp, long *removedApAtributo)
{
    long currentEntityDirection = -1;
    fseek(dataDictionary, currentEntityPointer, SEEK_SET);
    fread(&currentEntityDirection, sizeof(long), 1, dataDictionary);

    if (currentEntityDirection == -1L)
    {
        fprintf(stderr, "Entity was not found\n");
        return EXIT_FAILURE;
    }
    else
    {
        char currentEntityNamel[50];
        long NextEntity;

        fseek(dataDictionary, currentEntityDirection, SEEK_SET);
        fread(&currentEntityNamel, sizeof(char), 50, dataDictionary);
        NextEntity = ftell(dataDictionary) + (sizeof(long) * 2);

        if (strcmp(currentEntityNamel, entityTemp->Name) == 0)
        {
            fread(&entityTemp->ApData, sizeof(long), 1, dataDictionary);
            fread(&entityTemp->ApAtributo, sizeof(long), 1, dataDictionary);
            fread(&entityTemp->ApEntidad, sizeof(long), 1, dataDictionary);

            // Guardar el valor de ApAtributo de la entidad eliminada
            *removedApAtributo = entityTemp->ApAtributo;

            fseek(dataDictionary, currentEntityPointer, SEEK_SET);
            fwrite(&entityTemp->ApEntidad, sizeof(long), 1, dataDictionary);
            fprintf(stdout, "The entity was eliminated\n");
            return EXIT_SUCCESS;
        }
        else
        {
            return ModifyEntityName(dataDictionary, NextEntity, entityTemp, removedApAtributo);
        }
    }
}



/*long search_entity(FILE *dataDictionary, const long Header, const char* EntityName){

    long CurrentHeader;

    fseek(dataDictionary,Header,SEEK_SET);
    fread(&CurrentHeader,sizeof(long),1,dataDictionary);

    if(CurrentHeader==-1L){

        return -1L;
    }

    char entityName[50];

    fseek(dataDictionary,CurrentHeader,SEEK_SET);
    fread(&entityName,sizeof(char),50,dataDictionary);

    if(strcmp(entityName,EntityName)==0){

        fseek(dataDictionary,CurrentHeader,SEEK_SET);
        return CurrentHeader;
    }

    long next_entity=ftell(dataDictionary)+(sizeof(long)*2);
    return search_entity(dataDictionary,next_entity,entityName);
}

*/