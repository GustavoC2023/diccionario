#include "dictionary.h"
#include "entity.h"
#include "attribute.h"

void initializeDataDictionary(const char *filename)
{
    long header = -1L;
    FILE *file = fopen(filename, "wb");

    if (file == NULL)
    {
        fprintf(stderr, "Failed to create the data dictionary.\n");
    }

    if (fwrite(&header, sizeof(header), 1, file) != 1)
    {
        fprintf(stderr, "Failed to initialize the data dicitonary.\n");
    }
    else
    {

        fprintf(stderr, "Dictionary %s created!.\n", filename);
    }

    fclose(file);
}

int openDataDictionary(const char *filename)
{
    int opeationResult = EXIT_SUCCESS;
    long header;
    FILE *file = fopen(filename, "rb");

    if (file)
    {
        if (fread(&header, sizeof(header), 1, file) != 1)
        {
            fprintf(stderr, "Failed to read data.\n");
            opeationResult = EXIT_FAILURE;
        }
        else
        {
            printf("The header value is: %ld\n", header);
        }
        fclose(file);
    }
    else
    {
        fprintf(stderr, "Failed to open the data dictionary.\n");
        opeationResult = EXIT_FAILURE;
    }

    return opeationResult;
}

int newDataEntity(const char *filename, const char *entityName)
{
    int operationResult = EXIT_SUCCESS;
    FILE *file = fopen(filename, "r+b");

    if (file)
    {
        Entity dataEntity;

        dataEntity.ApData = -1L;
        dataEntity.ApAtributo = -1L;
        dataEntity.ApEntidad = -1L;

        snprintf(dataEntity.Name, sizeof(dataEntity.Name), "%s", entityName);
        if (appendEntity(file, &dataEntity) == EXIT_SUCCESS)
        {
            long dataDictionaryHeader = getDataDictionaryHeader(file);
            reassignEntityPointers(file, MAIN_HEADER_POSITION, dataEntity.Name, dataEntity.FileDirection);
        }
        else
        {
            fprintf(stderr, "Failed to create the \"%s\" entity.\n", entityName);
            operationResult = EXIT_FAILURE;
        }
    }
    else
    {
        fprintf(stderr, "Failed to open the data dictionary.\n");
        operationResult = EXIT_FAILURE;
    }

    fclose(file);

    return operationResult;
}

int removeDataEntity(const char *filename, long current_posicion, const char *entity_name)
{
    int operationResult = EXIT_SUCCESS;

    Entity tmp;

    strcpy(tmp.Name, entity_name);

    FILE *file = fopen(filename, "r+b");
    if (file)
    {
        operationResult = removeEntity(file, MAIN_HEADER_POSITION, &tmp);
        fclose(file);
    }
    else
    {
        fprintf(stderr, "Failed to open the data dictionary\n");
        operationResult = EXIT_FAILURE;
    }

    return operationResult;
}

int modifyEntityNameInFile(const char *filename, const char *currentEntityName, const char *newEntityName)
{
    int operationResult = EXIT_SUCCESS;
    long removedApAtributo = -1L;

    FILE *file = fopen(filename, "r+b");
    if (file)
    {
        Entity tmp;
        tmp.ApAtributo=-1L;
        tmp.ApData=-1L;
        tmp.ApEntidad=-1L;
        strcpy(tmp.Name, currentEntityName);
        ModifyEntityName(file, MAIN_HEADER_POSITION, &tmp, &removedApAtributo);
        strcpy(tmp.Name,newEntityName);
        appendEntity(file, &tmp);
        reassignEntityPointers(file, MAIN_HEADER_POSITION, tmp.Name, tmp.FileDirection);
        fclose(file);
        operationResult = EXIT_SUCCESS;
    }
    else
    {
        fprintf(stderr, "Failed to open the data dictionary\n");
        operationResult = EXIT_FAILURE;
    }

    return operationResult;
}

void printDataDictionary(const char *filename)
{
    FILE *file = fopen(filename, "rb");

    if (file)
    {
        Entity dataEntity;

        printf("Dictionary name: %s\n", filename);
        printEntityData(file, MAIN_HEADER_POSITION);
    }
    else
    {
        fprintf(stderr, "Failed to open the data dictionary.\n");
    }

    fclose(file);
}

