#include "country.h"

#include "LabMenu.h"
#include "parseLib4.h"
#include "strLib.h"

int isShorterThen30(char* str, size_t len) { return len <= 30; }
int isPopulationEqual(Country* country, void* data) { return country->population == *(size_t*)data; }
int isCapitalEqual(Country* country, void* data) { return strcopm(country->capital, (char*)data); }
int isValidInput(long n) { return n >= 1 && n <= 5; }

size_t findCountries(Country* array, size_t length, size_t** result, int(check)(Country*, void*), void* data) {
    size_t* indexies = calloc(length, sizeof(size_t));
    size_t resultCount = 0;
    for (size_t i = 0; i < length; i++) {
        if (check(array + i, data)) {
            indexies[resultCount] = i;
            resultCount++;
        }
    }
    indexies = realloc(indexies, sizeof(size_t) * resultCount);
    *result = indexies;
    return resultCount;
}

// Country* deleteCountries(Country* array, size_t* length, int(check)(Country*, void*), void* data) {
//     size_t resultCount = 0;
//     size_t len = *length;

//     for (size_t i = 0; i < len; i++) {
//         printf("###%s\n", array[i].capital);

//         if (check(array + i, data)) {
//             free(array[i].capital);
//             memcpy(array + i, array + i + 1, (len - i - 1) * sizeof(Country));
//             resultCount++;
//         }
//     }
//     len -= resultCount;
//     if (len > 0 && resultCount && !(array = realloc_f(array, len * sizeof(Country)))) handleMallocError();
//     *length = len;
//     return array;
// }
// do not work6
Country* deleteCountries(Country* array, size_t* length, int(check)(Country*, void*), void* data) {
    size_t* indexes = NULL;
    size_t len = *length;
    size_t count = findCountries(array, len, &indexes, check, data);

    for (size_t i = 0; i < count; i++) {
        size_t index = indexes[i];
        free(array[index].capital);
        memcpy(array + index, array + index + 1, (len - 1 - index) * sizeof(Country));
    }
    free(indexes);
    len -= count;
    if (len > 0 && count && !(array = realloc_f(array, len  * sizeof(Country)))) handleMallocError();
    *length = len;
    return array;
}

void readCountry(Country* country) {
    long pop = 0;
    long area = 0;
    char* tmpLine;
    readLongWithDialog_v(&pop, "Please enter country population (a number > 0): ", isG0);
    readLineWithDialog(&(country->capital), "Please enter capital name: ", NULL);
    readLineWithDialog_v(&tmpLine, "Please enter government type name (shoulb be shorter then 30 character): ", NULL, isShorterThen30);
    readLongWithDialog_v(&area, "Please enter country area in km^2 (a number > 0): ", isG0);
    _strcpy(country->gov, tmpLine);
    country->population = pop;
    country->area = area;
    free(tmpLine);
}
void printCountry(Country* country) {
    printf("Population - %ld\nCapital - %s\nGovernment type - %s\nArea - %ld\n", country->population, country->capital, country->gov,
           country->area);
}
/**@deprecated 
 * 
*/
Country* deleteByCapital(Country* array, size_t* length, char* capital) {
    size_t len = *length;
    size_t count = 0;
    for (size_t i = 0; i < len; i++) {
        if (strcopm(array[i].capital, capital)) {
            free(array[i].capital);
            memcpy(array + i, array + i + 1, (len - i - 1) * sizeof(Country));
            count++;
        }
    }
    len -= count;
    if (count && !(array = realloc_f(array, len * sizeof(Country)))) handleMallocError();
    printf("Deleted %lu countries\n", count);
    *length = len;
    return array;
}
Country* getInitialArray(long* len) {
    long length = 0;
    Country* countries = NULL;
    long answer = 0;
    printf("How would you like to initialize list of countries?\n");
    printLineWithOffset("1. By hand", 2);
    printLineWithOffset("2. Use demo data", 2);
    do {
        readLongWithDialog_v(&answer, ">", isValidInput);

        switch (answer) {
            case 1:
                readLongWithDialog_v(&length, "Please enter how many countries you want to enter:", isG0);
                countries = calloc(length, sizeof(Country));

                for (long i = 0; i < length; i++) {
                    printf("%ld-th country parametrs:\n", i + 1);
                    readCountry(countries + i);
                    puts("");
                }
                break;
            case 2:
                length = 4;
                countries = calloc(length, sizeof(Country));

                countries[0].capital = calloc(7, sizeof(char));
                _strcpy(countries[0].capital, "Berlin");
                countries[0].area = 357022;
                _strcpy(countries[0].gov, "Republic");
                countries[0].population = 83000000;

                countries[1].capital = calloc(7, sizeof(char));
                _strcpy(countries[1].capital, "Brazil");
                countries[1].area = 8515767;
                _strcpy(countries[1].gov, "Republic");
                countries[1].population = 213000000;

                countries[2].capital = calloc(6, sizeof(char));
                _strcpy(countries[2].capital, "Tokyo");
                countries[2].area = 377975;
                _strcpy(countries[2].gov, "Constitutional Monarchy");
                countries[2].population = 126000000;

                countries[3].capital = calloc(6, sizeof(char));
                _strcpy(countries[3].capital, "Cairo");
                countries[3].area = 1010408;
                _strcpy(countries[3].gov, "Republic");
                countries[3].population = 104000000;

                break;

            default:
                printf("Error: Check your input.\n");
                break;
        }
    } while (answer < 1 || answer > 2);
    *len = length;
    return countries;
}

Country* performActionByCode(Country* array, size_t* length, int code) {
    char* cap = NULL;
    size_t count = 0;
    long populationCheck = 0;
    size_t* indexes = NULL;

    switch (code) {
        case 1:
            (*length)++;
            if (!(array = realloc_f(array, (*length) * sizeof(Country)))) handleMallocError();
            readCountry(array + *length - 1);
            break;
        case 2:
            readLineWithDialog(&cap, "Please enter capital name: ", NULL);
            printf("1\n");

            count = *length;
            array = deleteCountries(array, length, isCapitalEqual, cap);
            printf("2\n");
            count -= *length;

            if (!count) {
                printf("No countries were deleted\n");
            } else {
                printf("%ld countries were deleted\n", count);
            }
            free(cap);

            break;
        case 3:
            readLongWithDialog_v(&populationCheck, "Please enter county population: ", isG0);
            count = findCountries(array, *length, &indexes, isPopulationEqual, &populationCheck);
            for (size_t i = 0; i < count; i++) {
                puts("");
                printCountry(array + indexes[i]);
                puts("");
            }
            if (!count) printf("No countries were found\n");
            free(indexes);
            break;
        case 4:
            for (size_t i = 0; i < *length; i++) {
                puts("");
                printCountry(array + i);
            }
            puts("");
            if (*length == 0) printf("The list is Empty\n");
            break;
        case 5:
            printf("Goodby!\n");
            break;
        default:
            printf("Invalid input!\n");
            break;
    }
    return array;
}