#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "allFunctions.h"

#define DEBUG_MODE 0    /* Debug mode OFF/ON.  */
#define EXIT_FAILURE 1  /* Failing exit status.  */
#define EXIT_SUCCESS 0  /* Successful exit status.  */


void getArgumentsFromInput(char *fileName) {

    FILE *readFrom = fopen(fileName, "r");


        if (readFrom == NULL) {
            fprintf(stderr, "Value of errno: %d\n", errno);
            exit(EXIT_FAILURE);
        }
        
        uint32_t rows, cols;
        uint32_t *prows = &rows;
        uint32_t *pcols = &cols;
        uint32_t **coloursArray;


        prepeareFileToExtractData(readFrom, prows, pcols);
        coloursArray = allocArray(rows, cols);
        fillArray(readFrom, coloursArray, rows, cols);
        
    #if DEBUG_MODE
        printArray(coloursArray, rows, cols);
    #endif
        
        findLongestSequence(coloursArray, rows, cols);

        deAllocArray(coloursArray, rows, cols);
        fclose(readFrom);

        // argvCount++;
}


uint32_t checkPositions(uint32_t **coloursArray, uint32_t row, uint32_t rows, uint32_t col, uint32_t cols, char symbol){

    uint32_t result = 0;
    uint32_t minRow = 0;
    uint32_t minCol = 0;
    uint32_t maxRow = rows - 1;
    uint32_t maxCol = cols - 1;

    /* upper left corner element */
    if( minRow == row && minCol == col ){
        if((coloursArray[row][col+1] == symbol) ||
           (coloursArray[row+1][col] == symbol)){
            result = 1;
        }
    }
    
    /* upper right corner element */
    else if((minRow == row) && (maxCol == col)){
        if((coloursArray[row][col-1] == symbol) ||
           (coloursArray[row+1][col] == symbol)){
            result = 1;
        }
    }
    
    /* bottom right corner element */
    else if(maxRow == row && maxCol == col){
        if((coloursArray[row][col-1] == symbol) ||
           (coloursArray[row-1][col] == symbol)){
            result = 1;
        }
    }
    
    /* bottom left corner element */
    else if((maxRow == row) && (minCol == col)){
        if((coloursArray[row][col+1] == symbol) ||
           (coloursArray[row-1][col] == symbol)){
            result = 1;
        }
    }
    
    /* uperr row element */
    else if((minRow == row) && (minCol != col) && (maxCol != col)){
        if((coloursArray[row][col-1] == symbol) ||
           (coloursArray[row][col+1] == symbol) ||
           (coloursArray[row+1][col] == symbol)){
            result = 1;
        }
    }
    
    /* bottom row element */
    else if((maxRow == row) && (minCol != col) && (maxCol != col)){
        if((coloursArray[row][col-1] == symbol) ||
           (coloursArray[row][col+1] == symbol) ||
           (coloursArray[row-1][col] == symbol)){
            result = 1;
        }
    }
    
    /* left column element */
    else if((maxRow != row) && (minRow != row) && (minCol == col)){
        if((coloursArray[row-1][col] == symbol) ||
           (coloursArray[row+1][col] == symbol) ||
           (coloursArray[row][col+1] == symbol)){
            result = 1;
        }
    }
    
    /* right column element */
    else if((maxRow != row) && (minRow != row) && (maxCol == col)){
        if((coloursArray[row-1][col] == symbol) ||
           (coloursArray[row+1][col] == symbol) ||
           (coloursArray[row][col-1] == symbol)){
            result = 1;
        }
    }
    
    /* right column element */
    else if((maxRow != row) && (minRow != row) && (maxCol != col) && (minCol != col)){
        if((coloursArray[row-1][col] == symbol) ||
           (coloursArray[row+1][col] == symbol) ||
           (coloursArray[row][col-1] == symbol) ||
           (coloursArray[row][col+1] == symbol) ){
            result = 1;
        }
    }

#if DEBUG_MODE
    if(result){
        printf("Hit symbol %c\n", symbol);
    }
#endif

    return result;

}

