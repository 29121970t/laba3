#include <stdio.h>
#include <stdlib.h>


#include "lib/parseLib4.h"

typedef struct Country {
    size_t population;
    char* capital;
    char gov[20];
    size_t area;
} Country;

int strcopm(char* s1, char* s2) {
    for (size_t i = 0; s1[i] != 0 && s2[i] != 0; i++) {
        if (s1[i] != s2[i]) return 0;
    }
    return 1;
}
void _strcpy(char * dest, char * src){
    for (size_t i = 0; src[i]; i++)
    {
        dest[i] = src[i];
    }
    
}
int isShorterThen20(char* str, size_t len) { return len <= 20; }

int isPopulationEqual(Country* country, void* data) { return country->population == *(size_t*)data; }
int isCapitalEqual(Country* country, void* data) { return strcopm(country->capital, data); }

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

void readCountry(Country* country) {
    long pop = 0;
    long area = 0;
    char * tmpLine;
    readLongWithDialog_v(&pop, "Please enter country population (a number > 0): ", isG0);
    readLineWithDialog(&country->capital, "Please enter capital name: ", NULL);
    readLineWithDialog_v(&tmpLine, "Please enter government type name (shoulb be shorter then 20 character): ", NULL,
                         isShorterThen20);
    readLongWithDialog_v(&area, "Please enter country area (a number > 0): ", isG0);
    _strcpy(country->gov, tmpLine);
    country->population = pop;
    country->area = area;
    free(tmpLine);
}
void printCountry(Country* country) {
    printf("Population - %ld\nCapital - %s\nGovernment type - %s\nArea - %ld\n", country->population, country->capital, country->gov,
           country->area);
}

void main() {
    Country* countries = calloc(3, sizeof(Country));
    countries[0].population = 2;
    countries[1].population = 2;
    readCountry(&countries[2]);
    printCountry(&countries[2]);

    size_t* res;
    size_t p = 2;
    size_t count = findCountries(countries, 3, &res, isPopulationEqual, &p);

    for (size_t i = 0; i < count; i++) {
        printf("%ld\n", res[i]);
    }

    return;
}
