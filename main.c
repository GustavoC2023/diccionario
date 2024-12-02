
#include "entity.c"
#include "dictionary.c"
#include "attribute.c"
int main()
{
    int currentUserSelection = NO_SELECTION;

    while (currentUserSelection != CLOSE_PROGRAM)
    {
        printMainMenu();
        currentUserSelection = readUserInput();
        processUserSelection(currentUserSelection);
    }

    return EXIT_SUCCESS;
}

void printMainMenu()
{
    printf("\n\t----PRIMER MENU----\n");
    printf("%d) CREAR DICCIONARIO\n", NEW_DICTIONARY);
    printf("%d) ABRIR DICCIONARIO\n", OPEN_DICTIONARY);
    printf("%d) SALIR\n", CLOSE_PROGRAM);
}

void printSubmenu()
{

    printf("\n\t----SEGUNDO MENU----\n");

    printf("%d) IMPRIMIR DICCIONARIO\n", PRINTF_DICTIONARY);
    printf("%d) NUEVA ENTIDAD\n", ADD_ENTITY);
    printf("%d) ELIMINAR ENTIDAD\n", DELETE_ENTITY);
    printf("%d) MODIFICAR ENTIDAD\n", MODIFI_ENTITY);
    printf("%d) NUEVO ATRIBUTO\n", ADD_ATTRIBUTE);
    printf("%d) ELIMINAR ATRIBUTO\n", DELETE_ATTRIBIUTE);
    printf("%d) MODIFICAR ATRIBUTO\n", MODIFY_ATTRIBUTE);
    printf("%d) REGRESAR AL PRIMER MENU\n", RETURN);
}

int readUserInput()
{
    int userSelection;
    printf("selecciona:");

    scanf("%d", &userSelection);

    clearInputBuffer();

    return userSelection;
}

void clearInputBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
    {
    }
}

void processUserSelection(DictionaryMenuOption userSelection)
{
    char fileName[MAX_NAME_SIZE];

    switch (userSelection)
    {
    case NEW_DICTIONARY:
        readUserString("ingresa el nombre del diccionario: ", fileName, sizeof(fileName));
        initializeDataDictionary(fileName);

        break;
    case OPEN_DICTIONARY:
        readUserString("ingresa el nombre del diccionario que quieres abrir:", fileName, sizeof(fileName));

        if (openDataDictionary(fileName) == EXIT_SUCCESS)
        {
            printSubmenu();
            int currentSelectionSub = readUserInput();

            processUserSelectionSubmenu(currentSelectionSub, fileName);
        }

        break;
    case CLOSE_PROGRAM:

        printf("cierra.");
        break;

    default:
        printf("opcion invalida");
        break;
    }
}

void processUserSelectionSubmenu(DictionaryMenuOption userSelection, char fileName[MAX_NAME_SIZE])
{

    char entityname[MAX_NAME_SIZE];
    char attributename[MAX_NAME_SIZE];
    char attributeNewName[MAX_NAME_SIZE];
    char newEntityName[MAX_NAME_SIZE];
    int attribute_type;

    switch (userSelection)
    {

    case PRINTF_DICTIONARY:
        printDataDictionary(fileName);
        break;

    case ADD_ENTITY:

        readUserString("ingresa el nombre de la entidad: ", entityname, sizeof(entityname));
        newDataEntity(fileName, entityname);
        break;

    case DELETE_ENTITY:
        readUserString("ingresa el nombre de la entidad que quieras eliminar ", entityname, sizeof(entityname));
        removeDataEntity(fileName, 0L, entityname);

        break;

    case MODIFI_ENTITY:

        readUserString("ingresa entidad para modificar: ", entityname, sizeof(entityname));
        readUserString("ingresa el NUEVO nombre: ", newEntityName, sizeof(newEntityName));
        modifyEntityNameInFile(fileName, entityname, newEntityName);
        break;

    case ADD_ATTRIBUTE:

        readUserString("ingresa el nombre de la entidad: ", entityname, sizeof(entityname));
        readUserString("ahora ingresa el nombre qu quieres el nombre del atributo: ", attributename, sizeof(attributename));
        printf("selecciona el tipo: 0(char) 1(int) 2(varchar): ");
        scanf("%d", &attribute_type);

        newDataAttribute(fileName, entityname, attributename, attribute_type);
        break;

    case DELETE_ATTRIBIUTE:

        readUserString("ingresa la entidad del atributo que quieras eliminar: ", entityname, sizeof(entityname));
        readUserString("ingresa el atributo que quieras eliminar: ", attributename, sizeof(attributename));
        removeDataAttribute(fileName, 0L, entityname, attributename);

        break;

    case MODIFY_ATTRIBUTE:

        readUserString("ingresa el nombre de la entidad del atributo que quieras modificar: ", entityname, sizeof(entityname));
        readUserString("ingresa el nombre del atributo: ", attributename, sizeof(attributename));
        readUserString("ingresa el nuevo nombre: ", attributeNewName, sizeof(attributeNewName));
        printf("ingresa el tipo de atributo: 0(char) 1(int) 2(varchar): ");
        scanf("%d", &attribute_type);
        modifyAttribute(fileName, entityname, attributename, attributeNewName, attribute_type);

        break;

    case RETURN:

        return;

        break;

    default:
        printf("Invalid option!");
        break;
    }
}

void readUserString(const char *prompt, char *buffer, size_t size)
{
    if (prompt != NULL)
    {
        printf("%s", prompt);
    }

    if (fgets(buffer, size, stdin) == NULL)
    {
        buffer[0] = '\0'; // Handle EOF or read error by clearing buffer
        return;
    }

    // Remove newline character if present
    buffer[strcspn(buffer, "\n")] = '\0';
}