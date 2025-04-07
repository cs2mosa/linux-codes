#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <ctype.h>
#define BUF_SIZE 1024
extern char **environ;

int main(){
	pid_t pid;
	char buf[BUF_SIZE];
	while(1){
		printf("linux command line$ ");
		fgets(buf, BUF_SIZE, stdin);
		buf[strlen(buf)-1] = 0;
		if(strcmp("exit", buf) == 0)
			break;
		if(strlen(buf) == 0)
			continue;
	
		char *LOCAL_VARS[BUF_SIZE];
		LOCAL_VARS[BUF_SIZE-1] = NULL;
		char *dol = strchr(buf, '$');
		if (dol != NULL) {
    			char *end = dol+1;
			while (*end != '\0' && *end != ' ') {
        			end++;
    			}
    		char saved = *end;
    		*end = '\0';
    		for (int i = 0; LOCAL_VARS[i] != NULL; i++) {
        		char *equals = strchr(LOCAL_VARS[i], '=');
        		if (equals && strncmp(LOCAL_VARS[i], dol+1, equals-LOCAL_VARS[i]) == 0) {
				char *value = equals + 1;
				char result[1024] = {0};
            			strncpy(result, buf, dol - buf);
            			strcat(result, value);
            			*end = saved;
            			strcat(result, end);
            			strcpy(buf, result);
            			break;
        		}
    		}
    
    			if (*end == '\0') {
        			*end = saved;
    			}
		}	
	
		char *argv = strtok(buf," ");
                int cap = 5;
                char **strings = (char**)malloc(cap*sizeof(char*));
                int  i = 0;
                for(;argv!=NULL;i++){
                        if(i >= cap){
                                cap *= 2;
                                strings = (char**)realloc(strings,cap*sizeof(char*));
                        }
                        strings[i] = argv;
                        argv = strtok(NULL," ");
                }
                strings[i] = NULL;
                if (strcmp(strings[0], "cd") == 0) {
                        if (strings[1] == NULL) {
                            printf("Missing argument for cd\n");
                        } else {
                            if (chdir(strings[1]) != 0) {
                                perror("cd failed");
                            }
                        }
                        free(strings);
                        continue;
                }
		i = 0;
		char *y = NULL;
		if (strings[1] != NULL) {
			y = strchr(strings[1], '=');
		}
		if (strcmp(strings[0],"export")!=0 && (strchr(strings[0], '=') != NULL || y != NULL)) {
			
            		if (strings[1] != NULL) {
                		printf("Invalid command\n");
            		} else {
				int l = 0;
				LOCAL_VARS[l] = (char*)malloc(strlen(strings[0]) + 1);
				if (LOCAL_VARS[l] != NULL) {
    					strcpy(LOCAL_VARS[l], strings[0]);
    					l++;
				}
            		}
            		free(strings);
           	 	continue; 
        	}
		if (strcmp(strings[0], "export") == 0) {
            		if (strings[1] == NULL || strings[2] != NULL) {
                		printf("Usage: export Variable=Value (no spaces allowed)\n");
            		} else if (strchr(strings[1], '=') != NULL) {
                		char *eq = strchr(strings[1], '=');
                		*eq = '\0';
                		char *var = strings[1];      
                		char *val = eq + 1;       
                		if (setenv(var, val, 1) != 0) {
                    			perror("setenv failed");
                		}
            			} else {
                			printf("Usage: export Variable=Value (no spaces allowed)\n");
            			}
            		free(strings);
            		continue; 
        	}


		pid = fork();
                if(pid > 0){
                        int status;
                        wait(&status);
                }
                else if(pid == 0){
                    execvp(buf , strings);
                    free(strings);
		    printf("failed to execute the given command");
                    exit(-1);
           	}
            	else{
                    printf("failure");
		}
	}
	return 0;
}
