/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: Romit Sagu
 *
 * Created on February 7, 2023, 4:00 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/types.h>

/*
 * 
 */

int main(int argc, char** argv) {
    char input[100];
    char cmd[100];
    int i = 0;
    int flag = 0;
    
    char *argPointer [100];
    int argPointerIndex = 0;
    int numOfArgPointer = 1;
    
    printf("Your command> \n");
    
    argPointer[argPointerIndex] = &input[i];
    
    input[i] = getchar();
    
    while (input[i] != '\n'){
        
        if (input[i] == ' '){ // Check if the character is a space
            input[i] = NULL; // Set it to null
            
            numOfArgPointer++;
            argPointerIndex++;
            argPointer[argPointerIndex] = &input[i+1]; // The next character is the address of the pointer
        }
        

        i++;
        input[i] = getchar();
    }
    
    if (input[i-1] == '&'){
        flag = 1;
    }
    
    pid_t pid;
    
    if (fork() == 0){
        printf("Child Process created \n");
        
        i = 0;
        
        for (argPointerIndex = 0; argPointerIndex < numOfArgPointer; argPointerIndex++){
            i = 0;
            
            while (*argPointer[argPointerIndex] != NULL){
                cmd[i] = *argPointer[argPointerIndex];
                argPointer[argPointerIndex] = argPointer[argPointerIndex + 1];
                
                i++;
            }
            cmd[i] = NULL;
            system(cmd); // Sends the command to the shell
        }
   
        exit(0);
        
    } else{
        printf("Parent Process waiting \n");
        
        if(flag == 0){
            pid = wait(NULL);
        }
        
        printf("Parent Process ended \n");
    }
    
    return (EXIT_SUCCESS);
}
