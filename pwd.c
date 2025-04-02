#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
int pwd_main(){
        char *buf = getcwd(NULL,0);
        if(buf == NULL)
                exit(-1);
        else
                printf("%s\n", buf);
                exit(0);

}