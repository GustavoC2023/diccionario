#include "main.h"
#include "entity.h"

int main(int argc, char **argv)
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
    printf("\n\t----PRINCIPAL MENU----\n");
    printf("%d) Create a new dictionary.\n", NEW_DICTIONARY);
    printf("%d) Open an existing dictionary.\n", OPEN_DICTIONARY);
    printf("%d) Exit.\n", CLOSE_PROGRAM);
    
}

void printSubmenu(){

    printf("\n\t----SUBMENU DICTIONARY----\n");

    printf("%d) Printf dictionary",PRINTF_DICTIONARY); 
    printf("\n------------------------------\n");
    printf("%d) New Entity.\n",ADD_ENTITY);
    printf("%d) Delete Entity.\n",DELETE_ENTITY);
    printf("%d) Modify Entity.\n",MODIFI_ENTITY);
    printf("\n------------------------------\n");
    printf("%d) New Attribute.\n",ADD_ATTRIBUTE);
    printf("%d) Delete Attribute.\n",DELETE_ATTRIBIUTE);
    printf("%d) Modify Attribute.\n",MODIFY_ATTRIBUTE);
    printf("\n------------------------------\n");
    printf("%d) Return Main Menu.\n",RETURN);

}

int readUserInput()
{
    int userSelection;
    printf("Please select an option:");

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
        readUserString("Enter the data dictionary name: ", fileName, sizeof(fileName));
        initializeDataDictionary(fileName);

        break;
    case OPEN_DICTIONARY:
        readUserString("Enter the data dictionary name: ", fileName, sizeof(fileName));
        openDataDictionary(fileName);

        if(openDataDictionary==EXIT_SUCCESS){

            printf("Dictionary Opened!");
        }

        printSubmenu();
        int currentSelectionSub=readUserInput();
            
        processUserSelectionSubmenu(currentSelectionSub,fileName);
        
        break;
    case CLOSE_PROGRAM:

        printf("Closing...");
        break;

    default:
        printf("Invalid option!");
        break;
    }
}

void processUserSelectionSubmenu(DictionaryMenuOption userSelection,char fileName[MAX_NAME_SIZE]){

    char entityname[MAX_NAME_SIZE];
    char attributename[MAX_NAME_SIZE];
    char newEntityName[MAX_NAME_SIZE];
    int attribute_type;

    switch (userSelection)
    {

    case PRINTF_DICTIONARY:
        printDataDictionary(fileName);
        break;
    
    case ADD_ENTITY:
        
        readUserString("Enter the entity name: ",entityname,sizeof(entityname));
        newDataEntity(fileName,entityname);
        break;     

    
    case DELETE_ENTITY:
        readUserString("Enter the data entity name: ",entityname,sizeof(entityname));  
        removeDataEntity(fileName,0L,entityname);   

        break;   

    case MODIFI_ENTITY:

        readUserString("Enter the entity Name: ",entityname,sizeof(entityname));
        readUserString("Enter the new name of Entity: ",newEntityName, sizeof(newEntityName));
        modifyEntityNameInFile(fileName,entityname,newEntityName);
        break;  

    /*case ADD_ATTRIBUTE:

        readUserString("Enter the entity Name: ",entityname,sizeof(entityname));
        readUserString("Enter the attribute name: ",attributename,sizeof(attributename)); 
        printf("Enter the type of the attribute: 0(char) 1(int) 2(varchar): ");scanf("%d",&attribute_type);

        newDataAttribute(fileName,entityname,attributename,attribute_type);
        break;*/
    
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