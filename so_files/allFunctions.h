#ifndef ALLFUNCTIONS_H__
#define ALLFUNCTIONS_H__


#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <errno.h>



#if 0
#define DEBUG_MODE 0
#endif

void getArgumentsFromInput(char *fileName);
void prepeareFileToExtractData(FILE *readFrom, uint32_t *rows, uint32_t *cols);
uint32_t **allocArray(uint32_t rows, uint32_t cols);
void deAllocArray(uint32_t **coloursArray, uint32_t rows, uint32_t cols);
void fillArray(FILE *readFrom, uint32_t **coloursArray, uint32_t rows, uint32_t cols);
void printArray(uint32_t **coloursArray, uint32_t rows, uint32_t cols);
void findLongestSequence(uint32_t **coloursArray, uint32_t rows, uint32_t cols);
uint32_t checkPositions(uint32_t **coloursArray, uint32_t row, uint32_t rows, uint32_t col, uint32_t cols, char symbol);


#endif  // ALLFUNCTIONS_H__