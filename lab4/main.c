/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: Romit Sagu
 *
 * Created on February 9, 2023, 5:08 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // For pipe, dup and fork

char **StringTokenizer(char *in, char *parser){
    int i = 0;
    char **out = malloc(sizeof(char)*100);
    char *currentToken;
    
    currentToken = strtok(in, parser);
    
    while (currentToken != NULL){
        out[i] = currentToken;
        i++;
        currentToken = strtok(NULL, parser);
    }
    
    out[i] = NULL;
    return out;
}

/*
 * 
 */
int main(int argc, char** argv) {
    char *input = malloc(sizeof(char)*100);
    int i = 0;
    char *firstCmd = malloc(sizeof(char)*100);
    char *secondCmd = malloc(sizeof(char)*100);
    char **cmdToken1, **cmdToken2;
    int pipeInt[2];
    
    printf("Your command> ");
    
    input[i] = getchar();
    
    while (input[i] != '\n'){
        i++;
        input[i] = getchar();
        
    }
    
    //printf("Input> %s\n", input);
    
    i = 0;
    while (input[i] != '|'){
        firstCmd[i] = input[i];   
        i++;
    }

    firstCmd[i] = '\0';
        
    //printf("First> %s\n", firstCmd);
    i++;

    int j = 0;
    while (input[i] != '\n'){
        secondCmd[j] = input[i];
        
        j++;
        i++;
    }
    
    secondCmd[j] = '\0';
    //printf("Second> %s\n", secondCmd);
    
    cmdToken1 = StringTokenizer(firstCmd, " ");
    cmdToken2 = StringTokenizer(secondCmd, " ");
    
    //printf("Token1> %s\n", cmdToken1);
    //printf("Token2> %s\n", cmdToken2);
    
    pipe(pipeInt);
    
    if(fork() == 0){
        dup2(pipeInt[1], STDOUT_FILENO);
        close(pipeInt[0]);
        execvp(cmdToken1[0], cmdToken1);
    }else{
        dup2(pipeInt[0], STDIN_FILENO);
        close(pipeInt[1]);
        execvp(cmdToken2[0], cmdToken2);
    }
    
    return (EXIT_SUCCESS);
}



