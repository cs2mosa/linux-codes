#include <stdio.h>
int echo_main(int argc, char *argv[]) {
        if (argc == 1)printf("\n");
        for(int  i = 1 ; i < argc ; i++){
            if(i== argc-1)
                printf("%s\n", argv[i]);
            else
                printf("%s ", argv[i]);
        }
        return 0;
}