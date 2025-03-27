#include <stdio.h>
#include <stdlib.h>

#include "lib/LabMenu.h"
#include "lib/country.h"



void main() {
    size_t length = 0;
    Country* array = NULL;
    long answer = 0;

    printCenteredLine("Lab 3");
    array = getInitialArray(&length);

    do {
        printf("What would you like do with a list?\n");
        printLineWithOffset("1. Add country to the list", 2);
        printLineWithOffset("2. Delete countries by capital", 2);
        printLineWithOffset("3. Find by population and print", 2);
        printLineWithOffset("4. Print info about countries", 2);
        printLineWithOffset("5. Exit programm", 2);
        readLongWithDialog_v(&answer, ">", isValidInput);
        array = performActionByCode(array, &length, answer);
    } while (answer != 5);

    for(size_t i = 0; i < length; i++){
        free(array[i].capital);
    }
    free(array);
    return;
}