void findLongestSequence(uint32_t **coloursArray, uint32_t rows, uint32_t cols) {

    uint32_t row, col;
    char temp;
    char r = 'R';
    char g = 'G';
    char b = 'B';
    uint32_t longTempR = 0;
    uint32_t longTempG = 0;
    uint32_t longTempB = 0;
    uint32_t longR = 0;
    uint32_t longG = 0;
    uint32_t longB = 0;
    uint32_t result = 0;
    

    for(row = 0; row < rows; row++){

        for(col = 0; col < cols; col++){

            temp = coloursArray[row][col];

            if(temp == r){
                result = checkPositions(coloursArray, row, rows, col, cols, r);
                if(result)
                    longTempR++;
                if(longTempR > longR)
                    longR = longTempR;
                
            } else if (temp == g){
                result = checkPositions(coloursArray, row, rows, col, cols, g);
                if(result)
                    longTempG++;
                if(longTempG > longG)
                    longG = longTempG;
                
            } else if (temp == b){
                result = checkPositions(coloursArray, row, rows, col, cols, b);
                if(result)
                    longTempB++;
                if(longTempB > longB)
                    longB = longTempB;
            }
        }
    }

    if (longR >= longG && longR >= longB){
        printf("The winner is R with longest sequences of %d elements\n", longR);
    } else if (longG >= longR && longG >= longB){
        printf("The winner is G with longest sequences of %d elements\n", longG);
    } else if (longB >= longR && longB >= longG){
        printf("The winner is B with longest sequences of %d elements\n", longB);
    }
}

void pruint32_tFile(FILE *readFrom){

    uint32_t a;

    while((a = getc(readFrom)) != EOF){
                printf("%c", a);
    }
    
    printf("\n");

    fseek(readFrom, 0, SEEK_SET);
}


void fillArray(FILE *readFrom, uint32_t **array, uint32_t rows, uint32_t cols) {

    uint32_t row, col;
    uint32_t a;

    for(row = 0; row < rows; row++){
        for(col = 0; col < cols; col++){

            a = getc(readFrom);

            while(isspace(a)){
                a = getc(readFrom);
            }

            array[row][col] = a;
        }
    }
}



uint32_t **allocArray(uint32_t rows, uint32_t cols) {
    
    uint32_t **array;
    uint32_t row;

    array = (uint32_t **)malloc(rows * (sizeof (*array)));
    if (array == NULL) {
        printf("Memory allocate fail!\n");
        exit(EXIT_FAILURE);
    }

    for (row = 0; row < rows; row++)
    {
        array[row] = (uint32_t *)malloc(cols * (sizeof (*array[row])));
    }

    return array;
}


void deAllocArray(uint32_t **array, uint32_t rows, uint32_t cols) {

    uint32_t row;

    for (row = 0; row < rows; row++)
    {
        free(array[row]);
    }

    free(array);
}

/*
 Extract rows and columns size
 and set pouint32_ter to first element
 */

void prepeareFileToExtractData(FILE *readFrom, uint32_t *rows, uint32_t *cols){
    
#if DEBUG_MODE
    pruint32_tFile(readFrom);
#endif

    char *line = NULL;
    ssize_t getLine;
    size_t len = 0;

    fscanf(readFrom, "%d %d", rows, cols);

    getLine = getline(&line, &len, readFrom);

}

/*
 For DEBUG_MODE only
 */
void printArray(uint32_t **coloursArray, uint32_t rows, uint32_t cols) {

    uint32_t row, col;

    printf("%s\n", "print array");

    for(row = 0; row < rows; row++){
        for(col = 0; col < cols; col++){
            printf("%c", coloursArray[row][col]);
        }
        printf("\n");
    }
}
















