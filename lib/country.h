#ifndef ___COUNTRY_LIB_DEF
#define ___COUNTRY_LIB_DEF

#include <stdlib.h>

typedef struct Country {
    size_t population;
    char* capital;
    char gov[30];
    size_t area;
} Country;

int isPopulationEqual(Country* country, void* data);
int isValidInput(long n);


size_t findCountries(Country* array, size_t length, size_t** result, int(check)(Country*, void*), void* data);
Country* deleteCountries(Country* array, size_t *length, int(check)(Country*, void*), void* data);
void readCountry(Country* country);
void printCountry(Country* country);
Country* deleteByCapital(Country* array, size_t * length, char * capital);
Country* getInitialArray(long* len);
Country* performActionByCode(Country* array, size_t* length, int code);

#endif