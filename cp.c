#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#define SIZE 100

int main(int argc, char *argv[]) {
	int fd = open(argv[1], O_RDONLY);
	if(fd < 0){
		exit(-1);
	}
	remove(argv[2]);

	int fd2 = open(argv[2], O_CREAT | O_RDWR,0644);
	char buf[SIZE];
	int num_read,num_write;
	while((num_read = read(fd ,buf,SIZE)) > 0){
		if((num_write = write(fd2, buf, num_read)) < 0)
			exit (-2);
	}
	printf("\n");	
	close(fd);
	close(fd2);
	return 0;
}
