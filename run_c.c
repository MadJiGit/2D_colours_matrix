#include <stdio.h>
#include <stdlib.h>
#include "allFunctions.h"
#include <errno.h>

// #define DEBUG_MODE 0    /* Debug mode OFF/ON.  */
// #define EXIT_FAILURE 1   Failing exit status.  
// #define EXIT_SUCCESS 0  /* Successful exit status.  */


int main(int argc, char *argv[]){


    if (argc < 2)
    {
        printf("%s\n", "Please, enter a file name!"); 
        return 0;  
    } 

    int argvCount = 1;


    for (int i = 2; i <= argc; ++i)
    {   

        // char *temp = argv[argvCount++];

        getArgumentsFromInput(argv[argvCount++]);

    }

    return 0;
}