#include "attribute.h"

void printAttributes(FILE *dataDictionary, long attributePointer) {
    while (attributePointer != -1L) {
        Attribute currentAttribute;
        
        // Ir a la posiciÃ³n del atributo actual
        fseek(dataDictionary, attributePointer, SEEK_SET);
        // Leer el atributo actual
        fread(&currentAttribute, sizeof(Attribute), 1, dataDictionary);

        // Imprimir los datos del atributo

        char type[15];

        switch (currentAttribute.Type)
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
            break;
        }
        printf("Attribute Name: %s\n", currentAttribute.name);
        printf("Type: %s\n", type);
        printf("Size: %d\n", currentAttribute.size);
        printf("Next Attribute Pointer: %ld\n\n", currentAttribute.ApAtributo);

        // Actualizar el puntero al siguiente atributo
        attributePointer = currentAttribute.ApAtributo;
    }
}

void appendAttribute(FILE *dataDictionary, const long AttributeDirection){


    Attribute tmp;
}






int nuevo_atributo(FILE *ptrDiccionario, const long direccionAtributos)
{
    int operacionResultado = EXIT_SUCCESS;

    TAtributo *atributoTemporal = crear_atributo();

    if (ptrDiccionario)
    {
        if (buscar_atributo(ptrDiccionario, CABECERA_PRINCIPAL, atributoTemporal->nombre) != SIN_DIRECCION)
        {
            fprintf(stderr, "Error para agregar \"%s\" atributo, ya existe.\n", atributoTemporal->nombre);
            operacionResultado = EXIT_FAILURE;
        }
        else if (agregar_atributo(ptrDiccionario, atributoTemporal) == EXIT_SUCCESS)
        {
            reasignar_punteros_atributo(ptrDiccionario, direccionAtributos, atributoTemporal);
        }
        else
        {
            fprintf(stderr, "Error para crear \"%s\" atributo.\n", atributoTemporal->nombre);
            operacionResultado = EXIT_FAILURE;
        }
    }
    else
    {
        fprintf(stderr, "Error para abrir el diccionario de datos.\n");
        operacionResultado = EXIT_FAILURE;
    }
    free(atributoTemporal);

    return operacionResultado;
}*/