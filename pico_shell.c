#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

#define BUF_SIZE 1024
int main(){
        pid_t pid;
        char buf[BUF_SIZE];
        while(1){
                printf("linux command line$ ");
                fgets(buf, BUF_SIZE, stdin);
                buf[strlen(buf)-1] = 0;
                if(strcmp("exit", buf) == 0)
                        break;
                if(strlen(buf) == 0){
                        continue;
                }
                pid = fork();
                if(pid > 0){
                        int status;
                        wait(&status);
                }
                else if(pid == 0){
                    char *argv = strtok(buf," ");
                    int cap = 5;
                    char **strings  = (char**)malloc(cap*sizeof(char*));
                    for(int  i = 0 ; argv!=NULL;i++){
                            if(i >= cap){
                                    cap *= 2;
                                    strings = (char**)realloc(strings,cap*sizeof(char*));
                            }
                            strings[i] = argv;
                            argv = strtok(NULL," ");
                    }
                    execvp(buf , strings);
                    free(strings);
                    exit(-1);
            }
            else{
                    printf("failure");
            }

    }
    return 0;
}