int newDataAttribute(const char *filename, const char *entityName, const char *attributeName, int attributeType)
{

    int operationResult = EXIT_SUCCESS;
    int size;

    FILE *file = fopen(filename, "r+b");
    if (file)
    {
        Entity tmp;
        tmp.FileDirection = search_entity(file, 0L, entityName);

        if (tmp.FileDirection != -1L)
        {

            Attribute atribute;
            atribute.ApAtributo=-1L;

            switch (attributeType)
            {
            case CHAR:
                atribute.size = 1;
                atribute.Type = CHAR;
                break;

            case INT:
                atribute.size = 4;
                atribute.Type = INT;
                break;

            case VARCHAR:
                printf("Enter the VARCHAR size: ");
                scanf("%d", &atribute.size);
                atribute.Type = VARCHAR;
                break;
            default:

                printf("Error. Invalid Type");
                break;
            }

            strcpy(atribute.name, attributeName);
            if (appendAttribute(file, &atribute) == EXIT_SUCCESS)
            {

                long AprAttribute = tmp.FileDirection + (sizeof(char) * 50) + sizeof(long);
                reassingAttributePointer(file, AprAttribute, &atribute);
            }
            else
            {

                printf("Error in add attribute");
            }

            fclose(file);
        }
        else
        {

            printf("Entidad was not found");
            operationResult = EXIT_FAILURE;
        }
    }
    else
    {
        fprintf(stderr, "Failed to open the data dictionary\n");
        operationResult = EXIT_FAILURE;
    }

    return operationResult;
}

int removeDataAttribute(const char *filename, long current_position, const char *entityName, const char *attributeName)
{

    int operationResult = EXIT_SUCCESS;

    FILE *file = fopen(filename, "r+b");

    if (file)
    {
        Entity tmp;
        tmp.FileDirection = search_entity(file, 0L, entityName);

        if (tmp.FileDirection != -1L)
        {
            Attribute Attributetmp;
            strcpy(Attributetmp.name, attributeName);
            long AprAttribute = tmp.FileDirection + (sizeof(char) * 50) + sizeof(long);
            operationResult = removeAttribute(file, AprAttribute, &Attributetmp);

            fclose(file);
        }
        else
        {

            fprintf(stderr, "Entity was not found\n");
            operationResult = EXIT_FAILURE;
        }
    }
    else
    {

        fprintf(stderr, "Failed to open the data dictionary\n");
        operationResult = EXIT_FAILURE;
    }
}

int modifyAttribute(const char*filename, const char* EntityName,const char*AttribueCurrentName, const char* AttributeNewName, int AttributeNewType)
{

    int operationResult = EXIT_SUCCESS;

    FILE *file = fopen(filename, "r+b");

    if (file)
    {

        Entity *EntityTmp;
        EntityTmp->FileDirection = search_entity(file, 0L, EntityName);

        if (EntityTmp->FileDirection != -1L)
        {

            Attribute Attributetmp;
            Attribute NewAttribute;
            NewAttribute.ApAtributo=-1L;
            strcpy(Attributetmp.name, AttribueCurrentName);
            long AprAttribute = EntityTmp->FileDirection + (sizeof(char) * 50) + sizeof(long);
            operationResult = removeAttribute(file, AprAttribute, &Attributetmp);

            strcpy(NewAttribute.name,AttributeNewName);
            
            switch (AttributeNewType)
            {
            case INT:
                NewAttribute.Type=INT;
                NewAttribute.size=4;
                break;
            case CHAR:
                NewAttribute.Type=CHAR;
                NewAttribute.size=1;
                break;
            case VARCHAR:
                NewAttribute.Type=VARCHAR;
                printf("Enter the size of VARCHAR: ");
                scanf("%d",&NewAttribute.size);
                break;
            
            default:

                printf("Invalid Option!");
                break;
            }

            if (appendAttribute(file, &NewAttribute) == EXIT_SUCCESS)
            {
                long AprAttribute = EntityTmp->FileDirection + (sizeof(char) * 50) + sizeof(long);
                reassingAttributePointer(file, AprAttribute, &NewAttribute);
                fprintf(stderr, "Attribute modify\n");

            }
            else
            {

                printf("Error in add attribute");
            }

            fclose(file);


        }
        else
        {

            fprintf(stderr, "Entity was not found\n");
            operationResult = EXIT_FAILURE;
        }
    }
    else
    {

        fprintf(stderr, "Failed to open the data dictionary\n");
        operationResult = EXIT_FAILURE;
    }
}

