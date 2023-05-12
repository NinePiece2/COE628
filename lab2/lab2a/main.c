#include <stdio.h>  //printf, fprintf
#include <stdlib.h> //EXIT_SUCCESS
#include <string.h> //strlen, strcmp
#define TOO_MANY_ARGS 2
#define TOO_FEW_ARGS 1

int main(int argc, char* argv[]) {
    //Default values:
    int exit_code = EXIT_SUCCESS;
    char * greeting = "Hello";
    char * person = "UNKNOWN";
    
    //Add code to change the exit_code depending on argc
    switch (argc){
        case 1:
            exit_code = TOO_FEW_ARGS;
            break;
        case 2:
            exit_code = EXIT_SUCCESS;
            break;
        default:
            exit_code = TOO_MANY_ARGS;
    }
    
    //Add code to change 'person' if one is given on command line
    if (argv[1] != NULL){
        person = argv[1];
    }
    
    int len = strlen(argv[0]);
    char * last3 = argv[0] + len - 3; //last3 points to last 3 chars
    fprintf(stderr, "%s\n", argv[0]);
    fprintf(stderr, "%s\n", last3);
    
    //Add code to change 'greeting' if last 3 chars of command are 'bye'
    if (strcmp(last3, "bye") == 0){
        greeting = "Bye";
    }
    
    printf("%s %s\n", greeting, person);
    
    fprintf(stderr, "exit_code: %d\n", exit_code);
    
    return exit_code; //Could also say exit(exit_code)
}