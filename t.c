#include <limits.h>
#include <stdio.h>
#include <time.h>

#include "lib/LabMenu.h"
#include "lib/parseLib4.h"

void calcFreqInFile(FILE *file, size_t *counts) {
    long tempPtr = ftell(file);
    char tempC;

    rewind(file);
    while ((tempC = fgetc(file)) > 0) counts[tempC]++;

    fseek(file, tempPtr, SEEK_SET);
}

int replaceCharInFile(FILE *file, char from, char to) {
    long tempPtr = ftell(file);
    char tempC;

    rewind(file);
    while ((tempC = fgetc(file)) > 0) {
        if (tempC == from) {
            fseek(file, -sizeof(char), SEEK_CUR);
            fwrite(&to, sizeof(char), 1, file);
        }
    }
    fseek(file, tempPtr, SEEK_SET);
}
void printFreqances(size_t *counts) {
    for (int i = 0; i < 128; i++) {
        if (counts[i] != 0) {
            if (i == ' ') {
                printf("%s - %lu\n", "<space>", counts[i]);
            } else {
                printf("%c - %lu\n", i, counts[i]);
            }
        }
    }
}

void printFile(FILE *file) {
    rewind(file);
    char tempC;
    while ((tempC = getc(file)) > 0) fputc(tempC, stdout);
    puts("");
}
int isCharString(char *str, size_t len) {
    if (len > 2) return 0;
    return 1;
}

int main(int argc, char const *argv[]) {
    FILE *file;
    size_t counts[128] = {0};
    char tempC;
    char rchar;
    char testString[] = "TTTest Striiiing";
    long length = 0;
    char *str;
    unsigned int seed;

    if (argc < 2) {
        puts("Error: No file name was passed.");
        return 1;
    }

    if ((file = fopen(argv[1], "w+")) == NULL) {
        puts("Error: Cannot open provided file.");
        return 1;
    }

    switch (start("Lab Work 2")) {
        case USER_INPUT:
            printf("Please enter a string: ");
            while ((tempC = getc(stdin)) != '\n') fputc(tempC, file);
            readLineWithDialog_v(&str, "Please enter replacment character: ", NULL, isCharString);
            rchar = str[0];
            free(str);
            break;

        case DEMO_INPUT:
            fwrite(testString, sizeof(char), 16, file);
            rchar = '-';
            break;

        case RANDOM_INPUT:
            readLongWithDialog_v(&length, "Please enter string length: ", isG0);
            str = calloc(length, sizeof(char));

            seed = (unsigned int)time(NULL);
            for (size_t i = 0; i < length; i++) {
                seed = MrandomUInt(seed);
                str[i] = (char)map(0, 254803967, 32, 126, (double)seed);
            }
            rchar = (char)map(0, 254803967, 32, 126, (double)MrandomUInt(seed));
            fwrite(str, sizeof(char), length, file);
            free(str);
            break;
            
        case EXIT_INPUT:
            return 0;
            break;

        default:
            puts("Somthing horable went wrong...");
            return 1;
            break;
    }
    printf("Input string: ");
    printFile(file);

    printf("Input replacment charecter: %c\n", rchar);

    calcFreqInFile(file, counts);

    printFreqances(counts);

    replaceCharInFile(file, ' ', rchar);

    printf("Result string: ");
    printFile(file);

    fclose(file);
    return 0;
}
