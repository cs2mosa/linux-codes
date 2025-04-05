#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_INPUT_SIZE 1024
#define PROMPT "Femto shell prompt > "

int main(int argc, char *argv[]) {
    char input[MAX_INPUT_SIZE];
    char str[] = "This is a sample string";
    char *token;
    
    // Get the first token
    token = strtok(str, " ");
    
    // Walk through other tokens
    while (token != NULL) {
        printf("%s\n", token);
        token = strtok(NULL, " ");
    }
    
    return 0;
    /*while (1) {
        // Display prompt
        printf("%s", PROMPT);
        //fflush(stdout);
        
        // Get input from user
        if (fgets(input, MAX_INPUT_SIZE, stdin) == NULL) {
            break; // Handle EOF (Ctrl+D)
        }
        
        // Remove trailing newline
        input[strcspn(input, "\n")] = '\0';
        if(strlen(input) == 0)
            continue;
        // Check if input starts with "exit"
        if (strcmp(input, "exit") == 0) {
            printf("Good Bye\n");
            break;
        }
        // Check if input starts with "echo "
        else if (strncmp(input, "echo ", 5) == 0) {
            // Print everything after "echo "
            printf("%s\n", input + 5);
        }
        // Any other command is invalid
        else {
            printf("Invalid command\n");
        }
    }
    
    return 0;*/
}